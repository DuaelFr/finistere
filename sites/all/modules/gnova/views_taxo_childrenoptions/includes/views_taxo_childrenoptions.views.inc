<?php

/**
 * Implementation of hook_views_data_alter().
 */
function views_taxo_childrenoptions_views_data_alter(&$data) {

	$data['node']['term_node_tid_depth_parent'] = array(
		'group' => 'Gnova',
		'title' => t('Term ID (by parent term selection)'),
		'help' => t('Provide the ability to dynamize the available options in exposed filters.'),
		'real field' => 'vid',
		/*'argument' => array(
			'handler' => 'views_handler_argument_term_node_tid_depth',
			'accept depth modifier' => TRUE,
		),*/
		'filter' => array(
			'handler' => 'views_handler_filter_term_node_tid_depth_parent',
		),
	);
	$data['node']['order_controler'] = array(
		'group' => 'Gnova',
		'title' => t('Sorting controler'),
		'help' => t('Give the ability to control sorting with exposed filter'),
		'filter' => array(
			'handler' => 'views_handler_filter_order_controler',
		),
	);
}
/**
 * Implementation of hook_views_handlers().
 */
function views_taxo_childrenoptions_views_handlers() {
	return array(
		'info' => array(
			'path' => drupal_get_path('module', 'views_taxo_childrenoptions') . '/includes',
		),
		'handlers' => array(
			'views_handler_filter_term_node_tid_depth_parent' => array(
				'parent' => 'views_handler_filter_term_node_tid_depth',
			),
			'views_handler_filter_order_controler' => array(
				'parent' => 'views_handler_filter',
			),
		),
	);
}
