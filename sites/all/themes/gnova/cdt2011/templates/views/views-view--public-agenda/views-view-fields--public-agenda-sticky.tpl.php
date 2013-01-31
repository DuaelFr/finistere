

<div class="ubox_item">
	
	<div class="ubox_item_content lys">
		<div class="date">
			<?php print (isset($fields['field_fl_date_debut_date_value']) && isset($fields['field_fl_date_fin_date_value'])? t('from').' '.$fields['field_fl_date_debut_date_value']->content.' '.t('to').' '.$fields['field_fl_date_fin_date_value']->content : t('On').' '.$fields['field_fl_date_debut_date_value']->content); ?>
		</div>
		<h3><?php print $fields['title']->content; ?></h3>
	</div>
	
	<?php print $fields['field_event_big_image_fid']->content; ?>

</div>