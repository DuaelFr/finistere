<div class="box_agenda clearfix">
  
  <a href="<?php print $node_url ?>">
	  <?php 
	  	print theme('imagecache', 'pro_la_une', $node->field_hqitem_teaserimg[0]['filepath']); ?>
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