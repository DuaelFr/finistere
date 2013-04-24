<?php

define('FLUX_TIMELIMIT', 240);

/**
 * Synchronisation class
 * Synchronisation with Tourinsoft
 *
 *
 * @author    Fabien CLEMENT - fabien.clement@g-nova.fr
 * @copyright {copyright}
 * @package   {package}
 */
class Synchronisation {

  static $soap;
  static $date;
  static $flux;
  static $vocabs;
  static $vocab;
  static $termCorresp;
  static $start;
  static $retreive_sync;
  static $cache;
  static $done;
  static $onprogress;
  static $currentFlux;
  static $stopedOnFlux;
  static $listingDiff;
  static $syncDateStarted;
  static $fplog;

  public function __construct($url = "") {

    set_time_limit(FLUX_TIMELIMIT);

    if (empty($url)) {
      $url = variable_get('flux_url', "http://cdt29.tourinsoft.com/soft/RechercheDynamique/Syndication/controle/syndication2.asmx");
    }
    $this->soap                   = new nusoap_client($url . '?WSDL', 'WSDL', FALSE, FALSE, FALSE, FALSE, 5, 60);
    $this->soap->soap_defencoding = 'UTF-8';
    $this->soap->decode_utf8      = FALSE;


  }

  /**
   *  Initialise variables
   */
  public function init($reset = FALSE, $flux = array()) {
    $cache = $this->flux_getBigDataCache();

    $this->cache         = new stdClass();
    $this->done          = new stdClass();
    $this->onprogress    = new stdClass();
    $this->retreive_sync = FALSE;

    if ($reset || empty($cache) || (!empty($cache) && !$cache->suspendedSync)) {

      watchdog('flux', 'Cache vide => Nouvelle synchro');

      $this->syncDateStarted = time();

      $this->retreive_sync = FALSE;

      $this->start = microtime(TRUE);

      // Chargement des informations de flux
      if (!$reset && isset($cache->flux) && !empty($cache->flux)) {
        $this->flux = $cache->flux;
      }
      else {
        $this->flux = loadFluxInfos($flux);
      }

      // Chargement des vocabulaires liés
      if (!$reset && isset($cache->vocabs) && !empty($cache->vocabs)) {
        $this->vocabs = $cache->vocabs;
      }
      else {
        $this->loadVocabularies();
      }

    }
    else {

      $this->date            = $cache->date;
      $this->flux            = $cache->flux;
      $this->stopedOnFlux    = $cache->stopedOnFlux;
      $this->vocabs          = $cache->vocabs;
      $this->vocab           = $cache->vocab;
      $this->termCorresp     = $cache->termCorresp;
      $this->done            = $cache->done;
      $this->onprogress      = $cache->onprogress;
      $this->retreive_sync   = TRUE;
      $this->listingDiff     = $cache->listingDiff;
      $this->start           = microtime(TRUE);
      $this->syncDateStarted = $cache->syncDateStarted;

    }
  }


  function flux_getBigDataCache() {
    $cache = variable_get("flux_sync_data_cache", "");
    if (empty($cache)) {
      return "";
    }
    return unserialize(gzuncompress(base64_decode($cache)));
  }

  function flux_setBigDataCache($data) {
    $cache = base64_encode(gzcompress(serialize($data))); // gzcompress car trop gros pour être récupéré ensuite sinon

    variable_set("flux_sync_data_cache", $cache);
  }

  /**
   *  get soap
   */
  public function soap() {
    return $soap;
  }


  /**
   * Execute la synchronisation entre Drupal & Tourinsoft.
   *
   * @param datetime $date Date of last synchronisation
   */
  public function sync($date = "") {

    $this->fplog = fopen(file_directory_path() . '/log/flux/' . date('Ymd') . '-flux.sync.log', 'a+');
    fseek($this->fplog, -1, SEEK_END);

    if (empty($date)) {
      $this->date = variable_get("flux_last_sync", time());
    }
    else {
      $this->date = $date;
    }

    $this->msglog(date('Y-m-d H:i:s') . " - Synchronisation à partir de la date " . date('Y-m-d', $this->date));

    if (date('d', $this->date) == date('d') && !$this->retreive_sync) {
      // Si la synchronisation à déjà été terminé aujourd'hui, on ne la recommence pas
      return;
    }

    $time = variable_get("flux_last_taxo_clean", time());
    if ($time < time() - 1200) {
      // Réparation et nettoyage des vocabulaires
      $this->msglog(date('Y-m-d H:i:s') . " - Nettoyage taxonomies ------------------ debut");
      module_load_include('inc', 'flux', 'flux.api');
      repair_term_node_all();
      clean_term_node_all();
      $this->msglog(date('Y-m-d H:i:s') . " - Nettoyage taxonomies ------------------ fin");
      variable_set("flux_last_taxo_clean", time());
    }

    // on met en cache les données pour éviter de les recharger
    // dans le cas où on est obliger de faire plusieurs passes pour synchroniser les données
    $this->setCache();

    $this->suspend = FALSE;

    module_load_include('inc', 'node', 'node.pages');
    //$date = strtotime(substr("2010-12-01T01:15:17.0000000+01:00", 0, 10).' '.substr("2010-12-01T01:15:17.0000000+01:00", 11, 8));

    // Parcours des flux
    $ctypes = $this->getNodeTypes();

    foreach ($this->flux as $fl) {
      if (!$this->suspend) {

        //On reprend au flux auquel on avait arrêté
        /*		  	if($this->retreive_sync && isset($this->stopedOnFlux) && $fl->idmodule!=$this->stopedOnFlux->idmodule){
                  watchdog('flux', 'Recherche de : '.$this->stopedOnFlux->title.' (Courant : '.$fl->title.')');
                  continue;
                }elseif($this->retreive_sync && isset($this->stopedOnFlux) && $fl->idmodule==$this->stopedOnFlux->idmodule){
                  watchdog('flux', 'Reprise sur : '.$fl->title);
                  $this->retreive_sync=FALSE;
                }*/

        //if(!$this->retreive_sync && strlen($fl->idmodule)>0){
        $this->currentFlux = $fl;
        if ($this->checkTime($fl, 'sync', $fl->idmodule)) {

          $this->majFlux($fl, FALSE);

          //Si une version anglaise a été renseignée, on traite aussi le flux en anglais
          if (isset($fl->idmodule_en) && is_string($fl->idmodule_en) && strlen(trim($fl->idmodule_en)) > 0) {
            $this->majFlux($fl, TRUE);
          }

          // Si la synchro n'est pas interrompue, tous les majFlux ce sont bien passés.
          // On peut supprimer leur mise en cache
          if (!$this->suspend) {
            unset($this->onprogress->majFlux);
          }
        }
        else {
          $this->msglog(date('Y-m-d H:i:s') . " - Flux non traité " . $fl->idmodule . " " . $fl->title);
        }
        //}

      }
      else {
        break;
      }
    }

    // On est arrivé au bout, on peut vider !
    if (!$this->suspend) {
      variable_set("flux_sync_data_cache", "");
      variable_set("flux_last_sync", $this->syncDateStarted);
      $this->msglog(date('Y-m-d H:i:s') . " - Synchronisation terminée ------------------");
    }
    else {
      $this->msglog(date('Y-m-d H:i:s') . " - Synchronisation suspendue. (" . date('Y-m-d', $this->syncDateStarted) . ") -----------------");
    }

    fclose($this->fplog);
  }

