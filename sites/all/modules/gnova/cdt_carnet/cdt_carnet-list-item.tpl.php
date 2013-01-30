<div class="box_agenda">
	
	<?php 
		if($node->field_fl_photos_imgs[0]['filepath'] && strlen($node->field_fl_photos_imgs[0]['filepath'])>0){
			print l(theme('imagecache', 'pro_la_une', $node->field_fl_photos_imgs[0]['filepath']), 'node/'.$node->nid, array('html'=>TRUE));
		}
	?>
	<div class="content_box_agenda">
		<h3><?php print l($node->title, 'node/'.$node->nid); ?></h3>
		<?php if($node->locations[0]['city'] && strlen($node->locations[0]['city'])>0): ?>
			<div class="date_agenda">
				<?php print $node->locations[0]['city'].($node->locations[0]['postal_code'] ? ' - '.$node->locations[0]['postal_code'] : '').($node->locations[0]['street'] ? ' - '.$node->locations[0]['street'] : '').($node->field_fixfl_maintelephone[0]['value'] ? ' - Tel : '.$node->field_fixfl_maintelephone[0]['value'] : ''); ?>
			</div>
		<?php endif; ?>
		
		<div>
			<?php 
				$body = trim(strip_tags($node->body)); 
				print (strlen($body)>200 ? '<p>'.substr($body, 0, 200).' ...</p>' : '<p>'.$body.'</p>');
			?>
		</div>
		<div class="wrap_btn clearfix">
			<a href="<?php print base_path(); ?>simple-share/mail/<?php print $node->nid; ?>">
				<img src="<?php print base_path(); ?><?php print drupal_get_path('theme', 'cdt2011'); ?>/images/mail.png">
			</a>
			<?php if($node->type=='flux_b2917'): ?>
			
				<?php if($node->field_fixfl_typeresa[0]['value']): ?>
					<?php if(trim(strtolower($node->field_fixfl_typeresa[0]['value']))=='avec résa en ligne' && $node->field_fixfl_urlresa[0]['value']):?>
						<?php print l(t('BOOK ONLINE'), $node->field_fixfl_urlresa[0]['value']); ?>
					<?php elseif(trim(strtolower($node->field_fixfl_typeresa[0]['value']))=='sans résa en ligne' && $node->field_fl_coord_telecom_ma_strs[0]['value']): ?>
						<a href="mailto:<?php print $node->field_fl_coord_telecom_ma_strs[0]['value']; ?>"><?php print t('BOOK ONLINE'); ?></a>
					<?php elseif($node->field_fixfl_typeresa[0]['value'] && $node->field_fixfl_urlresa[0]['value']): ?>
						<?php print l(t('BOOK ONLINE'), $node->field_fixfl_urlresa[0]['value']); ?>
					<?php endif; ?>
				<?php endif; ?>
				
			<?php else: ?>
			
				
			
			<?php endif;?>
		</div>
		
	</div>
	<br class="clear">
</div>