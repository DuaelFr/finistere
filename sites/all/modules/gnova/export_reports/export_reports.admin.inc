<?php
function export_reports_dblog_top($type){
  module_load_include('inc', 'dblog', 'dblog.admin');
  $output = dblog_top($type);

  $output .= l('Download CSV report', 'admin/reports/search/csv');
  //$output .= l('Download XLS report', 'admin/reports/search/xls');

  return $output;
}

function export_reports_dblog_top_export($type, $export='csv'){
  $header = array(
    array('data' => t('Count'), 'field' => 'count', 'sort' => 'desc'),
    array('data' => t('Message'), 'field' => 'message')
  );

  $result = db_query("SELECT COUNT(wid) AS count, message, variables FROM {watchdog} WHERE type = '%s' GROUP BY message, variables ", $type);

  while ($dblog = db_fetch_object($result)) {
    $variables = unserialize($dblog->variables);
    $gn_db_row[] = array($dblog->count, $variables['%keys']);
  }

  foreach($header as $gnheader){
    $gn_db_header[] = $gnheader['data'];
  }

  $gn_node = new StdClass();
  $gn_node->title = 'searchreport';

  if($export == 'csv'){
    customreports_render_csv($gn_db_header, $gn_db_row, $gn_node);
  }elseif($export == 'xls'){
    customreports_render_xls($gn_db_header, $gn_db_row, $gn_node);
  }
}