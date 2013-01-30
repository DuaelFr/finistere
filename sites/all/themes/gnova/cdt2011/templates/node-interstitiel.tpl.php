<div class="box_categories node <?php print $classes; ?>" id="node-<?php print $node->nid; ?>">

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