<?php
 function flux_maj_cck_fieldname($bordereauid, $wsfieldname, $cckfieldname=NULL){
  	$nb = db_result(db_query("SELECT count(*) FROM {flux_fieldsettings} WHERE bordereau_id='%s' AND fieldname='%s'", $bordereauid, $wsfieldname));
  	if($nb>0){
  		if($cckfieldname && strlen($cckfieldname)>0)
  			db_query("UPDATE {flux_fieldsettings} SET cckfieldname='%s' WHERE bordereau_id='%s' AND fieldname='%s'", $cckfieldname, $bordereauid, $wsfieldname);
  		return TRUE;
  	}
  	else{
  		return FALSE;
  	}
  }
  
  function similar_field_with_ws_fieldname($ws_fieldname){
  		$def = db_fetch_object(db_query("SELECT * FROM {flux_fieldsettings} WHERE fieldname='%s' LIMIT 1", $ws_fieldname));
  		if(is_object($def)){
  			return $def;
  		}else{
  			return FALSE;
  		}
  }
  
  /**
 *	Retourne le mapping entre 
 *	ws_fieldname (le champ du webservice)
 *	flux_fieldlabel(le libellé attribué)
 *	flux_function (la fonction à utiliser)
 *
 *	@return array
 */
function flux_fieldsmapping($fluxid){
	$query = db_query("SELECT * FROM {flux_fieldsettings} WHERE bordereau_id='%s' ORDER BY required DESC", $fluxid);
	$mapping = array();
	while($result = db_fetch_object($query)){
		$mapping[$result->fieldname] = $result;
	}
	return $mapping;
}

function flux_fieldsdisplay($fluxid){
	$query = db_query("SELECT di.* FROM {flux_display} AS di LEFT JOIN {flux_fieldsettings} AS st ON st.bordereau_id=di.bordereau_id AND st.cckfieldname=di.cckfieldname WHERE di.bordereau_id='%s' AND NOT(st.staticfield=1) ORDER BY  di.zone ASC, di.weight ASC", $fluxid);
	$mapping = array();
	while($result = db_fetch_object($query)){
		$mapping[$result->cckfieldname] = $result;
	}
	return $mapping;
}

