<?php
/**
 * Specially named implementation of hook_wysiwyg_plugin().
 *
 * Should be named {$module}_{$plugin}_plugin().
 */
function wysiwyg_richmedia_slideshow_plugin() {
  $plugins['slideshow'] = array(
    'title' => t('Slideshow: A richmedia plugin to display slideshow'),
    'css file' => 'wysiwyg_richmedia_slideshow.css',
    // The 'icon file' is the icon that appears in the Wysiwyg toolbar.
    'icon file' => 'slideshow.toolbar_icon.png',
    'icon title' => t('Add slideshow'),
    'settings' => array(),
  );
  return $plugins;
}