  public function msglog($msg) {
    if (!empty($this->fplog)) {
      fputs($this->fplog, $msg . "\r\n");
    }
  }


  /**
   * Vérifie que le temps d'exécution n'est pas dépassé.
   *
   * @param array $ctypes
   * @param array $flux
   */
  public function checkTime($flux, $action = NULL, $value = NULL, $en = FALSE) {
    if ($this->suspend) {
      return FALSE;
    }
    // Vérifie si on ne récupère pas une synchro en cours
    //if($this->retreive_sync){
    if ($en) {
      $fluxid = $flux->idmodule_en;
    }
    else {
      $fluxid = $flux->idmodule;
    }
    // On vient d'une synchro interrompue
    // Test si l'action a déjà été faite

    if (isset($this->done->{$fluxid}) && isset($this->done->{$fluxid}->{$action}) && in_array($value, $this->done->{$fluxid}->{$action})) {
      return FALSE; // Action déjà faite, on passe à la suivante
    }
    else {
      // On place l'ancienne action au statut fait
      if (isset($this->onprogress->{$action}->flux) && $this->onprogress->{$action}->value != $value) {
        if (!isset($this->done->{$this->onprogress->{$action}->flux})) {
          $this->done->{$this->onprogress->{$action}->flux} = new stdClass();
        }
        $this->done->{$this->onprogress->{$action}->flux}->{$this->onprogress->{$action}->action}[] = $this->onprogress->{$action}->value;
      }
      // L'action à réaliser est marquée en cours
      $this->onprogress->{$action}->flux   = $fluxid;
      $this->onprogress->{$action}->action = $action;
      $this->onprogress->{$action}->value  = $value;
    }

    //}

    // Vérifie que l'on ne dépasse pas le temps
    $end = microtime(TRUE);

    if ($end - $this->start > (FLUX_TIMELIMIT - 60)) { // 150 secondes = 2,5 minutes

      $this->suspend = TRUE;

      $this->setCache();

      $this->msglog('suspend TIME LIMIT : ' . $action . " : " . $value);

      watchdog('flux', 'Arrêt sur : ' . $this->cache->stopedOnFlux->title);

      return FALSE;
    }
    else {
      return TRUE;
    }
  }

  /**
   *  Create cache
   */
  public function setCache() {

    $this->cache->date            = $this->date;
    $this->cache->flux            = $this->flux;
    $this->cache->vocabs          = $this->vocabs;
    $this->cache->vocab           = $this->vocab;
    $this->cache->termCorresp     = $this->termCorresp;
    $this->cache->onprogress      = $this->onprogress;
    $this->cache->done            = $this->done;
    $this->cache->stopedOnFlux    = $this->currentFlux;
    $this->cache->suspendedSync   = ($this->suspend ? 1 : 0);
    $this->cache->listingDiff     = $this->listingDiff;
    $this->cache->syncDateStarted = $this->syncDateStarted;

    $this->flux_setBigDataCache($this->cache);
  }

  /**
   * Vérifie que le flux dispose d'un type de contenu.
   *
   * @param array $ctypes
   * @param array $flux
   */
  public function checkContentType($ctypes, $flux) {
    if (!in_array('flux_' . strtolower(trim($flux->identifiant)), $ctypes)) {
      //if($this->checkTime($flux, 'createcontenttype', $ctypes)){
      $this->createContentType($flux);
      //}
    }
  }

  /**
   * Récupère les ContentTypes de Flux.
   *
   * @return array $node_types
   */
  public function getNodeTypes() {
    // Sélection de tous les CT [Bordereau]
    // Les CT [Bordereau] sont des CT dont le nom est flux_*
    $node_types     = array();
    $node_types_all = node_get_types('names');
    foreach ($node_types_all as $node_type => $name) {
      if (preg_match('/^flux_/', $node_type)) {
        $node_types[] = $node_type;
      }
    }
    return $node_types;
  }

  /**
   * Récupère les vocabulaires liés aux flux
   *
   */
  public function loadVocabularies() {
    /* Récupération du vocabulaire et des termes pour la recherche
   *
   * Vocabulaire = Bordereau
   * Terme niveau 1 = flux
    * 	Terme niveau 2 = nom champ
    *		Terme niveau 3 = valeurs (term name: libelle, description: code, weight: ordre)
    */

    $vocabs = array();

    $vocabularies = $this->getDrupalVocabularies();

    if ($this->flux && count($this->flux) > 0) {

      // Parcours des flux et stockage des vocabulaires et/ou création
      foreach ($this->flux as $fl) {

        $this->loadSingleVocabulary($vocabs, $fl, $vocabularies, FALSE);

        if (isset($fl->idmodule_en) && is_string($fl->idmodule_en) && strlen(trim($fl->idmodule_en)) > 0) {
          $this->loadSingleVocabulary($vocabs, $fl, $vocabularies, TRUE);
        }

      }
    }

    $this->vocabs = $vocabs;
  }


