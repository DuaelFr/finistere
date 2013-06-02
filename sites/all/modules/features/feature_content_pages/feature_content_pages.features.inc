<?php

/**
 * Implementation of hook_ctools_plugin_api().
 */
function feature_content_pages_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => 1);
  }
}

/**
 * Implementation of hook_imagecache_default_presets().
 */
function feature_content_pages_imagecache_default_presets() {
  $items = array(
    'hqitem_teaser' => array(
      'presetname' => 'hqitem_teaser',
      'actions' => array(
        '0' => array(
          'weight' => '0',
          'module' => 'imagecache',
          'action' => 'imagecache_scale_and_crop',
          'data' => array(
            'width' => '196',
            'height' => '267',
          ),
        ),
      ),
    ),
    'prim_list_img' => array(
      'presetname' => 'prim_list_img',
      'actions' => array(
        '0' => array(
          'weight' => '0',
          'module' => 'imagecache',
          'action' => 'imagecache_scale_and_crop',
          'data' => array(
            'width' => '280',
            'height' => '163',
          ),
        ),
      ),
    ),
  );
  return $items;
}

/**
 * Implementation of hook_node_info().
 */
function feature_content_pages_node_info() {
  $items = array(
    'flux' => array(
      'name' => t('Flux'),
      'module' => 'features',
      'description' => t('Define Tourinsoft idModule'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'has_body' => '0',
      'body_label' => '',
      'min_word_count' => '0',
      'help' => '',
    ),
    'hqitem' => array(
      'name' => t('Contenu hiérarchique'),
      'module' => 'features',
      'description' => t('Contenu hiérarchique pouvant être placé n\'importe où dans le site'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'has_body' => '1',
      'body_label' => t('Body'),
      'min_word_count' => '0',
      'help' => '',
    ),
    'page' => array(
      'name' => t('Page'),
      'module' => 'features',
      'description' => t('A <em>page</em>, similar in form to a <em>story</em>, is a simple method for creating and displaying information that rarely changes, such as an "About us" section of a website. By default, a <em>page</em> entry does not allow visitor comments and is not featured on the site\'s initial home page.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'has_body' => '1',
      'body_label' => t('Body'),
      'min_word_count' => '0',
      'help' => '',
    ),
  );
  return $items;
}
