
<div class="box_agenda clearfix file-item">
	<?php print $fields['field_fl_photos_imgs_fid']->content; ?>
	<div class="content_box_agenda">
		
		<h3><?php print $fields['title']->content.(isset($fields['field_fl_categorie_strs_value']) ? ' - '.$fields['field_fl_categorie_strs_value']->content : '').cdt2011_new_norm($fields); ?></h3>
		<div class="date_agenda">
			<?php print $fields['city']->content; ?>
			<?php print $fields['postal_code']->content; ?>
			<?php print (isset($fields['street']) ? ' - '.$fields['street']->content : ''); ?>
			<?php print (isset($fields['field_fl_coord_telecom_fi_strs_value']) ? ' - '.t('Tél').' : '.$fields['field_fl_coord_telecom_fi_strs_value']->content : ''); ?>
		</div>
		<div class="item-body">
			<?php print strip_tags($fields['body']->content, '<p><strong>'); ?>
		</div>
	</div>
</div>