  public function loadSingleVocabulary(&$vocabs, $fl, $vocabularies, $en = FALSE) {

    if (isset($vocabularies['Tourinsoft_' . $fl->identifiant . ($en ? '_en' : '')]) && !isset($vocabs[$fl->identifiant . ($en ? '_en' : '')])) {

      $vocabs[$fl->identifiant . ($en ? '_en' : '')] = $vocabularies['Tourinsoft_' . $fl->identifiant . ($en ? '_en' : '')];

      //Vérification de l'association avec le node type
      $voc       = taxonomy_vocabulary_load($vocabs[$fl->identifiant . ($en ? '_en' : '')]['vid']);
      $nodeTypes = node_get_types();
      if (isset($nodeTypes['flux_' . strtolower($fl->identifiant)]) && !isset($voc->nodes['flux_' . strtolower($fl->identifiant)])) {
        $voc->nodes['flux_' . strtolower($fl->identifiant)] = 'flux_' . strtolower($fl->identifiant);
        $voc->nodes['hqitem']                               = 'hqitem'; // On rajoute le type de contenu hqitem pour pouvoir lui attribuer les mêmes termes
        taxonomy_save_vocabulary(get_object_vars($voc));
      }

      //Suppression des doublons
      repair_term_node($vocabs[$fl->identifiant . ($en ? '_en' : '')]['vid']);

      //Nettoyage des termes vides
      clean_term_node($vocabs[$fl->identifiant . ($en ? '_en' : '')]['vid']);

    }
    else {
      if (!isset($vocabs[$fl->identifiant . ($en ? '_en' : '')])) {

        $vocabulary = array(
          'name'      => 'Tourinsoft_' . $fl->identifiant . ($en ? '_en' : ''),
          'multiple'  => 1,
          'required'  => 0,
          'hierarchy' => 1,
          'relations' => 0,
          'module'    => 'flux',
          'weight'    => -10,
          'nodes'     => array(
            'flux_' . strtolower($fl->identifiant) => 1,
            'hqitem'                               => 1
          ),
        );

        taxonomy_save_vocabulary($vocabulary);

        // Récupération de nouveau des vocabulaires
        $vocabularies = $this->getDrupalVocabularies();

        // Ajout du nouveau vocabulaire
        if (isset($vocabularies['Tourinsoft_' . $fl->identifiant . ($en ? '_en' : '')])) {
          $vocabs[$fl->identifiant . ($en ? '_en' : '')] = $vocabularies['Tourinsoft_' . $fl->identifiant . ($en ? '_en' : '')];
        }
      }
    }

    // Récupération des termes
    $tree = get_taxonomy_get_nested_tree_right((int) $vocabs[$fl->identifiant . ($en ? '_en' : '')]['vid']);

    // Vérification si le term existe
    $term = $this->isTermExist($fl->title, $tree);

    if (!isset($term->tid)) {
      // Création s'il n'existe pas
      $term = array(
        'vid'  => $vocabs[$fl->identifiant . ($en ? '_en' : '')]['vid'],
        // Voacabulary ID
        'name' => $fl->title,
        // Term Name
      );

      taxonomy_save_term($term);

      $newTid = getTid($term->vid, $term->name, 0);

      if ($newTid && is_numeric($newTid)) {
        $term = taxonomy_get_term($newTid);
      }
    }

    $vocabs[$fl->identifiant . ($en ? '_en' : '')]['terms'][$fl->title] = $term;

  }

  /**
   * Parcours des vocabulaires et stockage dans un tableau pour traitement
   *
   * @param array $vocabularies
   */
  public function getDrupalVocabularies() {
    // Parcours des vocabulaires et stockage dans un tableau pour traitement
    $vocabularies = taxonomy_get_vocabularies();
    foreach ($vocabularies as $vocab) {
      // Stock les vocabulaires déjà existant
      $vocabulariesNames[$vocab->name] = array(
        "vid"  => $vocab->vid,
        "name" => $vocab->name
      );
    }
    return $vocabulariesNames;
  }


  /**
   * Met à jour le contenu Tourinsoft à partir du flux
   *
   * @param stdClass Flux
   */
  public function majFlux($flux, $en = FALSE) {

    watchdog('flux', 'Traitement du flux ' . $flux->title . ($en ? ' version Anglaise' : ''));

    $this->msglog(date('Y-m-d H:i:s') . " - Synchronisation Flux : " . $flux->idmodule . " [" . ($en ? 'EN' : 'FR') . "] " . $flux->title);

    $this->vocab = $this->vocabs[$flux->identifiant . ($en ? '_en' : '')]['terms'][$flux->title];

    if ($this->checkTime($flux, 'majFlux', $flux->identifiant . ($en ? '_en' : ''), $en)) {

      // Récupération des données  de champ de recherche
      $this->getFieldsSearch($flux, $en);

      // Récupération des données mises à jour dans Tourinsoft
      $datas = $this->getListingDiff($flux, $en);
    } // END if (checktime(

  }


