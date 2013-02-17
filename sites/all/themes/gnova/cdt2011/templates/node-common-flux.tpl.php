<?php if ($ubox_resume): ?>

  <div class="ubox_item_content">
    <h3><a href="<?php print $node_url ?>"><?php print $title; ?></a></h3>
    <?php echo $content; ?>
    <a href="<?php print $node_url ?>"><?php print t('More') ?></a>
  </div>

  <?php print $picture ?>

<?php else: ?>

  <div class="box_categories node <?php print $classes; ?> all" id="node-<?php print $node->nid; ?>">
    <div class="finistere-title">
      <?php if ($teaser): ?>
        <h2 class="title">
          <a href="<?php print $node_link; ?>"><?php print $title; ?></a>
        </h2>
      <?php else: ?>
        <h1 class="title">
          <?php
          print $title;
          if (!empty($field_fl_categorie_strs)) {
            print cdt2011_term_to_img($field_fl_categorie_strs[0]['value'], ' - ');
          }
          if (!empty($field_fl_classement_label_strs)) {
            print cdt2011_term_to_img($field_fl_classement_label_strs[0]['value'], ' - ');
          }
          ?>
        </h1>
        <?php if ($add_carnet_link) { print $add_carnet_link; } ?>
        <?php
        if (!empty($field_fl_attente_classeme)) {
          print '<div class="attente-classement">' . $field_fl_attente_classeme[0]['value'] . '</div>';
        }
        ?>
      <?php endif; ?>
    </div>

    <div class="uboxpb_items">
      <div class="uboxpb_items_left">
        <?php
        if (!isset($field_fl_adherent_cdt_tx[0]['value'])) {
          $field_fl_adherent_cdt_tx[0]['value'] = 'oui';
        }
        if ($field_fl_adherent_cdt_tx[0]['value'] == 'oui') {
          print $field_fl_photos_imgs_rendered;
        }
        elseif ($field_fl_photos_imgs[0]['filepath']) {
          // display only first image
          print theme('imagecache', 'bp_detail_big', $field_fl_photos_imgs[0]['filepath'], $node->title, $node->title);
        }
        if (FALSE && $field_fl_tarif_min[0]['view'] && $field_fl_adherent_cdt_tx[0]['value'] == 'oui'):
        ?>
        <div class="c_prix">
          <span class="border left_b"></span>
          <?php print $field_fl_tarif_min[0]['view']; ?>
          <span class="border right_b"></span>
        </div>
        <?php endif; ?>

        <div class="uboxbp_content">
          <div class="uboxpb_items_content addresszone">
            <?php
            print $addresszone;
            global $user;
            if ($field_fl_adherent_cdt_tx[0]['value'] == 'oui') {
              //print $addresszone;
              if ($field_fl_visite_virtuelle_tx[0]['value'] && $field_fl_visite_virtuelle_tx[0]['value'] != NULL) {
                global $theme_path;
                drupal_add_js('$("#virtual").colorbox({iframe:true, width:"600px", height:"430px"});', 'inline');
                print '<div class="virtual-visit">' . l(t('Virtual visit'), $field_fl_visite_virtuelle_tx[0]['value'], array('html'       => TRUE,
                                                                                                                             'attributes' => array('id' => 'virtual')
                )) . '</div>';
              }
            }
            ?>
          </div>
          <?php if (count($field_fl_tarif_label) > 0 && strlen($field_fl_tarif_label[0]['view']) > 0 && $field_fl_adherent_cdt_tx[0]['value'] == 'oui') : ?>
            <h4 class="lower"><?php print t('Prices'); ?></h4>
            <table id="table_tarif">
              <tr>
                <td class="no_border"></td>
                <td class="grey"><?php print t('Min');?></td>
                <td class="grey"><?php print t('Max');?></td>
              </tr>
              <?php
              $i = 0;
              foreach ($field_fl_tarif_label as $item) {
                print '<tr><td class="grey">' . $item['view'] . '</td><td class="grey">' . $field_fl_tarif_min[$i]['view'] . '</td><td class="grey">' . $field_fl_tarif_max[$i]['view'] . '</td></tr>';
                $i++;
              }
              ?>
            </table>
          <?php endif; ?>

          <?php if ($zone1 && $field_fl_adherent_cdt_tx[0]['value'] == 'oui'): ?>
            <div class="uboxpb_items_content">
              <?php print $zone1; ?>
            </div>
          <?php endif; ?>
        </div>

      </div>

      <div class="uboxpb_items_left">
        <div class="uboxbp_content">
          <?php
          if (($node->field_fixfl_onlineresa[0]['value'] == 'oui' || $node->field_fixfl_onlineresa[0]['value'] == 'yes') &&
            $node->field_fixfl_codemetier[0]['value'] &&
            $node->field_fixfl_codefournisseur[0]['value'] &&
            $field_fl_adherent_cdt_tx[0]['value'] == 'oui'
          ):
          ?>
          <!--DEBUT CODE WIDGET-->
          <script type="text/javascript" xml:space="preserve">

                         function loadosformscript(sScriptSrc, oCallback) {
                           var oHead = document.getElementsByTagName('head')[0];
                           var oScript = document.createElement('script');
                           oScript.type = 'text/javascript';
                           oScript.src = sScriptSrc;
                           // most browsers
                           oScript.onload = oCallback;
                           // IE 6 & 7
                           oScript.onreadystatechange = function () {
                             if (this.readyState == 'complete') {
                               oCallback();
                             }
                           }
                           oHead.appendChild(oScript);
                         }

                         function launchOSFG() {

                           //jQuery.noConflict();
                           //Passage du code de Widget Open System Hôtel: 25810-1210
                           // Correspond au formulaire de recherche de réservation du produit en cours
                           <?php
                           $code_widget   = '25810-1210';
                           $langue_widget = 'fr';
                           switch ($node->field_fl_id_module_tx[0]['value']) {
                             //Hotel
                             case '84a7ea9f-2a41-4b3a-94f6-e04c357bb3c4':
                               $code_widget = '25810-1210';
                               break;
                             // EN
                             case '5d01e7c3-116d-49c1-b9da-e3a2779c9335':
                               $code_widget   = '25810-1210';
                               $langue_widget = 'uk';
                               break;
                             //location de vacances (agences immo, cles vacances,gites de france)
                             //case 'fe61792a-5467-4aef-9d8a-3649a332bff1': // HLO Agences Immo
                             case '0bf53735-f2c6-4d02-9d42-787ef5e51c8e': // HLO-clévacances-meubles
                               //case '91e95fcb-17dc-4266-906a-d09787d55eef': // HLO Clevacances-chambres d'hotes
                               $code_widget = '25810-1211';
                               break;
                             // EN
                             //case 'f4b4b8d5-da01-48be-a6d3-f9ed16f68838': // HLO Agences Immo
                             case '819f8219-9cad-4c9f-8b7b-ef59f121c9b7': // HLO-clévacances-meubles
                               //case 'a671f62d-a664-4d0c-a3b0-c96f29ae25c6': // HLO Clevacances-chambres d'hotes
                               $code_widget   = '25810-1211';
                               $langue_widget = 'uk';
                               break;
                             //Camping
                             case '0ec8bf2d-66e3-4883-87a1-9fe4a41ee2de': // HPA-campings
                               $code_widget = '25810-1213';
                               break;
                             // EN
                             case 'bcb9cd72-3a61-4754-9502-9c1a551c8e8b': // HPA-campings
                               $code_widget   = '25810-1213';
                               $langue_widget = 'uk';
                               break;
                             //Hébergement locatif champbre
                             case '91e95fcb-17dc-4266-906a-d09787d55eef': // HLO Chambre
                               $code_widget = '25810-1212';
                               break;
                             // EN
                             case 'a671f62d-a664-4d0c-a3b0-c96f29ae25c6 ': // HLO Chambre
                               $code_widget   = '25810-1212';
                               $langue_widget = 'uk';
                               break;
                             //chambre d'hôte / gite d'étape
                             /*case 'dcd10b15-abf9-4ccc-b0e6-971aa004c998': // HLO-GitedEtape-Rando
                               $code_widget = '25810-1212';
                               break;
                             // EN
                             case '17feeb57-c16b-4ef2-ace8-24c3e4c42a26': // HLO-GitedEtape-Rando
                               $code_widget = '25810-1212';
                               $langue_widget = 'uk';
                               break;*/
                             //Résidences de tourisme
                             case 'e8471745-8b79-4ffe-8d74-7fad9474ef62': // HLO-Résidences
                               $code_widget = '25810-1315';
                               break;
                             // EN
                             case '30fe2788-f265-48d5-bb8c-f7f593365bbc': // HLO-Résidences
                               $code_widget   = '25810-1315';
                               $langue_widget = 'uk';
                               break;
                             //Village vacances
                             case 'fcbe9775-786b-4df4-8953-63801603c606': // VIL-villagesvacances
                               $code_widget = '25810-1316';
                               break;
                             // EN
                             case 'caac8cf7-5aea-4a11-a57d-2156510db9cf': // VIL-villagesvacances
                               $code_widget   = '25810-1316';
                               $langue_widget = 'uk';
                               break;
                           }
                           ?>
                           document.oswidget = new OsFG("OSRecherche", "<?php print $code_widget ?>", "<?php print $langue_widget ?>", "/<?php print path_to_theme(); ?>/css/widget.css");
                           document.oswidget.SetOptionAffichage({"Navigation":"accordeon"});
                           jQuery(function () {
                             //Passage du code unique Open System d'un hôtel, dans cet exemple: HRIT-7806
                             //Si un code produit est rensigné, on le rajoute à la fin : HRIT-7806-45
                             document.oswidget.CodeOs("<?php print $node->field_fixfl_codemetier[0]['value']; ?>-<?php print (($node->field_fixfl_codeproduit[0]['value'] && strlen($node->field_fixfl_codeproduit[0]['value']) > 0) ? $node->field_fixfl_codefournisseur[0]['value'] . '-' . $node->field_fixfl_codeproduit[0]['value'] : $node->field_fixfl_codefournisseur[0]['value']); ?>");
                             //Provoque l'affichage du Widget
                             document.oswidget.Affiche();
                           });
                         }


                         function checkJquery() {
                           if (window.jQuery) {
                             loadosformscript("http://gadget.open-system.fr/osform.min.js", launchOSFG);
                           }
                           else {
                             window.setTimeout(checkJquery, 100);
                           }
                         }

                         checkJquery();
          </script>
          <div id="OSRecherche"></div>
          <!--FIN CODE WIDGET-->

          <?php endif; ?>

          <?php if ($map): ?>
          <div class="node-map">
            <?php print $map; ?>
          </div>
          <?php endif; ?>

          <div class="uboxpb_items_content">
            <?php
            if ($field_fl_adherent_cdt_tx[0]['value'] == 'oui') {
              print $presentationzone;
            }
            ?>
          </div>

          <?php if ($zone2 && $field_fl_adherent_cdt_tx[0]['value'] == 'oui'): ?>
          <div class="uboxpb_items_content">
            <?php print $zone2; ?>
          </div>
          <?php endif; ?>

        </div>
      </div>

    </div><!-- /uboxpb_items -->

    <?php print $sharethis; ?>

  </div> <!-- /node-->

  <?php if ($links): ?>
    <div class="links clearfix"> <?php print $links; ?></div>
  <?php endif; ?>

<?php endif; /* /ubox_simple */ ?>