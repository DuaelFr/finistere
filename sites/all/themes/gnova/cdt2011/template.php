<?php

// Auto-rebuild the theme registry during theme development.
if (theme_get_setting('cdt2011_rebuild_registry')) {
  drupal_rebuild_theme_registry();
}

// Add Zen Tabs styles
if (theme_get_setting('cdt2011_zen_tabs')) {
  drupal_add_css(drupal_get_path('theme', 'cdt2011') . '/css/tabs.css', 'theme', 'screen');
}

//Ajout du css spécifique à un domaine (aucun css spécifique pour le domaine principal)
global $_domain;
if ($_domain && isset($_domain['domain_id'])) {
  if ($_domain['domain_id'] == 0) {

  }
  else {
    drupal_add_css(drupal_get_path('theme', 'cdt2011') . '/css/style_domain-2.css', 'theme', 'screen');
  }
}


/*
 *	 This function creates the body classes that are relative to each page
 *
 *	@param $vars
 *	  A sequential array of variables to pass to the theme template.
 *	@param $hook
 *	  The name of the theme function being called ("page" in this case.)
 */

function cdt2011_preprocess_page(&$vars, $hook) {
  global $language;
  $vars['language'] = $language->language;

  $cuss = get_cuss_context_settings();
  if ($cuss) {
    $inlinecss = '';
    if (isset($cuss->field_customth_header_img[0]['fid'])) {
      $imgurl = imagecache_create_url('headerbg', $cuss->field_customth_header_img[0]['filepath']);
      $inlinecss .= ' .not-front #header_type { background: black url(' . url($imgurl, array('absolute' => TRUE)) . ') no-repeat; background-position:center;}';
    }
    if (isset($cuss->field_customth_titlecolor[0]['value'])) {
      $inlinecss .= ' .ubox h3 a:hover, .browse:hover, .page_type .browse:hover, #slide_agenda .items_agenda .agenda_img .content_img_agenda h3 a:hover, #conteneur_left h2 a, #conteneur_left #fil_ariane li a, #conteneur_left #fil_ariane li , #conteneur_left .box_decouvrez h2, #conteneur_left .box_decouvrez .contenu_decouvrez ul li a:hover, #conteneur_left .box_categories h2, #slide_ss_categories h2, #conteneur_left #content_meteo, #conteneur_left .box_3_img .conteneur_img_ss_categories .content_img_ss_categories h3 a, #titre_agenda h1, .fleche:hover, #conteneur_left_agenda h2, #contact h2, #slide_ss_categories .conteneur_box a:hover, .conteneur_img_ss_categories .content_img_ss_categories a:hover, #conteneur_right .box_right h2 a:hover, .uboxbp h2, .uboxpb_items a, #conteneur_left .box_categories h1, .ubox_pro .ubox_item h3 a, #conteneur_left_agenda h1, #conteneur_left h1, #titre_h2, #wrap_haut_pro #box_profil li:hover > a, #conteneur_left_agenda .pagination li.active a, #conteneur_left_agenda .pagination li a:hover { color: #' . $cuss->field_customth_titlecolor[0]['value'] . '; }';
    }
    if (isset($cuss->field_customth_bgcolor[0]['value'])) {
      $inlinecss .= ' body.page_type { background-color: #' . $cuss->field_customth_bgcolor[0]['value'] . '; }';
    }
    $vars['cuss_inline'] = $inlinecss;
  }

  $vars['primary_links'] = menu_tree_page_data('primary-links');

  $vars['footer_links'] = menu_tree_page_data('menu-footer-links');

  // Don't display empty help from node_help().
  if ($vars['help'] == "<div class=\"help\"><p></p>\n</div>") {
    $vars['help'] = '';
  }

  // Classes for body element. Allows advanced theming based on context
  // (home page, node of certain type, etc.)
  $body_classes = array($vars['body_classes']);

  //Ajout d'une classe relative au domaine courant
  global $_domain;
  if ($_domain && isset($_domain['domain_id'])) {
    if ($_domain['domain_id'] == 0) {
      $body_classes[] = 'domain-default';
    }
    else {
      $body_classes[] = 'domain-' . $_domain['domain_id'];
    }
  }


  if (user_access('administer blocks')) {
    $body_classes[] = 'admin';
  }
  if (theme_get_setting('cdt2011_wireframe')) {
    $body_classes[] = 'with-wireframes'; // Optionally add the wireframes style.
  }
  if (!empty($vars['primary_links']) or !empty($vars['secondary_links'])) {
    $body_classes[] = 'with-navigation';
  }
  if (!empty($vars['secondary_links'])) {
    $body_classes[] = 'with-secondary';
  }
  if (module_exists('taxonomy') && $vars['node']->nid) {
    foreach (taxonomy_node_get_terms($vars['node']) as $term) {
      $body_classes[] = 'tax-' . eregi_replace('[^a-z0-9]', '-', $term->name);
    }
  }

  $vars['header_id'] = 'header_type';

  if (arg(0) == 'comment' && arg(1) == 'reply') {
    $body_classes[] = 'page-node';
    $body_classes[] = 'node-type-bon-plan';
  }

  $vars['main_domain'] = TRUE;
  if ($_domain['domain_id'] != 0) {
    $vars['main_domain'] = FALSE;
  }

  if (!$vars['is_front']) {

    // Add unique classes for each page and website section
    $path = drupal_get_path_alias($_GET['q']);
    list($section,) = explode('/', $path, 2);
    $body_classes[] = cdt2011_id_safe('page-' . $path);
    $body_classes[] = cdt2011_id_safe('section-' . $section);

    if (arg(0) == 'node') {
      if (arg(1) == 'add') {
        if ($section == 'node') {
          array_pop($body_classes); // Remove 'section-node'
        }
        $body_classes[] = 'section-node-add'; // Add 'section-node-add'
      }
      elseif (is_numeric(arg(1)) && (arg(2) == 'edit' || arg(2) == 'delete')) {
        if ($section == 'node') {
          array_pop($body_classes); // Remove 'section-node'
        }
        $body_classes[] = 'section-node-' . arg(2); // Add 'section-node-edit' or 'section-node-delete'
      }

    }

  }
  else {
    if ($_domain['domain_id'] == 0) {
      drupal_add_css(drupal_get_path('theme', 'cdt2011') . '/css/style_home.css', 'theme', 'screen');
      $vars['header_id'] = 'header';
    }
  }
  /*  // Check what the user's browser is and add it as a body class
      // DEACTIVATED - Only works if page cache is deactivated
      $user_agent = $_SERVER['HTTP_USER_AGENT'];
      if($user_agent) {
        if (strpos($user_agent, 'MSIE')) {
          $body_classes[] = 'browser-ie';
        } else if (strpos($user_agent, 'MSIE 6.0')) {
          $body_classes[] = 'browser-ie6';
        } else if (strpos($user_agent, 'MSIE 7.0')) {
          $body_classes[] = 'browser-ie7';
        } else if (strpos($user_agent, 'MSIE 8.0')) {
          $body_classes[] = 'browser-ie8';
        } else if (strpos($user_agent, 'Firefox/2')) {
          $body_classes[] = 'browser-firefox2';
        } else if (strpos($user_agent, 'Firefox/3')) {
          $body_classes[] = 'browser-firefox3';
        }else if (strpos($user_agent, 'Safari')) {
          $body_classes[] = 'browser-safari';
        } else if (strpos($user_agent, 'Opera')) {
          $body_classes[] = 'browser-opera';
        }
      }

  /* Add template suggestions based on content type
   * You can use a different page template depending on the
   * content type or the node ID
   * For example, if you wish to have a different page template
   * for the story content type, just create a page template called
   * page-type-story.tpl.php
   * For a specific node, use the node ID in the name of the page template
   * like this : page-node-22.tpl.php (if the node ID is 22)
   */

  if ($vars['node']->type != "") {
    $vars['template_files'][] = "page-type-" . $vars['node']->type;
  }
  if ($vars['node']->nid != "") {
    $vars['template_files'][] = "page-node-" . $vars['node']->nid;
  }

  /*Traitement des vairables des flux*/
  if ($vars['node']->nid != "" && substr($vars['node']->type, 0, 5) == 'flux_') {
    $body_classes[] = 'node-type-bon-plan';
  }

  $vars['body_classes'] = implode(' ', $body_classes); // Concatenate with spaces

  /* Modify styles
   */
  if (!empty($vars['styles'])) {
    $css = drupal_add_css();
    /* Suppression d'un fichier css de module */
    $path = drupal_get_path('module', 'textsize');
    unset($css['all']['module'][$path . '/textsize.css']);

    /* Prise en compte des modifications */
    $vars['styles'] = drupal_get_css($css);
  }
}


