<?php

/**
 * Implementation of hook_views_data_alter().
 */
function views_date_views_data_alter(&$data) {
  foreach ($data as $table_key => $table) {
    foreach ($table as $field_key => $field) {
      if ($new_field = _views_date_make_new_date_field($field)) {
        $data[$table_key][$field_key.'_advanced'] = $new_field;
        if (!isset($data[$table_key][$field_key.'_advanced']['sort']['field'])) {
          $data[$table_key][$field_key.'_advanced']['sort']['field'] = $field_key;
        }
      }
    }
  }
}

/**
 * Helper function for views_date_views_data_alter().
 * Returns a new field definition if applicable, or else returns FALSE.
 */
function _views_date_make_new_date_field($field) {
  // Is there a sort handler? If not, quickly return FALSE.
  if (empty($field['sort'])) {
    return FALSE;
  }

  // Case 1: The current sort handler is 'views_handler_sort_date'.
  if ($field['sort']['handler'] == 'views_handler_sort_date') {
    $field['sort']['type'] = 'int';
    return _views_date_process_new_date_field($field);
  }

  // Case 2: The field is a CCK field of type 'datestamp' or 'datetime'.
  // @todo: Add compatability for the 'date' type.
  $allowed_types = array('datestamp' => 'int', 'datetime' => 'datetime');
  if (!empty($field['field']['access arguments'])) {
    $type = $field['field']['access arguments'][1]['type'];
    if (!empty($allowed_types[$type])) {
      $field['sort']['type'] = $allowed_types[$type];
      return _views_date_process_new_date_field($field);
    }
  }

  // Otherwise, return FALSE.
  return FALSE;
}

function _views_date_process_new_date_field($field) {
  unset($field['field']);
  unset($field['argument']);
  unset($field['filter']);
  $field['title'] .= ' (Advanced)';
  $field['help'] = ( empty($field['help']) ? '' : $field['help'].' - ' ) . 'The date components are separable.';
  $field['sort']['handler'] = 'views_handler_sort_date_advanced';
  return $field;
}

/**
 * Implementation of hook_views_handlers().
 */
function views_date_views_handlers() {
  return array(
    'info' => array(
      'path' => drupal_get_path('module', 'views_date'),
    ),
    'handlers' => array(
      'views_handler_sort_date_advanced' => array(
        'parent' => 'views_handler_sort_date',
      ),
    ),
  );
}
