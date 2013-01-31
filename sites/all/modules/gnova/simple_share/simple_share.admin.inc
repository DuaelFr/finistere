<?php

/**
 * @file
 * Configuration options for Simple Share social network links.
 */

/**
 * Menu callback; Settings administration.
 */
function simple_share_admin_settings() {
  $form['simple_share_node_types'] = array(
    '#type'          => 'checkboxes',
    '#title'         => t('Node types'),
    '#description'   => t('Choose which node types to display the share links on.'),
    '#default_value' => variable_get('simple_share_node_types', array()),
    '#options'       => node_get_types('names'),
  );

  $form['simple_share_teaser'] = array(
    '#type'          => 'checkbox',
    '#title'         => t('Display in teaser view'),
    '#description'   => t('If enabled, the share links will appear in node teasers. If disabled, they will only appear on the full node page.'),
    '#default_value' => variable_get('simple_share_teaser', 1),
  );

  $form['simple_share_weight'] = array(
    '#type'          => 'weight',
    '#delta'         => 10,
    '#description'   => t('Where you want the share links to appear in the node. Negative numbers are rendered earlier, positive numbers are rendered later.'),
    '#title'         => t('Weight'),
    '#default_value' => variable_get('simple_share_weight', 0),
  );

  $form['simple_share_sites'] = array(
    '#type'          => 'checkboxes',
    '#title'         => t('Enabled share links'),
    '#description'   => t('Choose which websites you would like to enable a share link for.'),
    '#default_value' => variable_get('simple_share_sites', array()),
    '#options'       => array(),
  );
  
  $infos = get_simple_share_infos();
  foreach($infos as $id => $info){
  	$form['simple_share_sites']['#options'][$id] = $info['name'];
  }

  $form['simple_share_max_desc_length'] = array(
    '#type'          => 'textfield',
    '#maxlength'     => 3,
    '#size'          => 3,
    '#description'   => t('Define the maximum description length passed through the link. Anything over 100 is excessive.'),
    '#title'         => t('Maximum description length'),
    '#default_value' => variable_get('simple_share_max_desc_length', 50),
  );

  return system_settings_form($form);
}

function simple_share_admin(){

	$form=array();
	$form = system_settings_form($form);
	$types = node_get_types();
	$conf = variable_get('simple_share_conf', array());
	$infos = get_simple_share_infos();

  $form['simple_share_title_default'] = array(
    '#type'          => 'textfield',
    '#title'         => t('Default box title'),
    '#default_value' => variable_get('simple_share_title_default', 'Share this'),
    '#weight'        => -10,
  );
	
	$form['simple_share_teaser'] = array(
	    '#type'          => 'checkbox',
	    '#title'         => t('Display in teaser view'),
	    '#description'   => t('If enabled, the share links will appear in node teasers. If disabled, they will only appear on the full node page.'),
	    '#default_value' => (isset($conf['simple_share_teaser']) ? $conf['simple_share_teaser'] : 0),
	  );
	
	  $form['simple_share_weight'] = array(
	    '#type'          => 'weight',
	    '#delta'         => 10,
	    '#description'   => t('Where you want the share links to appear in the node. Negative numbers are rendered earlier, positive numbers are rendered later.'),
	    '#title'         => t('Weight'),
	    '#default_value' => (isset($conf['simple_share_weight']) ? $conf['simple_share_weight'] : 0),
	  );
	
	
	foreach($types as $name => $type){
	
		$form['simpleshare_'.$name] = array(
	  		'#type' => 'fieldset',
	  		'#collapsible' => TRUE,
	  		'#collapsed' => TRUE,
	  		'#title' => $type->name,
	  	);
		$form['simpleshare_'.$name]['ena_'.$name] = array(
			'#type' => 'checkbox',
			'#title' => t('Enable'),
		);
		if(isset($conf['simpleshare_'.$name]['ena'])){
			$form['simpleshare_'.$name]['ena_'.$name]['#default_value'] = $conf['simpleshare_'.$name]['ena'];
		}
		
		$form['simpleshare_'.$name]['custom_title_'.$name] = array(
			'#type' => 'textfield',
			'#title' => t('Custom box title for this CT'),
		);
		if(isset($conf['simpleshare_'.$name]['custom_title'])){
			$form['simpleshare_'.$name]['custom_title_'.$name]['#default_value'] = $conf['simpleshare_'.$name]['custom_title'];
		}
		
		$form['simpleshare_'.$name]['ct_sites_'.$name] = array(
			'#type' => 'checkboxes',
			'#title' => t('Enabled share types'),
			'#options' => array(),
		);
		foreach($infos as $site => $info){
			$form['simpleshare_'.$name]['ct_sites_'.$name]['#options'][$site] = $info['name'];
		}
		if(isset($conf['simpleshare_'.$name]['ct_sites'])){
			$form['simpleshare_'.$name]['ct_sites_'.$name]['#default_value'] = $conf['simpleshare_'.$name]['ct_sites'];
		}
		
	}

	$form['#submit'] = array('simple_share_admin_submit');
	return $form;
}

function simple_share_admin_submit($form_id, &$form_state){
	$types = node_get_types();
	$conf = variable_get('simple_share_conf', array());
	$infos = get_simple_share_infos();
	$vals = $form_state['values'];

  variable_set('simple_share_title_default', $vals['simple_share_title_default']);
	
	$conf['simple_share_teaser'] = $vals['simple_share_teaser'];
	$conf['simple_share_weight'] = $vals['simple_share_weight'] ;
	
	foreach($types as $name => $type){
		$conf['simpleshare_'.$name]['ena'] = $vals['ena_'.$name];
		$conf['simpleshare_'.$name]['custom_title'] = $vals['custom_title_'.$name];
		$conf['simpleshare_'.$name]['ct_sites'] = $vals['ct_sites_'.$name];
	}
	
	variable_set('simple_share_conf', $conf);
	
	drupal_set_message('Configuration has been saved');
	
}