  /**
   * Webservice Tourinsoft : getFieldsSearch
   *
   * param stdClass fluxInfos
   */
  public function getFieldsSearch($fluxInfos, $en = FALSE) {

    if (!$en) {
      $resultset = $this->soap->call('getFieldsSearch', array('idModule' => $fluxInfos->idmodule));
    }
    else {
      $resultset = $this->soap->call('getFieldsSearch', array('idModule' => $fluxInfos->idmodule_en));
    }


    //On place dans termParent, le terme représentant le flux
    $termParent = $this->vocabs[$fluxInfos->identifiant . ($en ? '_en' : '')]['terms'][$fluxInfos->title];

    if (is_numeric($termParent->tid) && $resultset) {

      // Clear du dataset pour ne récupérer que les données
      $dataset = $this->clearResult($resultset);


      if (is_array($dataset) && count($dataset) > 0) {

        foreach ($dataset as $data) {

          // Seuls les éléments de type entre 7 et 19 inclus sont de type liste
          if ($data['TYPE'] >= 7 && $data['TYPE'] <= 19) {

            if ($this->checkTime($fluxInfos, 'fieldsSearch', $data['FORMFIELD_ID'], $en)) {

              // Si pas de terme de niveau 2 : création (nom du champ)
              $name = trim($data['NAME']);

              if ((!isset($termParent->children) || !find_trm_by_name_in_list($termParent->children, $name)) && !empty($name)) {

                $term = array(
                  'vid'    => $this->vocabs[$fluxInfos->identifiant . ($en ? '_en' : '')]['vid'],
                  // Voacabulary ID
                  'name'   => $name,
                  // Term Name
                  'parent' => array($termParent->tid)
                );

                taxonomy_save_term($term);

                // Il faut récupérer le tid pour pouvoir l'attribuer ensuite a ses enfants
                $newTid = getTid($this->vocabs[$fluxInfos->identifiant . ($en ? '_en' : '')]['vid'], trim($name), $termParent->tid);
                if ($newTid && is_numeric($newTid)) {
                  $term['tid']                                                                                               = $newTid;
                  $niveau2                                                                                                   = taxonomy_get_term($newTid);
                  $this->vocabs[$fluxInfos->identifiant . ($en ? '_en' : '')]['terms'][$fluxInfos->title]->children[$newTid] = $niveau2;
                }
                else {
                  drupal_set_message('L\'enregistrement de ' . $term['name'] . ' a échoué.', 'error');
                }

              }
              else {
                $niveau2 = find_trm_by_name_in_list($termParent->children, $name);
              }

              // Récupération des valeurs du champ
              $elements = $this->getListElements($fluxInfos, $data['FORMFIELD_ID'], $data['FORMFIELD_PARENT'], $en);

              if (!isset($niveau2->children)) {
                $niveau3 = array();
              }
              else {
                $niveau3 = $niveau2->children;
              }

              // Parcours des valeurs
              if (!empty($elements) && (is_array($elements) || is_object($elements))) {

                foreach ($elements as $element) {
                  $libelle = trim($element['LIBELLE']);

                  // Si la valeur existe déjà dans les termes de niveau 3, vérifie s'il faut modifier le libellé.
                  if ($value = $this->isTermExistByDesc($element['CODE'], $niveau3)) {

                    if ($value->name != $libelle || $value->weight != $element['ORDRE']) {
                      $valuename     = $libelle;
                      $value->weight = $element['ORDRE'];

                      $term = get_object_vars($value); // taxonomy_save_term() get array only

                      taxonomy_save_term($term);

                    }

                  }
                  elseif (!empty($libelle)) {

                    // S'il n'existe pas, on le créée
                    // Terme niveau 3 = valeurs (term name: libelle, description: code, weight: ordre)
                    $value = array(
                      'vid'         => $this->vocabs[$fluxInfos->identifiant . ($en ? '_en' : '')]['vid'],
                      // Voacabulary ID
                      'name'        => $libelle,
                      // Term Name
                      'description' => $element['CODE'],
                      'parent'      => array($niveau2->tid),
                      'weight'      => $element['ORDRE']
                    );

                    taxonomy_save_term($value);

                    $newTid = getTidByDescription($this->vocabs[$fluxInfos->identifiant . ($en ? '_en' : '')]['vid'], $element['CODE'], $niveau2->tid);

                    if ($newTid && is_numeric($newTid)) {
                      $value['tid'] = $newTid;
                      $value        = taxonomy_get_term($newTid);
                      $niveau3[]    = $value;
                    }
                    else {
                      drupal_set_message('L\'enregistrement de ' . $value['name'] . ' a échoué.', 'error');
                    }
                  }

                  if ($value && isset($value->tid)) {
                    $this->vocabs[$fluxInfos->identifiant . ($en ? '_en' : '')]['terms'][$fluxInfos->title]->children[$niveau2->tid]->children[$value->tid] = $value;
                  }

                }
                //Fin foreach($element
              }
              //Fin if empty($elements
            }
            //Fin if($this->checkTime($fluxInfos
            else {
              break;
            }
          }
          //Fin if($data['TYPE'] >= 7
        }
        //Fin foreach($dataset
      }
      //Fin if(is_array($dataset)
    }
    //Fin if resultset

  }


