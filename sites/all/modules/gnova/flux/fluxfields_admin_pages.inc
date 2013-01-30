<?php


/**
 *	Formulaire d'édition de mapping des fields
 *
 *	@return array $form
 */
function flux_fluxfields_form($form_state, $identifiant) {
  //$sync = new Synchronisation();
  //$dataset = $sync->getFieldsByFluxIdentifiant($identifiant);

  $dataset = module_invoke_all('fluxgetfields', $identifiant);

  $options = flux_getFluxfieldinfo(); // Liste des fonctions disponibles
  
  $conf = flux_fieldsmapping($identifiant);
  
  $header = array('Webservice Field Name', 'Label', 'Function', 'Required');
  
  foreach($dataset as $cle=>$value){
  	$status = array();
  	
  	$similarField = similar_field_with_ws_fieldname($value['systemfieldname']);
  	
  	$form[$value['systemfieldname']]['ws_fieldname'] = array(
  		'#value' => $value['systemfieldname'],
  	);
  	$form[$value['systemfieldname']]['ws_fieldname_' . $value['systemfieldname']] = array(
  		'#value' => $value['systemfieldname'],
  		'#type' => 'hidden'
  	);
  	$form[$value['systemfieldname']]['flux_fieldlabel_' . $value['systemfieldname']] = array(
  		'#type' => 'textfield',
  		'#default_value' => (isset($conf[$value['systemfieldname']]->label) ? $conf[$value['systemfieldname']]->label : ($similarField ? $similarField->label : NULL)),
  	);
  	$form[$value['systemfieldname']]['flux_function_' . $value['systemfieldname']] = array(
			'#type' => 'select',
			'#options' => $options,
			'#default_value' => (isset($conf[$value['systemfieldname']]->fieldfunction) ? $conf[$value['systemfieldname']]->fieldfunction : ($similarField ? $similarField->fieldfunction : NULL)),
		);
	$form[$value['systemfieldname']]['flux_fieldrequired_' . $value['systemfieldname']] = array(
			'#type' => 'checkbox',
			'#default_value' => (isset($conf[$value['systemfieldname']]->required) ? $conf[$value['systemfieldname']]->required : ($similarField ? $similarField->required : 0)),
		);
	
	$form[$value['systemfieldname']]['flux_staticfield_' . $value['systemfieldname']] = array(
			'#type' => 'select',
			'#options' => array(
				0 => t('No'),
				1 => t('Static'),
				2 => t('Can be hidden'),
			),
			'#default_value' => (isset($conf[$value['systemfieldname']]->staticfield) ? $conf[$value['systemfieldname']]->staticfield : ($similarField ? $similarField->staticfield : 0)),
		);
		
	$fields[] = $value['systemfieldname'];
  }
  
  $form['flux_fieldhidden'] = array(
		'#type' => 'hidden',
		'#value' => implode('|', $fields)
	);
  $form['flux_identifiant'] = array(
		'#type' => 'hidden',
		'#value' => $identifiant
	);
	$form['submit'] = array(
	  '#type' => 'submit',
	  '#value' => t('Submit and build'),
	  '#name' => 'build'
	);
	$form['submitnobuild'] = array(
	  '#type' => 'submit',
	  '#value' => t('Only save settings'),
	  '#name' => 'nobuild',
	);
	
  return $form;
}

/**
 *	Soumission du formulaire flux_fluxfields_form (hook_submit)
 *
 */
