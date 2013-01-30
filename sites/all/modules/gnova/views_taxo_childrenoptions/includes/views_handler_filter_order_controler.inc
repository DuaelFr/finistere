<?php
// $Id: views_handler_filter_term_node_tid_depth.inc,v 1.1 2009/06/05 01:26:35 merlinofchaos Exp $
/**
 * 
 */
class views_handler_filter_order_controler extends views_handler_filter{
	
	
	function value_form(&$form, &$form_state) {
		
		if(!empty($form_state['exposed'])){
			
			//Exposed widget
			$form['value'] = array(
				'#type' => 'checkbox',
				'#title' => $this->options['expose']['label'],
			);
			
			/*if (!empty($form_state['exposed']) && !isset($form_state['input'][$this->options['expose']['identifier']])) {
		        $this->value = $form_state['input'][$this->options['expose']['identifier']];
		    }*/
			
		}else{
			//For administration
			$form['condvalue'] = array(
				'#type' => 'textfield',
				'#title' => t('Order by clause'),
				'#description' => t('Enter an order by clause whitch will be applied when the box is checked.'),
				'#default_value' => (isset($this->options['condvalue']) ? $this->options['condvalue'] : ''),
			);
		}
	}
	
	
	function value_submit($form, &$form_state) {
		parent::value_submit($form, &$form_state);
		// prevent array_filter from messing up our arrays in parent submit.
		if(isset($form_state['values']['condvalue'])){
			$this->options['condvalue'] = $form_state['values']['condvalue'];
		}
		
	}
	
	/**
   * Add this filter to the query.
   *
   * Due to the nature of fapi, the value and the operator have an unintended
   * level of indirection. You will find them in $this->operator
   * and $this->value respectively.
   */
  function query() {
  	
  	if(intval($this->value)==1){
  		$this->query->orderby[0]=$this->options['condvalue'];
  	}
  	
  }
  
  
}