function menu_tree_output_level($tree) {
  $lang   = language_initialize();
  $output = '';
  $items  = array();

  // Pull out just the menu items we are going to render so that we
  // get an accurate count for the first/last classes.
  foreach ($tree as $data) {
    if (!$data['link']['hidden']) {

      if (isset($data['link']['options']['langcode']) && $data['link']['options']['langcode'] != $lang->language) {
        // Doesn't show item menu if it hasn't to show in this language context
      }
      else {
        $items[] = $data;
      }
    }
  }

  $num_items = count($items);

  $level_with_imgs = FALSE;

  foreach ($items as $i => $data) {
    $extra_class = array();

    $separator = '';

    if ($data['link']['menu_name'] == 'primary-links' && $data['link']['depth'] == 1) {
      $separator = '<li class="separator">|</li>';
    }

    if ($i == 0) {
      $extra_class[] = 'first';
      $separator     = '';
    }
    if ($i == $num_items - 1) {
      $extra_class[] = 'last';
    }

    $output .= $separator;

    if (format_menu_link_imglist($data['link'])) {
      $level_with_imgs = TRUE;
    }

    $extra_class = implode(' ', $extra_class);
    $link        = theme('menu_item_link', $data['link']);
    if ($data['below']) {
      $output .= theme('menu_item_custom', $link, $data['link']['has_children'], menu_tree_output_level($data['below']), $data['link']['in_active_trail'], $extra_class);
    }
    else {
      $output .= theme('menu_item_custom', $link, $data['link']['has_children'], '', $data['link']['in_active_trail'], $extra_class);
    }
  }

  $attributes = array('class' => 'menu level-' . $data['link']['depth']);


  if ($data['link']['depth'] == 2) {
    $attributes['class'] .= ' ssmenu';
    //if($level_with_imgs){
    $attributes['class'] .= ' hoverleft_ssmenu';
    //}
  }

  if ($data['link']['depth'] == 1) {
    $attributes['id'] = "menu-" . $data['link']['menu_name'];
    $attributes['class'] .= ' hover_ssmenu';
  }

  return $output ? theme('menu_tree', $output, $attributes) : '';
}

