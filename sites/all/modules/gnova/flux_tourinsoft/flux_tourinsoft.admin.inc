<?php

function flux_tourinsoft_deleteproducts_form($form_state){
	$form['flux_tourinsoft_productsdelete'] = array(
    '#type' => 'textarea',
    '#title' => "Tourinsoft products IDs (Les produits suivants seront supprimées durant la nuit)",
    '#description' => t('Separate ids by , like : HLOBRE029FS00MID,HLOBRE029FS00MIC,HLOBRE029AX00789,HLOBRE029FS00OF1'),
    '#rows' => 10,
    '#cols' => 30,
    '#resizable' => TRUE,
    '#default_value' => variable_get('flux_tourinsoft_productsdelete', ""),
  );

  $products = explode(',', variable_get('flux_tourinsoft_productsdelete', ""));
  foreach($products as $key=>$product) {
    $products[$key] = trim($product);
  }

  $info = 0;

  if(!empty($products)) {
    $placeholders = db_placeholders($products, 'varchar');
    $query = db_query("SELECT count(n.nid) as nb
      FROM {node} n
      INNER JOIN {content_field_fl_techid_tx} cfftt ON n.nid=cfftt.nid
      WHERE cfftt.field_fl_techid_tx_value IN ($placeholders)", $products);
    $result = db_fetch_object($query);
    $info = $result->nb;
  }

  $form['flux_tourinsoft_productsdeleteinfo'] = array(
    '#type' => 'markup',
    '#value' => '<div>' . t('%number products have to be deleted tonight.', array('%number' => $info)) . '</div>',
  );

	$form['submit'] = array(
	  '#type' => 'submit',
	  '#value' => t('Save products to delete'),
	);

  return system_settings_form($form);
}