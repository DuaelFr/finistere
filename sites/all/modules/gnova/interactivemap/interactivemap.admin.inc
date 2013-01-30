<?php
function interactivemap_settings() {
  $form['#tree'] = false;

  // textarea & format (format needed to have the wysiwyg)
  $form['interactivemap']['interactivemap_description'] = array(
    '#type' => 'textarea',
    '#title' => "Interactive map description",
    '#rows' => 10,
    '#cols' => 30,
    '#resizable' => TRUE,
    '#default_value' => variable_get('interactivemap_description', ""),
  );

  $form['interactivemap']['format'] = filter_form(FILTER_FORMAT_DEFAULT, null, array('interactivemap'));

  /**
   * Source:
   * http://stackoverflow.com/questions/5624255/attach-wysiwyg-to-custom-drupal-form
   * http://www.thecarneyeffect.co.uk/drupal/enabling-wysiwyg-editor-custom-textareas
   */


  // build up buttons
  $form['buttons']['#weight'] = 10;

  return system_settings_form($form);
} // interactivemap_settings