//Menu de pied de page
function menu_tree_output_footer($tree, $id) {
  global $language;
  $output = '<ul id="' . $id . '">';
  $items  = array();

  // Pull out just the menu items we are going to render so that we
  // get an accurate count for the first/last classes.
  foreach ($tree as $data) {
    if (!$data['link']['hidden']) {

      if (isset($data['link']['options']['langcode']) && $data['link']['options']['langcode'] != $language->language) {
        // Doesn't show item menu if it hasn't to show in this language context
      }
      else {
        $items[] = $data;
      }
    }
  }

  // Pull out just the menu items we are going to render so that we
  // get an accurate count for the first/last classes.
  foreach ($items as $i => $menu) {
    $class = '';
    if (!$menu['link']['hidden'] && (!isset($menu['link']['options']['langcode']) || $menu['link']['options']['langcode'] == $language->language)) {
      if ($i == 0) {
        $class .= ' first';
      }
      $output .= '<li class="item-' . $i . $class . '">';
      $output .= l(menu_text_transform($menu['link']['title']), $menu['link']['link_path'], array('absolute'   => TRUE,
                                                                                                  'html'       => TRUE,
                                                                                                  'attributes' => array('title' => menu_text_transform($menu['link']['title']))
      ));
      if (is_array($menu['below'])) {
        $output .= '<ul>';
        foreach ($menu['below'] as $sousmenu) {
          if (!$sousmenu['link']['hidden'] && (!isset($sousmenu['link']['options']['langcode']) || $sousmenu['link']['options']['langcode'] == $language->language)) {
            $output .= '<li>';
            $output .= l(menu_text_transform($sousmenu['link']['title']), $sousmenu['link']['link_path'], array('absolute'   => TRUE,
                                                                                                                'html'       => TRUE,
                                                                                                                'attributes' => array('title' => menu_text_transform($sousmenu['link']['title']))
            ));
            $output .= '</li>';
          }
        }
        $output .= '</ul>';
      }
      $output .= '</li>';
    }
  }
  $output .= '<br class="clear"></ul>';

  return $output;
}

function menu_text_transform($text) {
  //Transforme une chaine "blabla;;bla" en "<span>blabla</span>blabla
  $pattern = '/^[a-zA-Z0-9._-ÀÁÂÃÄÅÇÈÉÊËÌÍÎÏÒÓÔÕÖÙÚÛÜÝàáâãäåçèéêëìíîïðòóôõöùúûüýÿ]+(;;)[a-zA-Z0-9._-ÀÁÂÃÄÅÇÈÉÊËÌÍÎÏÒÓÔÕÖÙÚÛÜÝàáâãäåçèéêëìíîïðòóôõöùúûüýÿ]+$/';

  if (preg_match($pattern, $text)) {
    $parts = split(';;', $text);
    $text  = '<span>' . t($parts[0]) . '</span>' . t($parts[1]);
  }
  return $text;
}

function cdt2011_theme($existing, $type, $theme, $path) {
  return array(
    'menu_item_custom' => array(
      'arguments' => array('link'            => NULL,
                           'has_children'    => NULL,
                           'menu'            => '',
                           'in_active_trail' => FALSE,
                           'extra_class'     => NULL
      ),
      'file'      => 'template-hooks.inc',
    ),
    'menu_tree'        => array(
      'arguments' => array('tree' => NULL, 'attributes' => NULL),
      'file'      => 'template-hooks.inc',
    ),
    'comment_form'     => array(
      'arguments' => array('form' => NULL)
    )
  );
}


/*
 *	 This function creates the NODES classes, like 'node-unpublished' for nodes
 *	 that are not published, or 'node-mine' for node posted by the connected user...
 *
 *	@param $vars
 *	  A sequential array of variables to pass to the theme template.
 *	@param $hook
 *	  The name of the theme function being called ("node" in this case.)
 */

