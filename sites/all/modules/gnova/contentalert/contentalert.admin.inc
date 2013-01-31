<?php
function contentalert_admin_form(){
  $form = array();
  $form['contentalert'] = array(
    '#type' => 'fieldset',
    '#title' => t("Content Alert mail settings"),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
  $form['contentalert']['contentalert_mail_title'] = array(
    '#type' => 'textfield',
    '#title' => "Mail title for Alert",
    '#default_value' => variable_get('contentalert_mail_title', ""),
  );
  $form['contentalert']['contentalert_mail_message'] = array(
    '#type' => 'textarea',
    '#title' => "Mail message for Alert",
    '#rows' => 10,
    '#cols' => 30,
    '#resizable' => TRUE,
    '#default_value' => variable_get('contentalert_mail_message', ""),
  );
  $form['contentalert']['help'] = array(
    '#type'          => 'fieldset',
    '#collapsible'   => TRUE,
    '#collapsed'     => TRUE,
    '#title'         => t('Placeholder tokens'),
    '#description'   => t("The following placeholder tokens can be used in both title and message. When used in a title or message, they will be replaced with the appropriate values."),
  );
  if (module_exists('token')) {
    // This code depends on a patch still under review at http://drupal.org/node/127072.
    // $form['help']['tokens'] = array('#value' => theme('token_help', array('global', 'node', 'user')), );
    // This is overkill, but is necessary until this patch is committed.
    $form['contentalert']['help']['tokens'] = array('#value' => theme('token_help', 'contentalert') . theme('token_help', 'all') . theme('token_help', 'user') );
  }
  else {
    $form['contentalert']['help']['#description'] = t("To use dynamic placeholder tokens, download and install the <a href='@token'>Token module</a> from Drupal.org.", array('@token' => 'http://www.drupal.org/project/token'));
    $form['help']['#collapsible'] = FALSE;
    $form['help']['#collapsed'] = FALSE;
  }


  /**
   * Source:
   * http://stackoverflow.com/questions/5624255/attach-wysiwyg-to-custom-drupal-form
   * http://www.thecarneyeffect.co.uk/drupal/enabling-wysiwyg-editor-custom-textareas
   */


  // build up buttons
  $form['buttons']['#weight'] = 10;

  return system_settings_form($form);
}