<?php

/**
 * Implementation of hook_views_default_views().
 */
function gnova_href_views_default_views() {
  $backref_view = &_gnova_href_backref_main_view();
  return array(
    $backref_view->name => $backref_view,
  );
}

function &_gnova_href_backref_main_view(){
	$view = new view;
	$view->name = 'gnova_href_backref_main';
	$view->description = 'Main view for back reference';
	$view->tag = '';
	$view->view_php = '';
	$view->base_table = 'node';
	$view->is_cacheable = FALSE;
	$view->api_version = 2;
	$view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */
	$handler = $view->new_display('default', 'Defaults', 'default');
	$handler->override_option('fields', array(
	  'nid' => array(
	    'label' => 'Nid',
	    'alter' => array(
	      'alter_text' => 0,
	      'text' => '',
	      'make_link' => 0,
	      'path' => '',
	      'link_class' => '',
	      'alt' => '',
	      'prefix' => '',
	      'suffix' => '',
	      'target' => '',
	      'help' => '',
	      'trim' => 0,
	      'max_length' => '',
	      'word_boundary' => 1,
	      'ellipsis' => 1,
	      'html' => 0,
	      'strip_tags' => 0,
	    ),
	    'empty' => '',
	    'hide_empty' => 0,
	    'empty_zero' => 0,
	    'link_to_node' => 0,
	    'exclude' => 1,
	    'id' => 'nid',
	    'table' => 'node',
	    'field' => 'nid',
	    'relationship' => 'none',
	  ),
	  'title' => array(
	    'label' => '',
	    'alter' => array(
	      'alter_text' => 0,
	      'text' => '',
	      'make_link' => 0,
	      'path' => '',
	      'link_class' => '',
	      'alt' => '',
	      'prefix' => '',
	      'suffix' => '',
	      'target' => '',
	      'help' => '',
	      'trim' => 0,
	      'max_length' => '',
	      'word_boundary' => 1,
	      'ellipsis' => 1,
	      'html' => 0,
	      'strip_tags' => 0,
	    ),
	    'empty' => '',
	    'hide_empty' => 0,
	    'empty_zero' => 0,
	    'link_to_node' => 1,
	    'exclude' => 0,
	    'id' => 'title',
	    'table' => 'node',
	    'field' => 'title',
	    'relationship' => 'none',
	  ),
	));
	$handler->override_option('arguments', array(
	  'field_hqitem_parent_nid' => array(
	    'default_action' => 'not found',
	    'style_plugin' => 'default_summary',
	    'style_options' => array(),
	    'wildcard' => 'all',
	    'wildcard_substitution' => 'All',
	    'title' => '',
	    'breadcrumb' => '',
	    'default_argument_type' => 'fixed',
	    'default_argument' => '',
	    'validate_type' => 'node',
	    'validate_fail' => 'not found',
	    'break_phrase' => 0,
	    'not' => 0,
	    'id' => 'field_hqitem_parent_nid',
	    'table' => 'node_data_field_hqitem_parent',
	    'field' => 'field_hqitem_parent_nid',
	    'validate_user_argument_type' => 'uid',
	    'validate_user_roles' => array(
	      '2' => 0,
	    ),
	    'relationship' => 'none',
	    'default_options_div_prefix' => '',
	    'default_argument_fixed' => '',
	    'default_argument_user' => 0,
	    'default_argument_php' => '',
	    'validate_argument_node_type' => array(
	      'hqitem' => 0,
	      'page' => 0,
	      'story' => 0,
	    ),
	    'validate_argument_node_access' => 0,
	    'validate_argument_nid_type' => 'nid',
	    'validate_argument_vocabulary' => array(
	      '1' => 0,
	    ),
	    'validate_argument_type' => 'tid',
	    'validate_argument_transform' => 0,
	    'validate_user_restrict_roles' => 0,
	    'validate_argument_php' => '',
	  ),
	));
	$handler->override_option('access', array(
	  'type' => 'none',
	));
	$handler->override_option('cache', array(
	  'type' => 'none',
	));
	$handler = $view->new_display('block', 'DisplayPageChildren', 'block_1');
	$handler->override_option('row_plugin', 'node');
	$handler->override_option('row_options', array(
	  'relationship' => 'none',
	  'build_mode' => 'teaser',
	  'links' => 0,
	  'comments' => 0,
	));
	$handler->override_option('block_description', 'DisplayPageChildren');
	$handler->override_option('block_caching', -1);

	return $view;
}