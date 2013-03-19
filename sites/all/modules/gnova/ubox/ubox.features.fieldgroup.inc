<?php

/**
 * Implementation of hook_fieldgroup_default_groups().
 */
function ubox_fieldgroup_default_groups() {
  $groups = array();

  // Exported group: group_ubox_footer
  $groups['ubox-group_ubox_footer'] = array(
    'group_type' => 'standard',
    'type_name' => 'ubox',
    'group_name' => 'group_ubox_footer',
    'label' => 'Footer Box',
    'settings' => array(
      'form' => array(
        'style' => 'fieldset_collapsed',
        'description' => '',
      ),
      'display' => array(
        'description' => '',
        'teaser' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        'full' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        '4' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        '2' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        '3' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        'token' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        'label' => 'above',
      ),
    ),
    'weight' => '11',
    'fields' => array(
      '0' => 'field_ubox_footer_label',
      '1' => 'field_ubox_footer_url',
    ),
  );

  // Exported group: group_ubox_header
  $groups['ubox-group_ubox_header'] = array(
    'group_type' => 'standard',
    'type_name' => 'ubox',
    'group_name' => 'group_ubox_header',
    'label' => 'Header box',
    'settings' => array(
      'form' => array(
        'style' => 'fieldset_collapsed',
        'description' => '',
      ),
      'display' => array(
        'description' => '',
        'teaser' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        'full' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        '4' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        '2' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        '3' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        'token' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        'label' => 'above',
      ),
    ),
    'weight' => '10',
    'fields' => array(
      '0' => 'field_ubox_header_label',
      '1' => 'field_ubox_header_url',
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Footer Box');
  t('Header box');

  return $groups;
}
