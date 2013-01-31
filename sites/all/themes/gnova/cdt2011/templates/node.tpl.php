<?php if($ubox_resume): ?>
	
<div class="ubox_item_content">
  <h3><a href="<?php print $node_url ?>"><?php print $title; ?></a></h3>
  <?php echo $content; ?>
  <a href="<?php print $node_url ?>"><?php print t('More') ?></a>
</div>
<?php print $picture ?>
	
<?php else: ?>
<div class="box_categories node <?php print $classes; ?>" id="node-<?php print $node->nid; ?>">

	<h1 class="title"><?php print $title; ?><!--<a href="javascript:void(0);"><?php print t('Noter dans son carnet de voyage') ?></a>--></h1>
	
  <div class="<?php if($content_right): ?>col_2<?php else: ?>col_1<?php endif; ?>">

    <?php if ($submitted): ?>
      <span class="submitted"><?php print $submitted; ?></span>
    <?php endif; ?>

    <div class="content">
      <?php print $content; ?>
    </div>

    <?php if ($terms): ?>
      <div class="taxonomy"><?php print $terms; ?></div>
    <?php endif;?>

    <?php if ($links): ?> 
      <div class="links"> <?php print $links; ?></div>
    <?php endif; ?>

  </div> <!-- /col -->
  
  <?php if($content_right): ?>
  	<div class="content_right" ?>
  		<?php print $content_right; ?>
  	</div>
  <?php endif; ?>
  
</div> <!-- /node-->
<?php endif; /* /ubox_simple */ ?>