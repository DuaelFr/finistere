<?php
function flux_tourinsoft_updatetourinsoft($node){

	if(!empty($node)){

    $dataList = _flux_tourinsoft_updatetourinsoft($node);

		drupal_set_message(t('Product %productid has been synchronized', array('%productid'=>$dataList['ID'])));
	}

  drupal_goto(drupal_get_path_alias('node/'.$node->nid, $node->language));
}

function flux_tourinsoft_infotourinsoft($node){
  module_load_include('inc', 'module', 'flux');

	if(!empty($node)){
    $dataList['ID'] = $node->field_fl_techid_tx[0]['value'];
    $idModule = $node->field_fl_id_module_tx[0]['value'];
    $identifiant = $node->field_fl_id_bordereau_tx[0]['value'];
    $langue = $node->language;
    $en = FALSE;

    if($langue == 'en'){
      $en = TRUE;
    }

    $query = array(
      'idModule' => $idModule,
      'idOffre' => $dataList['ID'],
      'OBJETTOUR_CODE' => $identifiant,
    );

	}

  drupal_goto('http://cdt29.tourinsoft.com/soft/RechercheDynamique/Syndication/controle/syndication2.asmx/getDetail', $query);
}

function _flux_tourinsoft_updatetourinsoft($node) {
  module_load_include('inc', 'module', 'flux');

  $dataList['ID'] = $node->field_fl_techid_tx[0]['value'];
  $idModule = $node->field_fl_id_module_tx[0]['value'];
  $identifiant = $node->field_fl_id_bordereau_tx[0]['value'];
  $langue = $node->language;
  $en = FALSE;

  if($langue == 'en'){
    $en = TRUE;
  }

  $traitements = array();

  $fluxInfos = new StdClass();
  $fluxInfos->idmodule = $idModule;
  $fluxInfos->identifiant = $identifiant;
  $fluxInfos->en = $en;

  $fieldsConf = flux_fieldsmapping($fluxInfos->identifiant);

  $Sync = new Synchronisation();
  $Sync->init(TRUE, $fluxInfos);
  foreach($Sync->flux as $fluxTmp){
    $fluxInfos = $fluxTmp;
  }

  $Sync->majProduct($dataList, $traitements, $fluxInfos, $fieldsConf, $en);

  return $dataList;
}