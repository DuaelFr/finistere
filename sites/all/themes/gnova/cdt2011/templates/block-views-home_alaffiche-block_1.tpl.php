<div id="block-<?php print $block->module .'-'. $block->delta ?>" class="<?php //print $block_classes_cdt . ' ' . $block_zebra.' '.$block_classes; 
?>">

  <?php if (!empty($block->subject)): ?>
    <h2 class="h2_spec"><?php print $block->subject; ?> <span><a href="<?php print base_path(); ?>agenda">Tout l'agenda</a></span></h2> 
  <?php endif; ?>
  <?php print $block->content; ?>

</div> <!-- /block -->