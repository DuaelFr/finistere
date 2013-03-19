<?php

/**
 * List of tables whose *data* is skipped by the 'sql-dump' and 'sql-sync'
 * commands when the "--structure-tables-key=common" option is provided.
 * You may add specific tables to the existing array or add a new element.
 */
$options['structure-tables']['common'] = array(
  'cache',
  'cache_block',
  'cache_content',
  'cache_filter',
  'cache_form',
  'cache_gc_map',
  'cache_gc_smap',
  'cache_geonames',
  'cache_gmaps_geocode',
  'cache_gmaps_map',
  'cache_gmaps_smap',
  'cache_gv_map',
  'cache_gv_map_result',
  'cache_gv_smap',
  'cache_gv_smap_result',
  'cache_location',
  'cache_menu',
  'cache_page',
  'cache_path',
  'cache_update',
  'cache_views',
  'cache_views_data',
  'boost_cache',
  'boost_cache_relationships',
  'boost_cache_settings',
  'boost_clearcache',
  'boost_crawler',
  'ctools_css_cache',
  'ctools_object_cache',
  'domain_2_cache_block',
  'domain_2_cache_menu',
  'domain_2_cache_views',
  'domain_2_cache_views_data',
  'domain_2_views_object_cache',
  'flood',
  'search_dataset',
  'search_index',
  'search_node_links',
  'search_total',
  'sessions',
  'views_object_cache',
  'watchdog',
);

$command_specific['sql-dump'] = array(
  'verbose' => TRUE,
  'structure-tables-key' => 'common',
  'gzip' => TRUE,
  'ordered-dump' => TRUE,
  'result-file' => '/home/finisteretourisme/BACKUPS/drush/database_' . date('Y-m-d-H-i-s') . '.sql',
);

$command_specific['archive-dump'] = array_merge($command_specific['sql-dump'], array(
  'verbose' => TRUE,
  'destination' => '/home/finisteretourisme/BACKUPS/drush/sources_' . date('Y-m-d-H-i-s') . '.tar',
  'overwrite' => TRUE,
  'tar-options' => "--exclude='.git' --exclude='.svn' --exclude='sites/default/files' --exclude='application-mobile' --exclude='cache' --exclude='facebook' --exclude='finistere-affaires' --exclude='integration' --exclude='marque-blanche' --exclude='monfinistere' --exclude='newsletters' --exclude='newweb.finisteretourisme.com' --exclude='ressources-blog-appli' --exclude='signatures-mail' --exclude='smswall' --exclude='stats'",
));