/**
   * Récupère la liste des flux
   *
   * @return stdClass flux {nid, idmodule, identifiant}
   */
  function loadFluxInfos($fluxInfos = array()){
  	$flux = new stdClass();

    $where = "";

    if(!empty($fluxInfos)){
      $where = " AND field_flux_idmodule_".(($fluxInfos->en)?"en_":"")."value='". $fluxInfos->idmodule ."'";
    }
    
  	$query = db_query("SELECT ctf.nid as nid, field_flux_idmodule_value as idmodule, field_flux_idmodule_en_value as idmodule_en, field_flux_identifiant_value as identifiant, n.title as title, ctf.field_default_img_fid as fid FROM {content_type_flux} ctf INNER JOIN {node} n ON n.vid=ctf.vid WHERE n.status=1".$where);
  	
  	while($result = db_fetch_object($query)){
  		$flux->{$result->nid} = $result;
  	}
  	return $flux;
  }
  
  /**
   * Webservice Tourinsoft : getTid
   *
   * param int vid
   * param string name
   * param int parent
   *
   * @return int tid
   */
  function getTid($vid, $name, $parent){
  	$query = db_query("SELECT DISTINCT td.tid FROM {term_data} td INNER JOIN {term_hierarchy} th ON th.tid=td.tid WHERE td.vid=%d AND td.name='%s' AND th.parent = %d", array($vid, $name, $parent));
		if($result = db_fetch_object($query)){
			return $result->tid;
		}
		return "";
  }
  
 /**
   * Webservice Tourinsoft : getTid
   *
   * param int vid
   * param string name
   * param int parent
   *
   * @return int tid
   */
  function getTidByDescription($vid, $description, $parent){
  	$query = db_query("SELECT DISTINCT td.tid FROM {term_data} td INNER JOIN {term_hierarchy} th ON th.tid=td.tid WHERE td.vid=%d AND td.description='%s' AND th.parent = %d", array($vid, $description, $parent));
		if($result = db_fetch_object($query)){
			return $result->tid;
		}
		return "";
  }
  
  /**
   * Supprime les doublons dans un vocabulaire : doublons sur description sur termes de niveau 3
   */
  function repair_term_node($vid){
    $tree = get_taxonomy_get_nested_tree_right(intval($vid));
    
  	if(is_array($tree) && count($tree)>0){
	  	foreach($tree as $nivo1){
	  		$nivo1Children = $tree->children;
	  		
	  		if(isset($nivo1Children) && count($nivo1Children)>0){
	  		
	  			foreach($nivo1Children as $nivo2){
	  				
	  				$nivo2Children = $nivo2->children;
	  				
	  				if($nivo2Children && count($nivo2Children)>0){
	  					foreach($nivo2Children as $nivo3){
	  						
	  						//Pour chaque item de niveau 3
	  						$nb = db_result(db_query("SELECT count(*) FROM {term_data} WHERE tid=%d", intval($nivo3->tid)));
	  						//Si le term n'a pas été supprimé par une précédente itération
	  						if($nb && $nb>0){
	  							/*
	  							$nb2 = db_result(db_query("SELECT count(*) FROM {term_data} AS td LEFT JOIN {term_hierarchy} AS th ON th.tid=td.tid WHERE th.parent=%d AND td.description='%s' AND NOT(td.tid=%d)", intval($nivo3->parents[0]), $nivo3->description, intval($nivo3->tid)));
	  							*/
	  							//On cherche les autres terms qui ont le même code (description) et le même père
	  							$res = db_query("SELECT td.* FROM {term_data} AS td LEFT JOIN {term_hierarchy} AS th ON th.tid=td.tid WHERE th.parent=%d AND td.description='%s' AND NOT(td.tid=%d)", intval($nivo3->parents[0]), $nivo3->description, $nivo3->tid);
	  							
	  							//Pour chaque doublon trouvé, on réaffecte les nodes au bon terme puis on supprime le doublon
	  							while($item = db_fetch_object($res)){
	  								db_query("UPDATE {term_node} SET tid=%d WHERE tid=%d", intval($nivo3->tid), intval($item->tid));
	  								taxonomy_del_term($item->tid);
	  								watchdog('flux', 'Le terme '.$item->name.' est un doublon et a été supprimé. Tous les nodes ont été basculés sur le terme connexe non doublon.');
	  							}
	  							
	  						}
	  					}//Fin foreach($nivo2->children
	  				}//Fin if($nivo2->children &
	  				
	  			}//Fin foreach($nivo1->children as
	  		}//Fin if($nivo1->children
	  		
	  	}//Fin foreach($tree as
	 }//Fin if($tree->children &
	 
  }
  
  /**
   * Function from http://api.drupal.org/api/drupal/modules--taxonomy--taxonomy.module/function/taxonomy_get_tree/6 to get real taxonomy tree
   *
   */
  function get_taxonomy_get_nested_tree($terms = array(), $max_depth = NULL, $parent = 0, $parents_index = array(), $depth = 0) {
	 
	  if (is_int($terms)) {
	    $terms = taxonomy_get_tree($terms);
	  }
	  
	  foreach($terms as $term) {
	  	if(!is_array($term)){
	  		$term = get_object_vars($term);
	  	}
	  	$termCorresp[$term['tid']] = $term['name'];
	    foreach($term['parents'] as $term_parent) {
	      if ($term_parent == $parent) {
	        $return[$term['name']] = $term;
	      }
	      else {
	        $parents_index[$termCorresp[$term_parent]][$term['name']] = $term;
	      }
	    }
	  }
	  
	  if(!empty($return)){
		  foreach($return as &$term) {
		    if (isset($parents_index[$term['name']]) && (is_null($max_depth) || $depth < $max_depth)) {
		      $term['children'] = get_taxonomy_get_nested_tree($parents_index[$term['name']], $max_depth, $term['tid'], $parents_index, $depth + 1);
		    }
		  }
		}	  
	  return $return;
	}
  
  
  /**
   * Function from http://api.drupal.org/api/drupal/modules--taxonomy--taxonomy.module/function/taxonomy_get_tree/6 to get real taxonomy tree
   *
   */
  function get_taxonomy_get_nested_tree_right($terms = array()) {
	 
	  //Chargement du premier niveau
	  if (is_int($terms)) {
	    $primterms = taxonomy_get_tree($terms,0, -1, 1);
	    $terms=array();
	    if(is_array($primterms) && count($primterms)>0){
		    foreach($primterms as $term){
		    		$terms[$term->tid]=$term;
		    }
	    }
	  }
	  if(is_array($terms) && count($terms)>0){
	  	
	  	foreach($terms as $tid => $term){
	  		
	  		$children = taxonomy_get_children($term->tid);
	  		
	  		if(is_array($children) && count($children)>0){
	  			
	  			$retour = get_taxonomy_get_nested_tree_right($children);
	  			
	  			$terms[$tid]->children=$retour;
	  			
	  		}
	  		
	  	}
	  	
	  }
	  return $terms;
	}
	
	/*
	* Recherche un terme dans une liste par son nom
	*/
	function find_trm_by_name_in_list($terms, $name){
		if(is_array($terms) && count($terms)>0 && is_string($name) && strlen($name)>0){
			foreach($terms as $term){
				if($term->name == $name){
					return $term;
				}
			}
		}
		return FALSE;
	}
