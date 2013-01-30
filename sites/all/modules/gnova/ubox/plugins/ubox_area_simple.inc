<?php
// $Id: ubox_area_simple.inc,v 1.2.2.1 2010/06/21 20:47:21 jmiccolis Exp $

/**
 * Simple custom text box.
 */
class ubox_area_simple extends ubox_area_box {
  /**
   * Implementation of ubox_area_content::options_defaults().
   */
  public function options_defaults() {
    return array();
  }

  /**
   * Implementation of ubox_area_content::options_form().
   */
  public function options_form() {
    if (filter_access($this->options['format'])) {
      $form = array();
      // NO OPTIONS
      return $form;
    }
  }

  /**
   * Implementation of ubox_area_content::render().
   * Met en forme les différentes ubox à l'intérieur d'un ubox_area
   * Retourne ubox_area
   */
  public function render() {
  	global $_domain;
    $content = '';
    
    if (!empty($this->options['body']) && isset($this->options['format'])) {
      $content = check_markup($this->options['body'], $this->options['format'], FALSE);
    }
    
  	/**
  	 * Get Ubox datas to put on Ubox area (=delta)
  	 * Show only datas to current page
     */
     
     $current_url = $_GET["q"];
     	
     /**
      *	Select all ubox node to check which can be display
      */
    $query_domain = $where_domain = "";
    if(!empty($_domain)){
    	$query_domain = "
    		LEFT JOIN {domain_access} d ON node.nid = d.nid
    	";
    	$where_domain = " AND (d.gid = '%d' AND d.realm = 'domain_id')
    	";
    }
		$query = "SELECT node.nid AS nid,
   node_revisions.body AS body,
   node_revisions.format AS body_format,
   node.title AS title,
   node.language AS language,
   node.type AS type,
   node.vid AS vid,
   node.status AS status,
   content_type_ubox.field_ubox_footer_label_value AS field_ubox_footer_label_value,
   content_type_ubox.field_ubox_footer_url_value AS field_ubox_footer_url_value,
   content_type_ubox.field_ubox_header_label_value AS field_ubox_header_label_value,
   content_type_ubox.field_ubox_header_url_value AS field_ubox_header_url_value,
   content_type_ubox.field_ubox_displayedtitle_value AS field_ubox_displayedtitle_value,
   content_type_ubox.field_ubox_footer_label_value AS field_ubox_footer_label_value,
   content_type_ubox.field_ubox_footer_url_value AS field_ubox_footer_url_value,
   content_type_ubox.field_ubox_itemsnb_value AS field_ubox_itemsnb_value,
   content_type_ubox.field_ubox_proportionsdisplay_value AS field_ubox_proportionsdisplay_value,
   content_type_ubox.field_ubox_template_value AS field_ubox_template_value,
   content_type_ubox.field_ubox_region_value AS field_ubox_region_value,
   content_type_ubox.field_ubox_pages_value AS field_ubox_pages_value,
   content_type_ubox.field_ubox_pagesnodisplay_value AS field_ubox_pagesnodisplay_value
 FROM {node} node 
 LEFT JOIN {content_type_ubox} content_type_ubox ON node.vid = content_type_ubox.vid
 LEFT JOIN {node_revisions} node_revisions ON node.vid = node_revisions.vid".$query_domain."
 WHERE node.status <> 0
 AND node.type = 'ubox'
 AND content_type_ubox.field_ubox_region_value = '%s'".$where_domain."
 ORDER BY content_type_ubox.field_ubox_weight_value ASC";
  	
  	$query_item = "SELECT cfue.field_ubox_existingcontent_nid AS nid
		FROM {content_field_ubox_existingcontent} cfue 
		WHERE cfue.vid = %n
		ORDER BY cfue.delta ASC";
  	
  	if(empty($query_domain)){
  		$result = db_query(db_rewrite_sql($query, 'node'), $this->delta);
  	}else{
  		$result = db_query(db_rewrite_sql($query, 'node'), $this->delta, $_domain['domain_id']);
  	}
  	while( $ubox = db_fetch_object($result)){

  		// Vérifie que l'ubox à les droits d'être affichée

  		$node = node_load($ubox->nid);
  		if(node_access('view', $node )){
	  		/**
	  		 *	Pour chaque ubox récupéré, on vérifie qu'elle peut être affichée
	  		 * 	(prise en compte des wildcards)
	  		 */
				$path = drupal_get_path_alias($_GET['q']);
	
				// Compare with the internal and path alias (if any).
				$page_match = drupal_match_path($path, $ubox->field_ubox_pages_value);
				$page_nodisplay_match = drupal_match_path($path, $ubox->field_ubox_pagesnodisplay_value);
				if ($path != $_GET['q'] && !$page_match) {
					$page_match = drupal_match_path($_GET['q'], $ubox->field_ubox_pages_value);
					$page_nodisplay_match = drupal_match_path($_GET['q'], $ubox->field_ubox_pagesnodisplay_value);
				}
	  		if(($page_match || empty($ubox->field_ubox_pages_value)) &&  !$page_nodisplay_match){
		
					/**
					* On récupère les items et les intègre au contenu de l'ubox
					*/
					 
					$result_item = db_query($query_item, $ubox->vid);
					while($niditem = db_fetch_object($result_item)){
						/**
						 * call theme node teaser
						 */
						if(!empty($niditem->nid)){
						
							$node = node_load($niditem->nid);
		
							/* Choix du build_mode à utiliser. Par défaut : teaser pris en compte */
							$node->build_mode = "ubox_".$ubox->field_ubox_template_value;
							$node->ubox_proportionsdisplay = $ubox->field_ubox_proportionsdisplay_value;
							$node->ubox_nbitems = $ubox->field_ubox_itemsnb_value;
							$node->ubox_region = $ubox->field_ubox_region_value;
		
							$ubox->items[] = node_view($node, TRUE);
						}
					}
					
		  		/**
		  		 * On met en forme l'objet ubox qui affichera les items
		  		 */
		  		switch($ubox->field_ubox_proportionsdisplay_value){
						case "1": $ubox->field_ubox_proportionsdisplay_class = 'box_all';break;
						case "0,5": $ubox->field_ubox_proportionsdisplay_class = 'bloc_1_2';break;
						case "0,3": $ubox->field_ubox_proportionsdisplay_class = 'bloc_1_3';break;
						case "0,7": $ubox->field_ubox_proportionsdisplay_class = 'bloc_2_3';break;
						default: $ubox->field_ubox_proportionsdisplay_class = 'box_all';break;
					}
		  		 
		  		 $content .= theme('ubox_box_' . $ubox->field_ubox_template_value, $ubox);
		  	}
		  }
  	}
  	
		if(empty($content)){
			return array();
		}
    $title = isset($this->title) ? check_plain($this->title) : NULL;
    return array(
      'delta' => $this->delta, // Crucial.
      'title' => $title,
      'subject' => $title,
      'content' => $content,
    );
  }
}