function cdt2011_preprocess_node(&$vars, $hook) {


  // Special classes for nodes
  $classes = array('node');

  /*
  * Pour les flux, on ajoute un template spécifique commun à tous les flux
  */
  if (isset($vars['node']) && substr($vars['node']->type, 0, 5) == "flux_" && !preg_match('/B2917/i', $vars['node']->type)) {
    $vars['template_files'][] = "node-common-flux";
  }
  elseif (preg_match('/B2917/i', $vars['node']->type) && $vars['node']->cssclass) {
    $classes[] = $vars['node']->cssclass;
  }
  elseif (preg_match('/sejwe_infos/i', $vars['node']->type)) {
    $classes[] = $vars['node']->field_sejwe_cssclass[0]['value'];
  }


  if ($vars['sticky']) {
    $classes[] = 'sticky';
  }
  // support for Skinr Module
  if (module_exists('skinr')) {
    $classes[] = $vars['skinr'];
  }
  if (!$vars['status']) {
    $classes[]           = 'node-unpublished';
    $vars['unpublished'] = TRUE;
  }
  else {
    $vars['unpublished'] = FALSE;
  }
  if ($vars['uid'] && $vars['uid'] == $GLOBALS['user']->uid) {
    $classes[] = 'node-mine'; // Node is authored by current user.
  }
  if ($vars['teaser']) {
    $classes[] = 'node-teaser'; // Node is displayed as teaser.
  }
  $classes[] = 'clearfix';

  // Class for node type: "node-type-page", "node-type-story", "node-type-my-custom-type", etc.
  $classes[] = cdt2011_id_safe('node-type-' . $vars['type']);


  /* Add region to node */
  $vars['content_right'] = theme('blocks', 'content_right');


  /* Add picture variable */
  if (isset($vars['field_hqitem_teaserimg'][0])) {
    $vars['picture'] = $vars['field_hqitem_teaserimg'][0]['view'];
  }

  if (isset($vars['field_ditem_list_image'][0])) {
    $vars['picture'] = $vars['field_ditem_list_image'][0]['view'];
  }
  if (isset($vars['field_page_thumbnails'][0])) {
    $vars['picture'] = $vars['field_page_thumbnails'][0]['view'];
  }

  /* Add build_mode into a variable
   * Example : array(build_mode=>ubox_resume) give $ubox_resume
   */
  if (is_string($vars['build_mode'])) {
    $vars[$vars['build_mode']] = TRUE;
  }

  if ($vars['readmore']) {
    $vars['links'] = theme('links', $vars['node']->links, array('class' => 'links inline'));
  }

  /*
  *  Gestion de l'encart droit des contenus de type hqitems :
  *  Lorsque le champ "field_hqitem_rightbox"
  */
  if (isset($vars['node']->field_hqitem_rightbox[0]['value']) && strlen($vars['node']->field_hqitem_rightbox[0]['value']) > 0) {
    $vars['content_right'] = '<div class="content-right-node-field">' . $vars['node']->field_hqitem_rightbox[0]['value'] . ($vars['content_right'] ? $vars['content_right'] : '') . '</div>' . $vars['content_right'];
  }

  if (isset($vars['node']->field_hqitem_pageimg[0]['filepath']) && strlen($vars['node']->field_hqitem_pageimg[0]['filepath']) > 0) {
    $vars['field_hqitem_pageimg'] = theme('imagecache', 'hqitem_page', $vars['node']->field_hqitem_pageimg[0]['filepath'], '', '', array('class' => 'img_ss_categories'));
  }
  else {
    unset($vars['field_hqitem_pageimg']);
  }

  if (isset($vars['node']->href_content_nodeClasses) && count($vars['node']->href_content_nodeClasses) > 0) {
    foreach ($vars['node']->href_content_nodeClasses as $c) {
      $vars['classes'] .= ' ' . $c;
    }
  }

  //Pour les teasers, permet de factoriser les tpls (utilisé pour les contenus mis en avant par tagging : "Coup de coeur", "A la une"...).
  if (isset($vars['node']->field_cnt_date)) {
    //TODO : Si français, mettre "Le " devant.
    //Si location, ajouter la ville
    $vars['cnt_date_loc'] = theme($vars['node']->content['field_cnt_date']['field']['items'][0]['#theme'], $vars['node']->content['field_cnt_date']['field']['items'][0]) . (isset($vars['node']->locations[0]['city']) ? ' | Lieu : ' . $vars['node']->locations[0]['city'] : '');
  }

  /*Traitement des vairables de bons plans*/
  if ($vars['page'] && $vars['node']->type == 'bon_plan') {
    node_bon_plan_set_vars($vars);
  }

  /*Traitement des vairables des flux*/
  if ($vars['page'] && substr($vars['node']->type, 0, 5) == 'flux_') {
    node_flux_set_vars($vars);
  }

  //Permet d'utiliser la variable "sharethis" directement dans le tpl du node
  if (isset($vars['node']->content['simple_share']['#value']) && !isset($vars['node']->field_hqitem_fluxdisplay[0]['value'])) {
    $vars['sharethis'] = $vars['node']->content['simple_share']['#value'];
  }
  unset($vars['node']->content['simple_share']);


  //Gestion de la liste des offres séjour weekend dans le node sejwe_infos
  if (isset($vars['node']->content['reservez_sejwe_by_theme_node_content_1'])) {
    $vars['reservez_sejwe_by_theme'] = $vars['node']->content['reservez_sejwe_by_theme_node_content_1']['#value'];
    drupal_add_css(drupal_get_path('theme', 'cdt2011') . '/css/style_INTERFACE_RESA.css');
    if (!isset($vars['node']->taxonomy['285']) && !isset($vars['node']->taxonomy['3078'])) { // Pas d'affichage du theme week end pour les séjours
      if (isset($vars['node']->taxonomy['3079'])) {
        $th_view = views_get_view('reservez_sejwe_weekend_themes_en');
      }
      else {
        $th_view = views_get_view('reservez_sejwe_weekend_themes');
      }
      $vars['list_theme_sejwe'] = $th_view->execute_display();
    }
  }

  //Ajoute une classe CSS spécifique aux affichages de flux
  if (isset($vars['node']->field_hqitem_fluxdisplay[0]['value']) || isset($vars['node']->field_hqitem_fluxtid[0]['value'])) {
    $classes[] = 'hqitem-with-flux-list';
  }

  $vars['add_carnet_link'] = l(t('Add bookmark'), 'ajax/add-to-carnet/' . $vars['node']->nid, array('attributes' => array('id'    => 'up_agenda',
                                                                                                                          'class' => 'add-to-carnet-btn'
  )
  ));

  $vars['classes'] = implode(' ', $classes); // Concatenate with spaces
//	dsm($vars);
}

