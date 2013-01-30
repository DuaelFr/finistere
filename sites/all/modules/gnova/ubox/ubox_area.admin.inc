<?php
// $Id: ubox.admin.inc,v 1.5.2.4 2010/07/26 19:31:53 jmiccolis Exp $

/**
 * Generate form for creating new ubox.
 */
function ubox_area_add_form($form_state, $plugin_key) {
  $form = ubox_area_box_form(array('ubox_area' => ubox_area_factory($plugin_key)));
  $form['delta'] = array(
    '#type' => 'textfield',
    '#title' => t('Machine name'),
    '#description' => t('Lowercase letters, numbers and underscores only'),
    '#required' => true,
    '#element_validate' => array('ubox_area_validate_delta'),
    '#size' => 32,
    '#maxlength' => 32,
    '#weight' => -1,
  );
  $form['submit']['#attributes']['class'] = '';

  return $form;
}

/**
 * Validate handler for box delta.
 */
function ubox_area_validate_delta($element, &$form_state) {
  if (!preg_match('!^[a-z0-9_]+$!', $element['#value'])) {
    form_error($element, t('The machine-readable name must contain only lowercase letters, numbers, and underscores.'));
  }
  if ((strpos($element['#value'], 'ubox_area_add__') === 0) || ubox_area_load($element['#value'])) {
    form_error($element, t('The machine-readable name is already taken.'));
  }
}

/**
 * Submit handler for box_add_form.
 */
function ubox_area_add_form_submit($form, &$form_state) {
  $ubox_area = ubox_area_factory($form_state['values']['plugin_key'], $form_state['values']);
  $ubox_area->save();
  drupal_set_message(t('%name has been created.', array('%name' => $ubox_area->description)));
  $form_state['redirect'] = 'admin/build/block';
}

/**
 * Box deletion form.
 */
function ubox_area_delete_form($form_state, $ubox) {
  $form['delta'] = array('#type' => 'hidden', '#value' => $ubox->delta);
  if (($ubox->export_type & EXPORT_IN_DATABASE) && ($ubox->export_type & EXPORT_IN_CODE)) {
    return confirm_form($form, t('Are you sure you want to revert the block %name? Userfriendly blocks which use this block will disappear.', array('%name' => $ubox->title)), 'admin/build/block', '', t('Revert'), t('Cancel'));
  }
  elseif (!($box->export_type & EXPORT_IN_CODE)) {
    return confirm_form($form, t('Are you sure you want to delete the block %name? Userfriendly blocks which use this block will disappear.', array('%name' => $ubox->title)), 'admin/build/block', '', t('Delete'), t('Cancel'));
  }
  drupal_not_found();
  die;
}

/**
 * Submit handler for ubox_area_delete_form
 */
function ubox_area_delete_form_submit($form, &$form_state) {
  ubox_area_load($form_state['values']['delta'])->delete();
  $form_state['redirect'] = 'admin/build/block';
}
