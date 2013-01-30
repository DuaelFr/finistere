

<div class="box_resa_details red">

	<?php print $fields['field_fl_photo_vignette_imgs_fid']->content; ?>
	
	<div class="prix ">
		<span><?php print t('from'); ?></span>
		<span class="left_b"></span>
		<span class="middle_b"><?php print $fields['field_fl_prix_prix_value']->content; ?></span>
		<span class="right_b"></span>
	</div>
	
	<?php //print '<h3>'.t('Description').'</h3>'; ?>
	<strong><?php print $fields['field_fl_descriptif_chapo_txa_value']->content; ?></strong>
	<p><?php print $fields['body']->content; ?></p>
	<?php print l(t('Learn more'), 'node/'.$fields['nid']->content, array('attributes'=>array('class'=>'lien'))); ?>
	
</div>