function node_bon_plan_set_vars(&$vars) {
  $n = $vars['node'];

  $prix = $n->field_bp_prix[0]['value'];

  //Gestion des images;
  $img       = '';
  $tiny_imgs = array();
  if (count($n->field_bp_images) > 0) {
    for ($i = 0; $i < count($n->field_bp_images); $i++) {
      if (isset($n->field_bp_images[$i]['fid'])) {
        $item = $n->field_bp_images[$i];
        $img .= '<a class="lien_img">' . $item['view'] . '</a>';
        $tiny_imgs[] = '<a href="#" ' . ($i == 0 ? 'class="current"' : '') . '>' . theme('imagecache', 'bp_tiny_img', $item['filepath'], $item['data']['alt'], $item['data']['title']) . '</a>';
      }
    }
    $vars['img']            = $img;
    $vars['img_thumbdails'] = '<ul class="g-tabs">';
    for ($i = 0; $i < count($tiny_imgs); $i++) {
      $item  = $tiny_imgs[$i];
      $class = '';
      if ($i == 0) {
        $class = 'first';
      }
      elseif ($i + 1 >= count($tiny_imgs)) {
        $class = 'last';
      }
      $vars['img_thumbdails'] .= '<li class="' . $class . '">' . $item . '</li>';
    }
    $vars['img_thumbdails'] .= '</ul>';
  }

  //Gestion du prix
  if ($n->field_bp_prix[0]['view']) {
    $vars['prix'] = '<div class="prix">' . $n->field_bp_prix[0]['view'];
    if ($n->field_bp_ancienprix[0]['view']) {
      $vars['prix'] .= '<span>' . t('instead of') . ' <del>' . $n->field_bp_ancienprix[0]['view'] . '</del></span>';
    }
    $vars['prix'] .= '</div>';
  }


  //Gestion du terme de taxo
  $tids          = array_keys($n->taxonomy);
  $terms         = $n->taxonomy[$tids[0]]->name;
  $vars['terms'] = '<h3>' . $terms . '</h3>';

  if ($n->field_bp_nbrestant[0]['view']) {
    $vars['nboffers'] = t('%nombre left', array('%nombre' => format_plural($n->field_bp_nbrestant[0]['view'], '1 offer', '@count offers')));
  }
  if ($n->field_resa_link[0]['display_url'] != '') {
    $vars['reservez'] = l(t('Réservez cette offre'), $n->field_resa_link[0]['display_url'], array('attributes' => array('id' => 'bouton')));
  }


}


/**
 * GESTION DES VARIABLES DES FLUX
 */
function node_flux_set_vars(&$vars) {

  if ($vars['node']->locations[0]['latitude'] && $vars['node']->locations[0]['longitude'] && $vars['node']->locations[0]['latitude'] != '0.000000' && $vars['node']->locations[0]['longitude'] != '0.000000') {
    $vars['map'] = gmap_simple_map($vars['node']->locations[0]['latitude'], $vars['node']->locations[0]['longitude'], '', '', 7);
  }

}


/*
* Theme implementation of the number cck formatter for CT bon-plan
*/
function cdt2011_number_formatter_fr_2($element) {
  $field = content_fields($element['#field_name'], $element['#type_name']);
  $value = $element['#item']['value'];

  if (($allowed_values = content_allowed_values($field))) {
    if (isset($allowed_values[$value]) && $allowed_values[$value] != $value) {
      return $allowed_values[$value];
    }
  }

  if (empty($value) && $value !== '0') {
    return '';
  }


  $output = number_format($value, 2, ',', ' ');


  //DEBUT OVERRIDE
  if ($element['#node']->type == 'bon_plan' &&
    ($element['#field_name'] == 'field_bp_prix' || $element['#field_name'] == 'field_bp_ancienprix')
  ) {

    $prefixes = isset($field['prefix']) ? array_map('content_filter_xss', explode('|', $field['prefix'])) : array('');
    $suffixes = isset($field['suffix']) ? array_map('content_filter_xss', explode('|', $field['suffix'])) : array('');
    $prefix   = (count($prefixes) > 1) ? format_plural($value, $prefixes[0], $prefixes[1]) : $prefixes[0];
    $suffix   = (count($suffixes) > 1) ? format_plural($value, $suffixes[0], $suffixes[1]) : $suffixes[0];

    $parts  = split(',', $output);
    $output = $parts[0] . $suffix . ',<sup>' . $parts[1] . '</sup>';
    return $output;

  }
  else {

    $prefixes = isset($field['prefix']) ? array_map('content_filter_xss', explode('|', $field['prefix'])) : array('');
    $suffixes = isset($field['suffix']) ? array_map('content_filter_xss', explode('|', $field['suffix'])) : array('');
    $prefix   = (count($prefixes) > 1) ? format_plural($value, $prefixes[0], $prefixes[1]) : $prefixes[0];
    $suffix   = (count($suffixes) > 1) ? format_plural($value, $suffixes[0], $suffixes[1]) : $suffixes[0];
    return $prefix . $output . $suffix;

  }
  //FIN OVERRIDE

}


function cdt2011_preprocess_comment_wrapper(&$vars) {
  $classes   = array();
  $classes[] = 'comment-wrapper';

  // Provide skinr support.
  if (module_exists('skinr')) {
    $classes[] = $vars['skinr'];
  }
  $vars['classes'] = implode(' ', $classes);
}


/*
 *	This function create the EDIT LINKS for blocks and menus blocks.
 *	When overing a block (except in IE6), some links appear to edit
 *	or configure the block. You can then edit the block, and once you are
 *	done, brought back to the first page.
 *
 * @param $vars
 *   A sequential array of variables to pass to the theme template.
 * @param $hook
 *   The name of the theme function being called ("block" in this case.)
 */

