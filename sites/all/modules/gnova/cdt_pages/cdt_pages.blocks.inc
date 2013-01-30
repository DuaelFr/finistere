<?php


function cdt_pages_block($op = 'list', $delta = 0, $edit = array()) {
  if ($op == 'list') {
    $blocks['cdt_pages_panier'] = array(
      'info' => 'CDT: Panier',
      'cache' => BLOCK_CACHE_PER_PAGE,
      'status' => 1,
      'region' => 'header',
      'weight' => 50
    );

    return $blocks;
  }
  elseif ($op == 'view') {
    switch ($delta) {
      case 'cdt_pages_panier':
        return cdt_pages_block_panier();
        break;
    }
  }

} // gn_ot_block


function cdt_pages_block_panier() {
  return array(
    'subject' => '',
    'content' => '<div id="open-system-widget-panier-script"></div>
<div id="container-widget-panier">'.t('My basket').'<div id="widget-panier"></div></div>',
  );
} // gn_ot_block_tag
