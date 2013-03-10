<?php

/**
 * Implementation of hook_user_default_permissions().
 */
function feature_content_pages_user_default_permissions() {
  $permissions = array();

  // Exported permission: filter and manage site content
  $permissions['filter and manage site content'] = array(
    'name' => 'filter and manage site content',
    'roles' => array(
      '0' => 'Manager',
      '1' => 'Responsable publication',
    ),
  );

  return $permissions;
}