function cdt2011_preprocess_block(&$vars, $hook) {
  $block = $vars['block'];

  // special block classes
  $classes   = array('block');
  $classes[] = cdt2011_id_safe('block-' . $vars['block']->module);
  $classes[] = cdt2011_id_safe('block-' . $vars['block']->region);
  $classes[] = cdt2011_id_safe('block-id-' . $vars['block']->bid);
  $classes[] = 'clearfix';

  // support for Skinr Module
  if (module_exists('skinr')) {
    $classes[] = $vars['skinr'];
  }
  if (module_exists('block_class')) {
    $cl = block_class_attributes($block);
    if ($cl && $cl->css_class) {
      $classes[] = $cl->css_class;
    }
  }
  $vars['block_classes'] = implode(' ', $classes); // Concatenate with spaces

  if (theme_get_setting('cdt2011_block_editing') && user_access('administer blocks')) {
    // Display 'edit block' for custom blocks.
    if ($block->module == 'block') {
      $edit_links[] = l('<span>' . t('edit block') . '</span>', 'admin/build/block/configure/' . $block->module . '/' . $block->delta,
        array(
          'attributes' => array(
            'title' => t('edit the content of this block'),
            'class' => 'block-edit',
          ),
          'query'      => drupal_get_destination(),
          'html'       => TRUE,
        )
      );
    }
    // Display 'configure' for other blocks.
    else {
      $edit_links[] = l('<span>' . t('configure') . '</span>', 'admin/build/block/configure/' . $block->module . '/' . $block->delta,
        array(
          'attributes' => array(
            'title' => t('configure this block'),
            'class' => 'block-config',
          ),
          'query'      => drupal_get_destination(),
          'html'       => TRUE,
        )
      );
    }
    // Display 'edit menu' for Menu blocks.
    if (($block->module == 'menu' || ($block->module == 'user' && $block->delta == 1)) && user_access('administer menu')) {
      $menu_name    = ($block->module == 'user') ? 'navigation' : $block->delta;
      $edit_links[] = l('<span>' . t('edit menu') . '</span>', 'admin/build/menu-customize/' . $menu_name,
        array(
          'attributes' => array(
            'title' => t('edit the menu that defines this block'),
            'class' => 'block-edit-menu',
          ),
          'query'      => drupal_get_destination(),
          'html'       => TRUE,
        )
      );
    }
    // Display 'edit menu' for Menu block blocks.
    elseif ($block->module == 'menu_block' && user_access('administer menu')) {
      list($menu_name,) = split(':', variable_get("menu_block_{$block->delta}_parent", 'navigation:0'));
      $edit_links[] = l('<span>' . t('edit menu') . '</span>', 'admin/build/menu-customize/' . $menu_name,
        array(
          'attributes' => array(
            'title' => t('edit the menu that defines this block'),
            'class' => 'block-edit-menu',
          ),
          'query'      => drupal_get_destination(),
          'html'       => TRUE,
        )
      );
    }
    $vars['edit_links_array'] = $edit_links;
    $vars['edit_links']       = '<div class="edit">' . implode(' ', $edit_links) . '</div>';
  }
}

/*
 * Override or insert PHPTemplate variables into the block templates.
 *
 *  @param $vars
 *    An array of variables to pass to the theme template.
 *  @param $hook
 *    The name of the template being rendered ("comment" in this case.)
 */

function cdt2011_preprocess_comment(&$vars, $hook) {
  // Add an "unpublished" flag.
  $vars['unpublished'] = ($vars['comment']->status == COMMENT_NOT_PUBLISHED);

  // If comment subjects are disabled, don't display them.
  if (variable_get('comment_subject_field_' . $vars['node']->type, 1) == 0) {
    $vars['title'] = '';
  }

  // Special classes for comments.
  $classes = array('comment');
  if ($vars['comment']->new) {
    $classes[] = 'comment-new';
  }
  $classes[] = $vars['status'];
  $classes[] = $vars['zebra'];
  if ($vars['id'] == 1) {
    $classes[] = 'first';
  }
  if ($vars['id'] == $vars['node']->comment_count) {
    $classes[] = 'last';
  }
  if ($vars['comment']->uid == 0) {
    // Comment is by an anonymous user.
    $classes[] = 'comment-by-anon';
  }
  else {
    if ($vars['comment']->uid == $vars['node']->uid) {
      // Comment is by the node author.
      $classes[] = 'comment-by-author';
    }
    if ($vars['comment']->uid == $GLOBALS['user']->uid) {
      // Comment was posted by current user.
      $classes[] = 'comment-mine';
    }
  }
  $vars['classes'] = implode(' ', $classes);
}

/*
 * 	Customize the PRIMARY and SECONDARY LINKS, to allow the admin tabs to work on all browsers
 * 	An implementation of theme_menu_item_link()
 *
 * 	@param $link
 * 	  array The menu item to render.
 * 	@return
 * 	  string The rendered menu item.
 */

