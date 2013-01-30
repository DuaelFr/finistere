<?php
function cdt_carnet_settings() {
  $form['#tree'] = false;

  // textarea & format (format needed to have the wysiwyg)
  $form['cdt_carnet']['cdt_carnet_description'] = array(
    '#type' => 'textarea',
    '#title' => "Bookmark page description",
    '#rows' => 10,
    '#cols' => 30,
    '#resizable' => TRUE,
    '#default_value' => variable_get('cdt_carnet_description', ""),
  );
  $form['cdt_carnet']['format'] = filter_form(FILTER_FORMAT_DEFAULT, null, array('cdt_carnet'));

  $form['cdt_carnet']['cdt_carnet_share'] = array(
    '#type' => 'fieldset',
    '#title' => t("Bookmark"),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
  $form['cdt_carnet']['cdt_carnet_share']['cdt_carnet_share_title'] = array(
    '#type' => 'textfield',
    '#title' => "Bookmark title",
    '#default_value' => variable_get('cdt_carnet_share_title', ""),
  );
  $form['cdt_carnet']['cdt_carnet_share']['cdt_carnet_share_message'] = array(
    '#type' => 'textarea',
    '#title' => "Bookmark message",
    '#rows' => 10,
    '#cols' => 30,
    '#resizable' => TRUE,
    '#default_value' => variable_get('cdt_carnet_share_message', ""),
  );


  /**
   * Source:
   * http://stackoverflow.com/questions/5624255/attach-wysiwyg-to-custom-drupal-form
   * http://www.thecarneyeffect.co.uk/drupal/enabling-wysiwyg-editor-custom-textareas
   */


  // build up buttons
  $form['buttons']['#weight'] = 10;

  return system_settings_form($form);
} // cdt_carnet_settings