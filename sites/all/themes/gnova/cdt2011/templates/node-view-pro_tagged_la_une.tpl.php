<div class="box_agenda">
  <?php if($cnt_date_loc): ?>
  
  	<div class="date_agenda"><?php print $cnt_date_loc; ?></div>
  
  <?php endif; ?>

  <h2><a href="<?php print $node_url ?>"><?php print $title; ?></a></h2>
  <?php echo $node->content['body']['#value']; ?>
  <a href="<?php print $node_url ?>"><?php print t('More') ?></a>
</div>
