<div class="box_agenda clearfix short">
  
  <a href="<?php print $node_url ?>">
	  <?php 
	  	$imgpath = (isset($node->field_cnt_list_img[0]['filepath']) ? $node->field_cnt_list_img[0]['filepath'] : $node->field_bp_images[0]['filepath']);
	  	print theme('imagecache', 'agenda_home_list', $imgpath); ?>
  </a>
  
  <div class="content_box_agenda">
  
	  <?php if($cnt_date_loc): ?>
	  	<div class="date_agenda"><?php print $cnt_date_loc; ?></div>
	  <?php endif; ?>
	  
	  <h3><a href="<?php print $node_url ?>"><?php print $title; ?></a></h3>
	  <div>
		  <?php echo (strlen($node->content['body']['#value'])>80 ? substr($node->content['body']['#value'], 0, 75).' ...' : $node->content['body']['#value']); ?>
		  <a href="<?php print $node_url ?>"><?php print t('More') ?></a>
	  </div>
  </div>
</div>