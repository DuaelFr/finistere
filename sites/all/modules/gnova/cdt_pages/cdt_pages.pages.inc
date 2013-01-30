<?php


function reservez_sejwe_weekend_main(){
	
	drupal_add_css(drupal_get_path('theme', 'cdt2011').'/css/style_INTERFACE_RESA.css');
	
	$out='';
	
	$th_view = views_get_view('reservez_sejwe_weekend_themes');
	
	$topleft = $th_view->execute_display();
	
	$tb_view = views_get_view('sejwe_forecast_list_weekend');
	
	$bottomleft = $tb_view->execute_display();
	
	$br_view = views_get_view('sejwe_forecast_notreidee_weekend');
	$br_view->set_display('default');
	$br_view->set_items_per_page(1);
	$br_view->execute('default');

  if(sizeof($br_view->result) > 0){
  	$bottomright = $br_view->render();
  }
	
	$out .= theme('cdtpages_sejwe-main', t('Book your weekend in Finistère'), $topleft, NULL, $bottomleft, t('Our weekend offers'), $bottomright, t('Our journey idea'), 'fr');
	
	return $out;
	
}

function reservez_sejwe_weekend_main_en(){
	
	drupal_add_css(drupal_get_path('theme', 'cdt2011').'/css/style_INTERFACE_RESA.css');
	
	$out='';
	
	$th_view = views_get_view('reservez_sejwe_weekend_themes_en');
	
	$topleft = $th_view->execute_display();
	
	$tb_view = views_get_view('sejwe_forecast_list_weekend_en');
	
	$bottomleft = $tb_view->execute_display();
	
	$br_view = views_get_view('sejwe_forecast_notreidee_week_en');
	$br_view->set_display('default');
	$br_view->set_items_per_page(1);
	$br_view->execute('default');

  if(sizeof($br_view->result) > 0){
  	$bottomright = $br_view->render();
  }
	
	$out .= theme('cdtpages_sejwe-main', t('Book your weekend in Finistère'), $topleft, NULL, $bottomleft, t('Our weekend offers'), $bottomright, t('Our journey idea'), 'uk');
	
	return $out;
	
}

function reservez_sejwe_sejour_main(){
	
	drupal_add_css(drupal_get_path('theme', 'cdt2011').'/css/style_INTERFACE_RESA.css');
	
	$out='';
	
	$th_view = views_get_view('reservez_sejwe_sejour_themes');
	
	$topleft = $th_view->execute_display();
	
	$tb_view = views_get_view('sejwe_forecast_list_sejour');
	
	$bottomleft = $tb_view->execute_display();
	
	$br_view = views_get_view('sejwe_forecast_notreidee_sejour');
	$br_view->set_display('default');
	$br_view->set_items_per_page(1);
	$br_view->execute('default');

  if(sizeof($br_view->result) > 0){
  	$bottomright = $br_view->render();
  }
	
	$out .= theme('cdtpages_sejwe-main', t('Book your journey in Finistère'), $topleft, NULL, $bottomleft, t('Our journey offers'), $bottomright, t('Our journey idea'), 'fr');
	
	return $out;
	
}

function reservez_sejwe_sejour_main_en(){
	
	drupal_add_css(drupal_get_path('theme', 'cdt2011').'/css/style_INTERFACE_RESA.css');
	
	$out='';
	
	$th_view = views_get_view('reservez_sejwe_sejour_themes_en');
	
	$topleft = $th_view->execute_display();
	
	$tb_view = views_get_view('sejwe_forecast_list_sejour_en');
	
	$bottomleft = $tb_view->execute_display();
	
	$br_view = views_get_view('sejwe_forecast_notreidee_sej_en');
	$br_view->set_display('default');
	$br_view->set_items_per_page(1);
	$br_view->execute('default');

  if(sizeof($br_view->result) > 0){
  	$bottomright = $br_view->render();
  }
	
	$out .= theme('cdtpages_sejwe-main', t('Book your journey in Finistère'), $topleft, NULL, $bottomleft, t('Our journey offers'), $bottomright, t('Our journey idea'), 'uk');
	
	return $out;
	
}

function public_agenda(){

	$out='';
	
	drupal_add_css(drupal_get_path('theme', 'cdt2011').'/css/style_AGENDA.css');
	
	$view = views_get_view('public_agenda_sticky');
	$eventssticky = $view->execute_display();
	
	$view = views_get_view('public_agenda');
	
	
	foreach($view->display['default']->display_options['filters'] as $filId => $filter){
		if(isset($_GET[$filId])){
			if($filter['form_type']=='date_popup'){
				$filter['value']['value'] = $_GET[$filId]['value']['date'].' 00:00:00';
				$view->set_item('default', 'filter', $filId, $filter);
			}else{
				
				$filter['value']['value'] = $_GET[$filId];
				$view->set_item('default', 'filter', $filId, $filter);
			}
		}
	}
	
	$events = $view->execute_display();
	
	$nids = array();
	if(count($view->result)>0){
		
		foreach($view->result as $res){
			
			$nids[]=$res->nid;
				
		}
		$nids = implode('-', $nids);
	}
	
	
	
	$out .= theme('cdtpages_publicagenda', t('Agenda'), $eventssticky, $events, NULL, $nids);
	
	
	return $out;
}