function flux_fluxfields_form_submit($form_id, $form) {

	$fields = explode('|', $form['values']['flux_fieldhidden']);
	
	foreach($fields as $fieldname){
	
		$nb = db_result(db_query("SELECT count(*) AS nb FROM {flux_fieldsettings} WHERE bordereau_id='%s' AND fieldname='%s'", $form['values']['flux_identifiant'], $form['values']['ws_fieldname_' . $fieldname]));
		
		
		if($nb<=0){
			$res=db_query("INSERT INTO {flux_fieldsettings} (bordereau_id, fieldname, label, fieldfunction, required, staticfield) VALUES ('%s', '%s', '%s', '%s', %d, %d)", 
				$form['values']['flux_identifiant'],
				$form['values']['ws_fieldname_' . $fieldname],
				$form['values']['flux_fieldlabel_' . $fieldname],
				$form['values']['flux_function_' . $fieldname],
				$form['values']['flux_fieldrequired_' . $fieldname],
				$form['values']['flux_staticfield_' . $fieldname]
			);
		}else{
			
			//Avant de mettre à jour la table puis de créer le CT (le nom du cckfield est créé par la fonction de création du CT appelée à la fin du submit)
			//On supprime les données de ce champ dans la table flux_display
			$q = db_query("SELECT ff.* FROM {flux_fieldsettings} AS ff LEFT JOIN {flux_display} AS fd ON ff.cckfieldname=fd.cckfieldname WHERE ff.bordereau_id='%s' AND ff.fieldname='%s'", $form['values']['flux_identifiant'], $form['values']['ws_fieldname_' . $fieldname]);
			
			//Supprime de la table flux_display les champs (cck fields) qui n'ont plus de correspondance avec les cckfields défénis dans flux_fieldsettings
			//SSI la fonction de gestion du champ a été changée
			while($res1 = db_fetch_array($q)){
				if($res1['fieldfunction']!=$form['values']['flux_function_' . $fieldname]){
					db_query("DELETE FROM {flux_display} WHERE bordereau_id='%s' AND cckfieldname='%s'", $form['values']['flux_identifiant'], $res1['cckfieldname']);
				}
			}
			
			$res=db_query("UPDATE {flux_fieldsettings} SET label='%s', fieldfunction='%s', required=%d, staticfield=%d WHERE bordereau_id='%s' AND fieldname='%s'", 
				$form['values']['flux_fieldlabel_' . $fieldname], 
				$form['values']['flux_function_' . $fieldname],
				$form['values']['flux_fieldrequired_' . $fieldname],
				$form['values']['flux_staticfield_' . $fieldname],
				$form['values']['flux_identifiant'],
				$form['values']['ws_fieldname_' . $fieldname]
			);
			
			
		}
		
		if($form['values']['flux_staticfield_' . $fieldname]==1){
			$cckfieldnamefunc = $form['values']['flux_function_' . $fieldname].'_cckfieldname';
			if(function_exists($cckfieldnamefunc)){
				$cckfieldname = $cckfieldnamefunc($fieldname);
				if($cckfieldname){
					$nb = db_result(db_query("SELECT count(*) AS nb FROM {flux_display} WHERE bordereau_id='%s' AND cckfieldname='%s'", $form['values']['flux_identifiant'], $cckfieldname));
					if($nb && intval($nb)>0){
						db_query("DELETE FROM {flux_display} WHERE bordereau_id='%s' AND cckfieldname='%s'", $form['values']['flux_identifiant'], $cckfieldname);
					}
				}
			}
		}
		
		//Supprime de la table flux_display les champs (cck fields) qui n'ont plus de correspondance avec les cckfields défénis dans flux_fieldsettings
		
	}
	if($form['clicked_button']['#name']=='build')
		flux_createContentType($form['values']['flux_identifiant']);
	else
		drupal_set_message(t('Settings have been saved. No change have been made to the content type.'));
	
}


/* Liste des flux (bordereaux) */
function fluxfields_flux_list(){
	$res = db_query("SELECT DISTINCT(field_flux_identifiant_value) AS id FROM {content_type_flux}");
	$bordereaux = array();
	while($bor = db_fetch_array($res)){	
		$adminAccess = user_access('Administer flux content types');
		$adminDisplayLink = l(t('Edit display settings'), 'admin/flux/displayedit/'.$bor['id']);
		$adminCTLink = l(t('Edit fields settings'), 'admin/flux/edit/'.$bor['id']);
		$bordereaux[] = array($bor['id'], ($adminAccess ? $adminCTLink.' / '.$adminDisplayLink : $adminDisplayLink));
	}
	return theme_table(
		array(t('Bordereau'), t('Actions')), 
		$bordereaux
	);
}