  /**
   * Webservice Tourinsoft : getListingDiff
   *
   * param stdClass fluxInfos
   */
  public function getListingDiff($fluxInfos, $en = FALSE) {

    $fieldsConf = flux_fieldsmapping($fluxInfos->identifiant);

    watchdog('flux', 'Date : ' . date('d/M/Y h:i:s', $this->date) . ' ' . $this->date . ' ' . ($en ? $fluxInfos->idmodule_en : $fluxInfos->idmodule));

    if ($this->retreive_sync && $this->listingDiff) { // On ne re-télécharge pas tout si la précédente synchronisation n'a pas été finie

      $this->msglog(date('Y-m-d H:i:s') . " - Utilisation du listingDiff du cache");
      $resultset = $this->listingDiff;
    }
    else {
      if (!$en) {
        $resultset = $this->soap->call('getListingDiff', array(
          'idModule' => $fluxInfos->idmodule,
          'date'     => $this->date
        ));
      }
      else {
        $resultset = $this->soap->call('getListingDiff', array(
          'idModule' => $fluxInfos->idmodule_en,
          'date'     => $this->date
        ));
      }
      $this->listingDiff = $resultset;
    }

    $fluxid = $fluxInfos->idmodule;
    if ($en) {
      $fluxid = $fluxInfos->idmodule_en;
    }

    $traitements = array(
      'creation' => array(),
      'maj'      => array(),
      'none'     => array(),
      'error'    => array()
    );

    if ($this->checkTime($fluxInfos, 'getListingDiff_TourinsoftCall', $fluxid, $en)) {

      $dataset = FALSE;
      if ($resultset) {
        // Clear du dataset pour ne récupérer que les données
        $dataset = $this->clearResultListingDiff($resultset);
      }

      //$it = 0;
      //$nbMax=1500;

      if (is_array($dataset) && count($dataset) > 0) {
        // Liste les fiches a mettre à jour
        foreach ($dataset as $dataList) {
          //if($it<$nbMax){
          if ($this->checkTime($fluxInfos, 'getListingDiff_dataWork', $dataList['ID'], $en)) {

            $datecrea = strtotime(substr($dataList['DATECREA'], 0, 10) . ' ' . substr($dataList['DATECREA'], 11, 8));
            $datemaj  = strtotime(substr($dataList['DATEMAJ'], 0, 10) . ' ' . substr($dataList['DATEMAJ'], 11, 8));


            if ($datecrea > $this->date || $datemaj > $this->date) {

              if ($fluxInfos->identifiant <> $dataList['OBJETTOUR_CODE']) {

                $this->msglog(date('Y-m-d H:i:s') . " OBJETTOUR_CODE différent entre flux (" . $fluxInfos->identifiant . ") et produit (" . $dataList['OBJETTOUR_CODE'] . ") pour le flux $fluxid et le produit " . $dataList['ID']);
                $traitements['error'][] = $dataList['ID'];
              }
              else {
                $this->majProduct($dataList, $traitements, $fluxInfos, $fieldsConf, $en, $datemaj);
              }

            }
            else {
              $traitements['none'][] = $dataList['ID'];
            }
            //  $it++;
            //}else{
            //  break;
            //}
          } // END if(checkTime
          if ($this->suspend) {
            break;
          }

        } // END foreach($dataset
      } // END if(is_array($dataset
    } // END if(chekTime
    // Suppression de onprogress pour getListingDiff_TourinsoftCall si celui-si est terminé
    if (!$this->suspend) {
      unset($this->onprogress->getListingDiff_TourinsoftCall);
      unset($this->listingDiff); // Suppression des produits du flux à mettre à jour
    }

    if (empty($traitements['creation'])) {
      $traitements_creation = '';
    }
    else {
      $traitements_creation = implode(', ', $traitements['creation']);
    }
    if (empty($traitements['maj'])) {
      $traitements_maj = '';
    }
    else {
      $traitements_maj = implode(', ', $traitements['maj']);
    }
    if (empty($traitements['none'])) {
      $traitements_none = '';
    }
    else {
      $traitements_none = implode(', ', $traitements['none']);
    }
    if (empty($traitements['error'])) {
      $traitements_error = '';
    }
    else {
      $traitements_error = implode(', ', $traitements['error']);
    }

    $nbResultats = sizeof($traitements['creation']) + sizeof($traitements['maj']);

    $this->msglog(date('Y-m-d H:i:s') . " - Flux " . $fluxInfos->identifiant . " " . ($en ? "[EN]" : "[FR]") . " : ");
    $this->msglog("Traitement de $nbResultats resultats");
    if (!empty($traitements_creation)) {
      $this->msglog("création : " . $traitements_creation);
    }
    if (!empty($traitements_maj)) {
      $this->msglog("mise à jour : " . $traitements_maj);
    }
    if (!empty($traitements_none)) {
      $this->msglog('Aucune maj : ' . sizeof($traitements['none']) . ' résultats : ' . $traitements_none);
    }
    if (!empty($traitements_error)) {
      $this->msglog('Erreur : ' . sizeof($traitements['error']) . ' résultats : ' . $traitements_error);
    }

    watchdog('flux', 'Flux ' . $fluxInfos->identifiant . ($en ? ' version Anglaise' : '') . ' : Traitement de ' . sizeof($traitements['creation']) + sizeof($traitements['maj']) . ' resultats : création : ' . $traitements_creation . ' | mise à jour : ' . $traitements_maj);
  }


  public function majProduct($dataList, &$traitements, $fluxInfos, $fieldsConf, $en = FALSE, $datemaj = "") {
    if (empty($datemaj)) {
      $datemaj = time();
    }
    // Récupère le détail de la fiche a mettre à jour
    $data = $this->getDetail($fluxInfos, $dataList, $en);

    if (!$data || empty($data)) {
      drupal_set_message(date('Y-m-d H:i:s') . " La fiche n'existe plus ou le webservice n'a pas repondu (" . $fluxInfos->identifiant . ") produit (" . $dataList['OBJETTOUR_CODE'] . ") pour le flux $fluxid et le produit " . $dataList['ID']);

      $this->msglog(date('Y-m-d H:i:s') . " La fiche n'existe plus ou le webservice n'a pas repondu (" . $fluxInfos->identifiant . ") produit (" . $dataList['OBJETTOUR_CODE'] . ") pour le flux $fluxid et le produit " . $dataList['ID']);
      return FALSE;
    }

    if (!isset($this->vocab) || empty($this->vocab)) {
      $this->vocab = $this->vocabs[$fluxInfos->identifiant . ($en ? '_en' : '')]['terms'][$fluxInfos->title];
    }

    // Vérifie l'existence d'un node identique (éviter les doublons)
    $nid = $this->nodeExists($data['ID'], 'flux_' . strtolower($fluxInfos->identifiant), $en);
    if (!$nid) { // Création uniquement si la fiche n'existe pas deja dans drupal
      $this->createData($data, $fluxInfos, $fieldsConf, $en);
      $traitements['creation'][] = $dataList['ID'];
    }
    elseif ($datemaj > $this->date) {
      $this->updateData($data, $fluxInfos, $nid, $fieldsConf, $en);
      $traitements['maj'][] = $dataList['ID'];
    }
  }

  /**
   * Webservice Tourinsoft : getDetail
   *
   * @param stdClass fluxInfos
   * @param array    dataList
   * @return array data
   */
  public function getDetail($fluxInfos, $dataList, $en = FALSE) {
    if (!$en) {
      $resultset = $this->soap->call('getDetail', array(
        'idModule'       => $fluxInfos->idmodule,
        'idOffre'        => $dataList['ID'],
        'OBJETTOUR_CODE' => strtoupper($fluxInfos->identifiant)
      ));
    }
    else {
      $resultset = $this->soap->call('getDetail', array(
        'idModule'       => $fluxInfos->idmodule_en,
        'idOffre'        => $dataList['ID'],
        'OBJETTOUR_CODE' => strtoupper($fluxInfos->identifiant)
      ));
    }

    if (isset($resultset['faultcode'])) {
      return FALSE;
    }

    $dataset = $this->clearResult($resultset);
    //exit;
    return $dataset;
  }

