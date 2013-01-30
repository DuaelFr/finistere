<?php
// $Id: views_handler_filter_term_node_tid_depth.inc,v 1.1 2009/06/05 01:26:35 merlinofchaos Exp $
/**
 * 
 */
class views_handler_filter_term_node_tid_depth_parent extends views_handler_filter_term_node_tid_depth{
	
	function operator_options() {
		return array(
			'or' => t('Is one of'),
		);
	}
	
	function option_definition() {
		$options = parent::option_definition();
		
		$options['parentchildren'] = array('default' => 0);
		
		return $options;
	}
	
	function extra_options_form(&$form, &$form_state) {
		parent::extra_options_form($form, $form_state);
		
		$form['parentchildren'] = array(
			'#type' => 'checkbox',
			'#title' => t('Parent'),
			'#default_value' => $this->options['parentchildren'],
			'#description' => t('Only select parent term, and all children terms will be available.'),
		);
	}
	
	function value_form(&$form, &$form_state) {
		$prevtype=$this->options['type'];
		
		if(empty($form_state['exposed'])){
			
			//$this->options['type']='select';
			parent::value_form($form, $form_state);
			//$this->options['type']=$prevtype;
		
		}else{
			parent::value_form($form, $form_state);
			if ($this->options['type'] == 'textfield' && !empty($form_state['exposed'])) {
				if ($this->options['limit']) {
					$tids = $this->options['value'];
					if(is_array($tids) && count($tids)>0)
						$form['value']['#autocomplete_path'] = 'childrenoptions/taxonomy/autocomplete/' . $tids[0];
				}
			}
		}
	}
	
	 function value_validate(&$form, &$form_state) {
	    // We only validate if they've chosen the text field style.
	    if ($this->options['type'] != 'textfield' /*|| empty($form_state['exposed'])*/) {
	      return;
	    }
	//dsm($form_state['values']['options']['value']);
	    $values = drupal_explode_tags($form_state['values']['options']['value']);
	    $tids = $this->validate_term_strings($form['value'], $values);
		//dsm($tids);
	    if ($tids) {
	      $form_state['values']['options']['value'] = $tids;
	    }
	  }
	
	/**
   * When using exposed filters, we may be required to reduce the set.
   * 
   * ICI ON REECRIT CETTE FONCTION POUR OBTENIR LA LISTE DES FILS.
   * NE FONCTIONNE QU'AVEC LA SELECTION D'UN SEUL TERME (dans la conf)
   * 
   */
  function reduce_value_options($input = NULL) {
    if (!isset($input)) {
      $input = $this->value_options;
    }
    
    $tids = array_keys($this->options['value']);
    
	foreach($tids as $seltid){
		$term = taxonomy_get_term($seltid);
    
	    $options = array();
	   
	    if($term){
	    	//Récupérer la liste des fils du terme
	        $children = taxonomy_get_children($term->tid);
	        
	        if($children && count($children)>0){
	        	foreach($children as $tid => $child){
	        		$option = new stdClass();
	        		$option->option = array(
	        			$tid => $child->name,
	        		);
	        		$options[$tid]=$option;
	        	}
	        }
	    }
	}
	
	    
    return $options;
    
  }
	
}