function field_display_settings_form($form_state, $identifiant){

	$header = array(t('Webservice Field Name'), t('Default label'), t('Custom label'), t('hide'), t('Display zone'), t('Show value after'), t('Only first value'), t('Weight'));
	
	$confList = flux_fieldsmapping($identifiant);
	$displayConfList = flux_fieldsdisplay($identifiant);

	$after_options = array(
		'<none>' => '- None -',
	);
	
	$admin = user_access('Override fixed display settings');
	
	
	$fkeys = array();
	foreach($confList as $ws_fieldname => $conf){
		$fkeys[$conf->cckfieldname]=$ws_fieldname;
	}
	
	if(is_array($displayConfList) && count($displayConfList)>0){
		
		$dispkeys=array_keys($displayConfList);
		
		foreach($dispkeys as $k){
			$orderedConfList[$fkeys[$k]]=$confList[$fkeys[$k]];
		}
		
		$confList = array_merge($orderedConfList, $confList);
	}
	
	foreach($confList as $ws_fieldname => $conf){
		
		if(intval($conf->staticfield)!==1){
			
			
			$after_options[$conf->cckfieldname] = $conf->label;
	
			$form[$ws_fieldname]['ws_fieldname'] = array(
		  		'#value' => $ws_fieldname,
		  		'#prefix' => (intval($conf->staticfield)>=2 ? '<span style="color:red;font-weight:bold;">' : ''),
		  		'#suffix' => (intval($conf->staticfield)>=2 ? '</span>' : ''),
		  	);
		  	$form[$ws_fieldname]['cckfieldname_'.$ws_fieldname] = array(
		  		'#type' => 'hidden',
		  		'#value' => $conf->cckfieldname,
		  	);
			$form[$ws_fieldname]['ccklabel'] = array(
		  		'#value' => $conf->label,
		  	);
		  	$form[$ws_fieldname]['customlabel_'.$ws_fieldname] = array(
		  		'#type' => 'textfield',
		  		'#size' => 20,
		  		'#default_value' => (isset($displayConfList[$conf->cckfieldname]->label) ? $displayConfList[$conf->cckfieldname]->label : ''),
		  	);
		  	$form[$ws_fieldname]['hide_'.$ws_fieldname] = array(
		  		'#type' => 'checkbox',
		  		'#default_value' => (isset($displayConfList[$conf->cckfieldname]->hide) ? $displayConfList[$conf->cckfieldname]->hide : 0),
		  	);
		  	$form[$ws_fieldname]['zone_'.$ws_fieldname] = array(
		  		'#type' => 'select',
		  		'#default_value' => (isset($displayConfList[$conf->cckfieldname]->zone) ? $displayConfList[$conf->cckfieldname]->zone : '<default>'),
		  		'#options' => get_display_zones(),
		  		'#disabled' => (intval($conf->staticfield)>=2 ? (!$admin ? TRUE : FALSE) : FALSE),
		  	);
		  	$form[$ws_fieldname]['after_'.$ws_fieldname] = array(
		  		'#type' => 'select',
		  		'#default_value' => (isset($displayConfList[$conf->cckfieldname]->after) ? $displayConfList[$conf->cckfieldname]->after : '<none>'),
		  		'#options' => array(),
		  		'#disabled' => (intval($conf->staticfield)>=2 ? (!$admin ? TRUE : FALSE) : FALSE),
		  	);
		  	
		  	$form[$ws_fieldname]['disptype_'.$ws_fieldname] = array(
		  		'#type' => 'select',
		  		'#default_value' => (isset($displayConfList[$conf->cckfieldname]->disptype) ? $displayConfList[$conf->cckfieldname]->disptype : '<none>'),
		  		'#options' => get_display_type(),
		  		'#disabled' => (intval($conf->staticfield)>=2 ? (!$admin ? TRUE : FALSE) : FALSE),
		  	);
		  	
		  	$form[$ws_fieldname]['single_'.$ws_fieldname] = array(
		  		'#type' => 'checkbox',
		  		'#default_value' => (isset($displayConfList[$conf->cckfieldname]->single) ? $displayConfList[$conf->cckfieldname]->single : 0),
		  	);
		  	
		  	$form[$ws_fieldname]['weight_'.$ws_fieldname] = array(
				'#type' => 'weight', 
				'#default_value' => (isset($displayConfList[$conf->cckfieldname]->weight) ? $displayConfList[$conf->cckfieldname]->weight : 0), 
				'#delta' => 100, 
				'#disabled' => (intval($conf->staticfield)>=2 ? (!$admin ? TRUE : FALSE) : FALSE),
			);
		  	
		  	$fields[] = $ws_fieldname;
			
		}
		
	}
	
	
	foreach($confList as $ws_fieldname => $conf){
		$form[$ws_fieldname]['after_'.$ws_fieldname]['#options'] = $after_options;
	}
	
	$form['flux_fieldhidden'] = array(
		'#type' => 'hidden',
		'#value' => implode('|', $fields)
	);
  	$form['flux_identifiant'] = array(
		'#type' => 'hidden',
		'#value' => $identifiant
	);
	$form['submit'] = array(
	  '#type' => 'submit',
	  '#value' => t('Save'),
	);
	
	return $form;
}

