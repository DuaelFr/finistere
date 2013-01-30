<?php
//dsm($fields);
?>
<div class="box_agenda clearfix">
	
	<?php print $fields['field_fl_photos_imgs_fid']->content; ?>
	
	<div class="content_box_agenda">
		
		<h3><?php print $fields['title']->content; ?></h3>
		<div class="date_agenda">Du <?php print $fields['field_fl_date_debut_date_value']->content; ?> au <?php print $fields['field_fl_date_fin_date_value']->content; ?> | <?php print $fields['city']->content; ?></div>
		
		<?php print $fields['body']->content; ?>
		
	</div>
	
</div>