function cdt2011_menu_item_link($link) {
  if (empty($link['localized_options'])) {
    $link['localized_options'] = array();
  }

  // If an item is a LOCAL TASK, render it as a tab
  if ($link['type'] & MENU_IS_LOCAL_TASK) {
    $link['title']                     = '<span class="tab">' . t(check_plain($link['title'])) . '</span>';
    $link['localized_options']['html'] = TRUE;
  }

  $html_link = format_menu_link_imglist($link);

  $title = '';

  //Transforme une chaine "blabla;;bla" en "<span>blabla</span>blabla
  $pattern = '/^[a-zA-Z0-9._-ÀÁÂÃÄÅÇÈÉÊËÌÍÎÏÒÓÔÕÖÙÚÛÜÝàáâãäåçèéêëìíîïðòóôõöùúûüýÿ]+(;;)[a-zA-Z0-9._-ÀÁÂÃÄÅÇÈÉÊËÌÍÎÏÒÓÔÕÖÙÚÛÜÝàáâãäåçèéêëìíîïðòóôõöùúûüýÿ]+$/';

  if (preg_match($pattern, $link['title'])) {
    $parts                             = split(';;', $link['title']);
    $title                             = '<span>' . t($parts[0]) . '</span>' . t($parts[1]);
    $link['localized_options']['html'] = TRUE;
  }
  else {
    $title = t($link['title']);
  }

  if ($html_link) {
    return l($title, $link['href'], $link['localized_options']) . $html_link;
  }
  else {
    return l($title, $link['href'], $link['localized_options']);
  }
}


/*
 *  Duplicate of theme_menu_local_tasks() but adds clear-block to tabs.
 */

function cdt2011_menu_local_tasks() {
  $output = '';
  if ($primary = menu_primary_local_tasks()) {
    if (menu_secondary_local_tasks()) {
      $output .= '<ul class="tabs primary with-secondary clearfix">' . $primary . '</ul>';
    }
    else {
      $output .= '<ul class="tabs primary clearfix">' . $primary . '</ul>';
    }
  }
  if ($secondary = menu_secondary_local_tasks()) {
    $output .= '<ul class="tabs secondary clearfix">' . $secondary . '</ul>';
  }
  return $output;
}

/*
 * 	Add custom classes to menu item
 */
function cdt2011_menu_item($link, $has_children, $menu = '', $in_active_trail = FALSE, $extra_class = NULL) {
  $class = ($menu ? 'expanded' : ($has_children ? 'collapsed' : 'leaf'));
  if (!empty($extra_class)) {
    $class .= ' ' . $extra_class;
  }
  if ($in_active_trail) {
    $class .= ' active-trail';
  }

#New line added to get unique classes for each menu item
  $css_class = cdt2011_id_safe(str_replace(' ', '_', strip_tags($link)));
  return '<li class="' . $class . ' ' . $css_class . '">' . $link . $menu . "</li>\n";
}

/*
 *	Converts a string to a suitable html ID attribute.
 *
 *	 http://www.w3.org/TR/html4/struct/global.html#h-7.5.2 specifies what makes a
 *	 valid ID attribute in HTML. This function:
 *
 *	- Ensure an ID starts with an alpha character by optionally adding an 'n'.
 *	- Replaces any character except A-Z, numbers, and underscores with dashes.
 *	- Converts entire string to lowercase.
 *
 *	@param $string
 *	  The string
 *	@return
 *	  The converted string
 */

function cdt2011_id_safe($string) {
  // Replace with dashes anything that isn't A-Z, numbers, dashes, or underscores.
  $string = strtolower(preg_replace('/[^a-zA-Z0-9_-]+/', '-', $string));
  // If the first character is not a-z, add 'n' in front.
  if (!ctype_lower($string{0})) { // Don't use ctype_alpha since its locale aware.
    $string = 'id' . $string;
  }
  return $string;
}

/**
 * Return a themed breadcrumb trail.
 *
 * @param $breadcrumb
 * An array containing the breadcrumb links.
 * @return
 * A string containing the breadcrumb output.
 */
function cdt2011_breadcrumb($breadcrumb) {
  // Determine if we are to display the breadcrumb.
  $show_breadcrumb = theme_get_setting('cdt2011_breadcrumb');
  if ($show_breadcrumb == 'yes' || $show_breadcrumb == 'admin' && arg(0) == 'admin') {

    // Optionally get rid of the homepage link.
    $show_breadcrumb_home = theme_get_setting('cdt2011_breadcrumb_home');
    if (!$show_breadcrumb_home) {
      array_shift($breadcrumb);
    }

    // Return the breadcrumb with separators.
    if (!empty($breadcrumb)) {
      $breadcrumb_separator = '<li class="separate">' . theme_get_setting('cdt2011_breadcrumb_separator') . '</li>';
      $trailing_separator   = $title = '';
      if (theme_get_setting('cdt2011_breadcrumb_title')) {
        if ($title = drupal_get_title()) {
          $trailing_separator = $breadcrumb_separator;
        }
      }
      elseif (theme_get_setting('cdt2011_breadcrumb_trailing')) {
        $trailing_separator = $breadcrumb_separator;
      }

      if (is_array($breadcrumb)) {
        foreach ($breadcrumb as $cle => $val) {
          $breadcrumb[$cle] = "<li>$val</li>";
        }
      }
      else {
        $breadcrumb = "<li>$breadcrumb</li>";
      }

      return '<ul id="fil_ariane">' . implode($breadcrumb_separator, $breadcrumb) . "$trailing_separator$title</ul>";
    }
  }
  // Otherwise, return an empty string.
  return '';
}

function cdt2011_comment_form($form) {
  $output = '';
  unset ($form['homepage']);
  $output .= drupal_render($form);
  return $output;
}

function cdt2011_new_norm($fields) {
  $output = '';
  if (isset($fields['field_fl_attente_classeme_value'])) {
    $output = $fields['field_fl_attente_classeme_value']->content;
    if (!empty($output)) {
      $output = ' - ' . $output;
    }
  }
  return $output;
}