  /**
   * Webservice Tourinsoft : getListElements
   *
   * @param stdClass fluxInfos
   * @param string   formfield_id
   * @param string   valeur_parent
   * @return array data
   */
  public function getListElements($fluxInfos, $formfield_id, $valeur_parent = "", $en = FALSE) {
    if (!$en) {
      $resultset = $this->soap->call('getListElements', array(
        'idModule'      => $fluxInfos->idmodule,
        'FORMFIELD_ID'  => $formfield_id,
        'VALEUR_PARENT' => $valeur_parent
      ));
    }
    else {
      $resultset = $this->soap->call('getListElements', array(
        'idModule'      => $fluxInfos->idmodule_en,
        'FORMFIELD_ID'  => $formfield_id,
        'VALEUR_PARENT' => $valeur_parent
      ));
    }


    if (isset($resultset['faultcode'])) {
      return FALSE;
    }
    $dataset = $this->clearResult($resultset);
    // Si le tableau contient la clé CODE au premier niveau, il faut rajouter une profondeur
    if (isset($dataset['CODE'])) {
      $dataset = array($dataset);
    }

    return $dataset;
  }

  /**
   * Clear resultset to return only dataset
   *
   * @param array $result
   * @return array $dataset
   */
  public function clearResultListingDiff($result) {
    $result  = reset($result);
    $dataset = $result['diffgram'];
    if (is_array($dataset) || is_object($dataset)) {
      $dataset = reset($dataset);
    }
    if (is_array($dataset) || is_object($dataset)) {
      $dataset2 = $dataset;
      $dataset2 = reset($dataset2);
      if (isset($dataset2['0'])) {
        $dataset = $dataset2;
      }
      //$dataset = reset($dataset);
    }
    return $dataset;
  }

  public function clearResult($result) {
    if (is_array($result) || is_object($result)) {
      $result  = reset($result);
      $dataset = $result['diffgram'];
      if (is_array($dataset) || is_object($dataset)) {
        $dataset = reset($dataset);
      }
      if (is_array($dataset) || is_object($dataset)) {
        $dataset = reset($dataset);
      }

      return $dataset;
    }
    return FALSE;
  }

  /**
   * Create node Data in Content Type
   *
   * @param array    $data
   * @param stdClass $fluxInfos
   * @return boolean
   */
  public function createData($data, $fluxInfos, $fieldsConf, $en = FALSE) {

    $nb = db_result(db_query("SELECT count(*) FROM {node_type} WHERE type='%s'", 'flux_' . strtolower($data['OBJETTOUR_CODE'])));
    if (!$nb || $nb <= 0) {
      drupal_set_message('Le type de contenu "' . 'flux_' . strtolower($data['OBJETTOUR_CODE']) . '" n\'existe pas, le flux ne peut être importé.', 'error');
      return FALSE;
    }

    if (!$fluxInfos || !isset($fluxInfos->nid)) {
      drupal_set_message('Un problème a été rencontré lors de la mise à jour des données.', 'error');
      return FALSE;
    }

    $node       = new stdClass();
    $node->type = 'flux_' . strtolower($data['OBJETTOUR_CODE']);


    $node->uid       = '1';
    $node->name      = 'admin';
    $node->status    = '1';
    $node->created   = ($this->getDateFromCBIS($data['DATECREA'])) ? $this->getDateFromCBIS($data['DATECREA']) : time();
    $node->timestamp = ($this->getDateFromCBIS($data['DATECREA'])) ? $this->getDateFromCBIS($data['DATECREA']) : time();
    $node->changed   = ($this->getDateFromCBIS($data['DATEMAJ'])) ? $this->getDateFromCBIS($data['DATEMAJ']) : $node->created;
    $node->comment   = '0';
    $node->promote   = '1';
    $node->moderate  = '0';
    $node->sticky    = '0';

    //------ GESTION DE LA LANGUE ----------
    if (!$en) {
      $node->language = 'fr';
    }
    else {
      $node->language = 'en';
    }
    if ($en) {
      //On cherche si la version française existe
      $nid = $this->nodeExists($data['ID'], 'flux_' . strtolower($fluxInfos->identifiant), FALSE);
      if ($nid) {
        $node->tnid = '' . $nid;
      }
      else {
        $node->tnid = $node->nid;
      }
    }
    else {
      //On cherche si la version anglaise existe
      $nid = $this->nodeExists($data['ID'], 'flux_' . strtolower($fluxInfos->identifiant), TRUE);
      if ($nid) {
        $node->tnid = '' . $nid;
      }
      else {
        $node->tnid = $node->nid;
      }
    }

    $node->translate    = '0';
    $node->revision_uid = $node->uid;

    $node->field_fl_nid_tx[0]['value']          = $fluxInfos->nid;
    $node->field_fl_id_bordereau_tx[0]['value'] = $fluxInfos->identifiant;
    $node->field_fl_id_module_tx[0]['value']    = ($en ? $fluxInfos->idmodule_en : $fluxInfos->idmodule);
    $node->field_fl_techid_tx[0]['value']       = $data['ID'];

    if (module_exists('domain')) {
      $node->domains     = array('-1' => -1);
      $node->domain_site = TRUE;
    }

    $fields = array();

    $success = TRUE;


    //Pour traiter les champs paramétrés, on prend la conf DANS L'ORDRE OU ELLE EST DONNEE (issu de flux_fieldsmapping)

    $ws_field_names = array_keys($fieldsConf);
    $ws_fields      = array_keys($data);

    for ($i = 0; $i < count($ws_field_names) && $success; $i++) {

      $prevName = $ws_field_names[$i];
      $name     = substr($prevName, 0, 21);
      $value    = $data[$prevName];

      if (intval($fieldsConf[$prevName]->required) === 1) {
        if (!in_array($prevName, $ws_fields)) {
          watchdog($prevName . 'N\'est pas dans la liste des champs du flux "' . $fluxInfos->identifiant . '".');
        }
      }

      //Si le champ est requis et vide, alors, on arrête tout
      if (strlen(trim($value)) <= 0 && intval($fieldsConf[$prevName]->required) === 1) {
        $success = FALSE;
        watchdog('flux', 'Le champ requis "' . $prevName . '" est vide : "' . $data[$prevName] . '". Bordereau : ' . $fluxInfos->identifiant . ' FicheID : !fiche', array('!fiche' => $data['ID']), WATCHDOG_ERROR);

      }
      else {
        $function = $fieldsConf[$prevName]->fieldfunction . '_fluxfieldvalue';

        if (function_exists($function)) {

          $defaultVals = array();

          //Image par défaut
          if ($fluxInfos->fid != NULL) {
            $defaultVals['fid'] = $fluxInfos->fid;
          }

          $function($node, $fieldsConf[$prevName]->cckfieldname, $value, $defaultVals);

        }
        else {

          drupal_set_message('La fonction "' . $function . '()" n\'existe pas.', 'error');
        }

        //---------- GESTION DE LA TAXONOMIE ------------------
        //On récupère le TID du champ courant
        $nameToSearch = $name;
        if ($name == 'EQUIPEMENTS') { // Cas des flux qui ont un nom de champ différent du moteur de recherche
          $nameToSearch = 'EQUIPEMENT';
        }
        elseif ($name == 'CLASSEMENT_LABEL') {
          $nameToSearch = 'CLASSEMENT';
        }
        elseif ($name == 'DESC_HABITATION') {
          $nameToSearch = 'DESCRIPTIF_HABITATION';
        }

        $currentTerm = find_trm_by_name_in_list($this->vocab->children, $nameToSearch);

        //Si le terme est dans la liste des termes "CHAMP" de la branche du vocabulaire associé au flux, on met à jour les termes
        if ($currentTerm && isset($this->vocab->children[$currentTerm->tid])) { // Si le champ existe dans la taxonomy du type de contenu

          //On récupère la liste des termes possibles
          $terms = $this->vocab->children[$currentTerm->tid]->children;

          // Sélection des termes correspondant aux valeurs du champ
          $values = explode("#", $value);
          foreach ($values as $val) {
            $val  = trim($val);
            $term = find_trm_by_name_in_list($terms, $val);
            if ($term && !in_array($term->tid, $fields) && !isset($node->taxonomy[$term->tid])) {
              $fields[$term->tid] = $term->tid;
            }
          }
        }
      }

    }

    foreach (module_implements('flux_alterdata') as $module) {
      $func = $module . '_flux_alterdata';
      $func($node);
    }

    //Si aucun champ n'a bloqué le process
    if ($success) {
      // ajout du term principal pour connaitre le flux grace a la taxo
      if (!isset($node->taxonomy[$this->vocab->tid])) {
        $fields[$this->vocab->tid] = $this->vocab->tid;
      }


      if (!empty($fields) && is_array($fields)) {
        foreach ($fields as $tid) {
          if (!isset($node->taxonomy[$tid])) {
            $taxo                 = new stdClass();
            $taxo->tid            = $tid;
            $taxo->vid            = $vocab_temp['vid'];
            $node->taxonomy[$tid] = $taxo;
          }
        }
      }

      $node = node_submit($node);

      node_save($node);

      return TRUE;
    }

    return FALSE;
  }

