<?php

function simple_share_mail_form(&$form_state, $node){
	
	$form = array();
	
	$form['entete'] = array(
		'#value' => '<h1>'.t('Share by mail').'</h1>',
	);
	$form['nid'] = array(
		'#type' => 'hidden',
		'#value' => $node->nid,
	);
	
	
	$form['to'] = array(
		'#type' => 'textfield',
		'#title' => t('Send to'),
		'#required' => TRUE,
	);
	$form['from'] = array(
		'#type' => 'textfield',
		'#title' => t('From'),
		'#required' => TRUE,
	);
	
	$form['subject'] = array(
		'#type' => 'textfield',
		'#title' => t('Subject'),
		'#required' => TRUE,
		'#default_value' => $node->title,
	);
	
	$form['node'] = array(
		'#value' => node_view($node, TRUE),
	);
	
	$form['message'] = array(
		'#type' => 'textarea',
		'#title' => t('Your message'),
		'#required' => FALSE,
	);
	
	$form['submit']=array(
		'#type' => 'submit',
		'#value' => t('Send'),
	);
	
	return $form;
}

function simple_share_mail_form_submit($form_id, &$form_state){
	$vals = $form_state['values'];
	$node = node_load($vals['nid']);
	global $language;
	
	$cnt = '<div class="personalmessage">'.$vals['message'].'</div>'.node_view($node, TRUE);
	
	$params = array(
	    'subject' => $vals['subject'],
	    'body' => $cnt,
	  );
  
  	if(drupal_mail('simple_share', 'simple_share', $vals['to'], $language, $params, $vals['from'])){
  		drupal_set_message(t('Your message has been sent.'));
  	}
	
	drupal_goto('node/'.$vals['nid']);
}