function field_display_settings_form_submit($form, &$form_state){

	
	$fields = explode('|', $form_state['values']['flux_fieldhidden']);
	
	foreach($fields as $fieldname){
	
	
		$nb = db_result(db_query("SELECT count(*) AS nb FROM {flux_display} WHERE bordereau_id='%s' AND cckfieldname='%s'", $form_state['values']['flux_identifiant'], $form_state['values']['cckfieldname_' . $fieldname]));
		
		
		if($form_state['values']['cckfieldname_' . $fieldname] == $form_state['values']['after_' . $fieldname]){
			$form_state['values']['after_' . $fieldname] = '<none>';
		}
		
		if($nb<=0){
			$res=db_query("INSERT INTO {flux_display} (bordereau_id, cckfieldname, label, hide, after, zone, single, weight, disptype) VALUES ('%s', '%s', '%s', %d, '%s', '%s', %d, %d, '%s')", 
				$form_state['values']['flux_identifiant'],
				$form_state['values']['cckfieldname_' . $fieldname],
				$form_state['values']['customlabel_' . $fieldname],
				$form_state['values']['hide_' . $fieldname],
				$form_state['values']['after_' . $fieldname],
				$form_state['values']['zone_' . $fieldname],
				$form_state['values']['single_' . $fieldname],
				$form_state['values']['weight_' . $fieldname],
				$form_state['values']['disptype_' . $fieldname]
			);
		}else{
			$res=db_query("UPDATE {flux_display} SET label='%s', hide=%d, after='%s', zone='%s', single=%d, weight=%d, disptype='%s' WHERE bordereau_id='%s' AND cckfieldname='%s'", 
				$form_state['values']['customlabel_' . $fieldname],
				$form_state['values']['hide_' . $fieldname],
				$form_state['values']['after_' . $fieldname],
				$form_state['values']['zone_' . $fieldname],
				$form_state['values']['single_' . $fieldname],
				$form_state['values']['weight_' . $fieldname],
				$form_state['values']['disptype_' . $fieldname],
				$form_state['values']['flux_identifiant'],
				$form_state['values']['cckfieldname_' . $fieldname]
			);
		}
		
	}
	drupal_set_message('Display options has been saved');
}



function repair_nodes_page($vid){
	$voc = taxonomy_vocabulary_load($vid);
	dsm($voc);
	repair_term_node($vid);
	return '';
}