  /**
   * Update node Data in Content Type
   *
   * @param array $data
   * @param int   $nid
   * @return boolean
   */
  public function updateData($data, $fluxInfos, $nid, $fieldsConf, $en = FALSE) {
    $node = node_load($nid);

    $node->taxonomy = array();

    $fields = array();

    $success = TRUE;

    if ($node->tnid == 0) {
      $node->tnid = $node->nid;
    }
    else {
      if ($en) {
        //On cherche si la version française existe
        $nid = $this->nodeExists($data['ID'], 'flux_' . strtolower($fluxInfos->identifiant), FALSE);
        if ($nid) {
          $node->tnid = '' . $nid;
        }
        else {
          $node->tnid = '' . $node->nid;
        }
      }
      else {
        //On cherche si la version anglaise existe
        $nid = $this->nodeExists($data['ID'], 'flux_' . strtolower($fluxInfos->identifiant), TRUE);
        if ($nid) {
          $node->tnid = '' . $nid;
        }
        else {
          $node->tnid = '' . $node->nid;
        }
      }
    }

    $ws_field_names = array_keys($fieldsConf);
    $ws_fields      = array_keys($data);

    for ($i = 0; $i < count($ws_field_names) && $success; $i++) {

      $prevName = $ws_field_names[$i];
      $name     = substr($prevName, 0, 21);
      $value    = $data[$prevName];

      if (intval($fieldsConf[$prevName]->required) === 1) {
        if (!in_array($prevName, $ws_fields)) {
          watchdog($prevName . 'N\'est pas dans la liste des champs du flux "' . $fluxInfos->identifiant . '".');
        }
      }

      //Si le champ est requis et vide, alors, on arrête tout
      if (strlen(trim($value)) <= 0 && intval($fieldsConf[$prevName]->required) === 1) {
        $success = FALSE;
        watchdog('flux', 'Le champ requis "' . $prevName . '" est vide : "' . $data[$prevName] . '". Bordereau : ' . $fluxInfos->identifiant . ' FicheID : !fiche', array('!fiche' => $data['ID']), WATCHDOG_ERROR);

      }
      else {
        $function = $fieldsConf[$prevName]->fieldfunction . '_fluxfieldvalue';
        if (function_exists($function)) {


          $defaultVals = array();

          //Image par défaut
          if ($fluxInfos->fid != NULL) {
            $defaultVals['fid'] = $fluxInfos->fid;
          }

          $function($node, $fieldsConf[$prevName]->cckfieldname, $value, $defaultVals);

        }
        else {
          drupal_set_message('La fonction "' . $function . '()" n\'existe pas.', 'error');
        }

        //---------- GESTION DE LA TAXONOMIE ------------------
        //On récupère le TID du champ courant
        $nameToSearch = $name;
        if ($name == 'EQUIPEMENTS') { // Cas des flux qui ont un nom de champ différent du moteur de recherche
          $nameToSearch = 'EQUIPEMENT';
        }
        elseif ($name == 'CLASSEMENT_LABEL') {
          $nameToSearch = 'CLASSEMENT';
        }
        elseif ($name == 'DESC_HABITATION') {
          $nameToSearch = 'DESCRIPTIF_HABITATION';
        }

        $currentTerm = find_trm_by_name_in_list($this->vocab->children, $nameToSearch);

        //Si le terme est dans la liste des termes "CHAMP" de la branche du vocabulaire associé au flux, on met à jour les termes
        if ($currentTerm && isset($this->vocab->children[$currentTerm->tid])) { // Si le champ existe dans la taxonomy du type de contenu
          //On récupère la liste des termes possibles
          $terms = $this->vocab->children[$currentTerm->tid]->children;

          // Sélection des termes correspondant aux valeurs du champ
          $values = explode("#", $value);
          if ($name == 'LABEL_TH' && sizeof($values) < 2) {
            $values = explode('-', $value);
          }
          foreach ($values as $val) {
            $val  = trim($val);
            $term = find_trm_by_name_in_list($terms, $val);
            if ($term && !in_array($term->tid, $fields) && !isset($node->taxonomy[$term->tid])) {
              $fields[$term->tid] = $term->tid;
            }
          }
        }
      }
    }

    if ($success) {
      $vocab_temp = array();
      if (is_object($this->vocab)) {
        $vocab_temp = get_object_vars($this->vocab);
      }
      else {
        $vocab_temp = $this->vocab;
      }

      if (!isset($node->taxonomy[$vocab_temp['tid']])) {
        // ajout du term principal pour connaitre le flux grace a la taxo
        $fields[$vocab_temp['tid']] = $vocab_temp['tid'];
      }

      if (!empty($fields) && is_array($fields)) {
        foreach ($fields as $tid) {
          if (!isset($node->taxonomy[$tid])) {
            $taxo                 = new stdClass();
            $taxo->tid            = $tid;
            $taxo->vid            = $vocab_temp['vid'];
            $node->taxonomy[$tid] = $taxo;
          }
        }
      }

      if ($node->nid && !empty($node->nid)) {
        $node = node_submit($node);

        // use dates from $data to fix created and changed dates
        $node->created = $this->getDateFromCBIS($data['DATECREA']);
        if (isset($data['DATEMAJ']) && !empty($data['DATEMAJ'])) {
          $node->changed   = $this->getDateFromCBIS($data['DATEMAJ']);
          $node->timestamp = $node->changed;
        }
        else {
          $node->changed   = $node->created;
          $node->timestamp = $node->created;
        }

        node_save($node);
      }

      return TRUE;

    }
    else {

      return FALSE;

    }
  }