function cdt2011_term_to_img($term, $separator = '', $prefix = 'term-img') {
  if (is_object($term)) {
    $term = $term->name;
  }

  $result = '';
  if (!empty($term)) {
    $result = '<span title="' . $term . '" class="' . $prefix . ' ' . $prefix . '-' . pathauto_cleanstring($term) . '">' . $separator . $term . '</span>';
  }

  return $result;
}

/**
 * Prepare the booking button if needed.
 */
function cdt2011_booking_button($fields) {
  $taxo = explode(',', $fields['tid_1']->content);
  $types = array(
    152 => 'z3132e9_fr', // Hotel
    2621 => 'z3132e9_fr', // Hotel
    2622 => 'z3132e9_uk', // Hotel EN
    410 => 'z3130e9_fr', // Camping
    2704 => 'z3130e9_uk', // Camping EN
    2629 => 'z2852e3_fr', // Chambres meublés
    2701 => 'z2852e3_uk', // Chambres meublés EN
    2402 => 'z3131e9_fr', // Chambres d'hôte
    2623 => 'z3131e9_uk', // Chambres d'hôte EN
  );

  $code = '';
  while (empty($code) && ($tid = key($types)) && ($type = current($types))) {
    if (in_array($tid, $taxo)) {
      $code = $type;
    }
    next($types);
  }

  $result = '';
  if (!empty($code)) {
    if (($fields['field_fixfl_onlineresa_value']->content == 'oui' || $fields['field_fixfl_onlineresa_value']->content == 'yes') &&
      isset($fields['field_fixfl_codemetier_value']) &&
      isset($fields['field_fixfl_codefournisseur_value'])
    ) {
      // Prepare CodeOs
      $code_parts = array(
        $fields['field_fixfl_codemetier_value']->content,
        $fields['field_fixfl_codefournisseur_value']->content,
        $fields['field_fixfl_codeproduit_value']->content,
      );
      $url = 'http://' . variable_get('flux_booking_domain_url', 'resa.finisteretourisme.com') . '/' . $code . '-.aspx?Param/CodeOs=' . implode('-', array_filter($code_parts));

      $result = '<div class="wrap_btn wrap_rsv_btn clearfix">';
      $result .= '<a class="rsv_btn" title="' . t('Book online') . '" href="' . $url . '">' . t('Book') . '</a>';
      $result .= '</div>';
    }
  }
  return $result;
}

function cdt2011_labels($terms) {
  if (!is_array($terms)) {
    $terms = explode(',', $terms);
  }

  // Prepare cache
  $labels = array();
  $cache = cache_get('cdt2011:labels', 'cache');
  if (!empty($cache->data)) {
    $labels = unserialize($cache->data);
  }

  $output = '';
  $accepted_parents = array(
    'LABELS',
//    'LABEL_TH',
//    'LOCALISATION',
  );
  foreach ($terms as $tid) {
    $term = taxonomy_get_term($tid);
    if (empty($term)) {
      continue;
    }
    if (!isset($labels[$tid])) {
      $parent = reset(taxonomy_get_parents($term->tid));
      $labels[$tid] = !empty($parent) && in_array($parent->name, $accepted_parents);
    }
    if ($labels[$tid]) {
      $output .= cdt2011_term_to_img($term, '', 'label-img');
    }
  }

  // Save cache
  cache_set('cdt2011:labels', serialize($labels));

  return $output;
}

function cdt2011_chaines_labels_tpl($node) {
  $output = '';

  $fields = array(
    'field_fl_chaines_strs' => 'chaine',
    'field_fl_labels_strs' => 'label',
    'field_fl_classement1_labe_strs' => 'label',
    'field_fl_classement2_labe_strs' => 'label',
    'field_fl_classement3_labe_strs' => 'label',
  );

  foreach ($fields as $fname => $type) {
    if (!empty($node->{$fname})) {
      foreach ($node->{$fname} as $delta => $item) {
        $output .= cdt2011_term_to_img($item['value'], '', $type. '-img');
      }
    }
  }

  if (!empty($output)) {
    $output = '<div class="chaines-labels">' . $output . '</div>';
  }
  return $output;
}

function cdt2011_prices_tpl($node) {
  $output = '';
  $lines = array();

  if (!empty($node->field_fl_tarif_label) && !empty($node->field_fl_tarif_label[0]['view']) && $node->field_fl_adherent_cdt_tx[0]['value'] == 'oui') {
    foreach ($node->field_fl_tarif_label as $delta => $item) {
      if (!empty($node->field_fl_tarif_min[$delta]['view']) || !empty($node->field_fl_tarif_max[$delta]['view'])) {
        $tmp = '<td class="grey">' . $item['view'] . '</td>';
        $tmp .= '<td class="grey">' . $node->field_fl_tarif_min[$delta]['view'] . '</td>';
        $tmp .= '<td class="grey">' . $node->field_fl_tarif_max[$delta]['view'] . '</td>';
        $lines[] = $tmp;
      }
    }
  }

  if (!empty($lines)) {
    $output .= '<h4 class="lower">' . t('Prices') . '</h4>';
    $output .= '<table id="table_tarif">';
      $output .= '<tr>';
        $output .= '<td class="no_border"></td>';
        $output .= '<td class="grey">' . t('Min') . '</td>';
        $output .= '<td class="grey">' . t('Max') . '</td>';
      $output .= '</tr>';
      $output .= '<tr>' . implode('</tr><tr>', $lines) . '</tr>';
    $output .= '</table>';
  }
  return $output;
}
