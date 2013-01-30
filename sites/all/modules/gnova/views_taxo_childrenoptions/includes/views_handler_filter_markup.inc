<?php
// $Id: views_handler_filter_term_node_tid_depth.inc,v 1.1 2009/06/05 01:26:35 merlinofchaos Exp $
/**
 * 
 */
class views_handler_filter_markup extends views_handler_filter{
	
	function option_definition() {
		$options = parent::option_definition();
		
		return $options;
    }
	
	/*function extra_options_form(&$form, &$form_state) {
		parent::extra_options_form($form, $form_state);
		
		$form['orderbyfilter'] = array(
			'#type' => 'textfield',
			'#title' => t('Order by clause'),
			'#default_value' => $this->options['orderbyfilter'],
			'#description' => t('Enter an order by clause whitch will be applied when the box is checked.'),
		);
		
	}*/
	
	function value_form(&$form, &$form_state) {
		parent::value_form($form, $form_state);
		
		if(!empty($form_state['exposed'])){
			//Exposed widget
			$val = '';
			if(isset($this->options['markupend']) && intval($this->options['markupend'])==1){
				$val = $this->options['markupconf'].';;end';
			}else{
				$val = 'start;;'.$this->options['markupconf'];
			}
			
			$form['value'] = array(
				'#value' => $val,
			);
			
		}else{
			//For administration
			$form['markupconf'] = array(
				'#type' => 'textarea',
				'#title' => t('markup code'),
				'#default_value' => (isset($this->options['markupconf']) ? $this->options['markupconf'] : ''),
			);
			$form['markupend'] = array(
				'#type' => 'checkbox',
				'#title' => 'Closing markup',
				'#default_value' => (isset($this->options['markupend']) ? $this->options['markupend'] : 0),
			);
		}
	}
	
	function value_submit($form, &$form_state) {
		
		// prevent array_filter from messing up our arrays in parent submit.
		if(isset($form_state['values']['markupconf'])){
			$this->options['markupconf'] = $form_state['values']['markupconf'];
			$this->options['markupend'] = $form_state['values']['markupend'];
		}
		
	}
	
	
}