  public function getDateFromCBIS($date) {
    $date_time = explode('T', $date);
    $date      = explode('-', $date_time[0]);
    if (isset($date_time[1])) {
      $time = explode('.', $date_time[1]);
      $time = explode(':', $time[0]);
      if (sizeof($time) != 3) {
        $time = array(0, 0, 0);
      }
    }
    return mktime($time[0], $time[1], $time[2], $date[1], $date[2], $date[0]);
  }


  /**
   * Vérifie l'existence d'un term en fonction de son nom
   *
   * @param string $name
   * @param array  $tree
   *
   * @return stdClass $term OR false if no term exist
   */
  function isTermExist($name, $tree) {
    if (empty($tree)) {
      return FALSE;
    }
    foreach ($tree as $term) {
      if ($term->name == $name) {
        return $term;
      }
    }
    return FALSE;
  }


  /**
   * Vérifie l'existence d'un term en fonction de sa description
   *
   * @param string $name
   * @param array  $tree
   *
   * @return stdClass $term OR false if no term exist
   */
  function isTermExistByDesc($description, $tree) {

    foreach ($tree as $term) {
      if ($term->description == $description) {
        return $term;
      }
    }
    return FALSE;
  }

  /**
   * Check if node already exist
   *
   * @param string $id
   * @return int $nid
   */
  public function nodeExists($id, $contenttype, $en = FALSE) {
    $fieldInfos = content_fields('field_fl_techid_tx', $contenttype);

    if (!$en) {
      $langcode = 'fr';
    }
    else {
      $langcode = 'en';
    }

    if (intval($fieldInfos['db_storage']) == 1) {
      $query = db_query("SELECT ct.nid FROM {content_type_%s} AS ct INNER JOIN {node} AS n ON ct.nid=n.nid WHERE field_fl_techid_tx_value = '%s' AND n.language='%s'", $contenttype, $id, $langcode);
    }
    else {
      $query = db_query("SELECT cf.nid FROM {content_field_fl_techid_tx} AS cf INNER JOIN {node} AS n ON cf.nid=n.nid WHERE field_fl_techid_tx_value = '%s' AND n.language='%s'", $id, $langcode);
    }

    if ($result = db_fetch_object($query)) {
      return $result->nid;
    }
    else {
      return FALSE;
    }
  }

  /**
   * Récupère les champs de tous les flux d'un bordereau.
   *
   * @param array $flux
   * @return array $fields
   */
  public function getFieldsByFluxIdentifiant($identifiant) {
    $fields       = array();
    $fields_exist = array();

    $query = db_query("SELECT ctf.field_flux_idmodule_value FROM {content_type_flux} ctf WHERE ctf.field_flux_identifiant_value = '%s'", array($identifiant));

    while ($result = db_fetch_object($query)) { // Pour chaque flux

      // On récupère les champs d'un flux
      $resultset = $this->soap->call('getFieldsDetail', array('idModule' => $result->field_flux_idmodule_value));

      $dataset = $this->clearResult($resultset);

      if (is_array($dataset) && count($dataset) > 0) {
        foreach ($dataset as $cle => $val) {
          // On vérifie qu'il n'est pas déjà dans la liste des flux
          if (!in_array($val['DETAILFIELD_NAME'], $fields_exist)) {
            $fields[]       = $val;
            $fields_exist[] = $val['DETAILFIELD_NAME'];
          }
        }
      }
    }
    return $fields;
  }


}

?>
