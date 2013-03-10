<?php

/**
 * Page callback for the cuss item list
 */
function page_list_cuss(){
	
	$items = cuss_get_list(FALSE);
	$table = array();
	if($items){
		foreach($items as $item){
			$table[] = array(
				l($item->title, 'node/'.$item->nid.'/edit'), 
				(strlen($item->path)>30 ? substr($item->path, 0, 30).'...' : $item->path),
				l(t('Edit'), 'admin/build/cuss/edit/'.$item->cussid),
			);
		}
	}
	
	
	return theme_table(
			array(t('Theme'), t('Path(s)'), t('Actions')),
			$table
		);
}