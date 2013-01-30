<?php /* Informations site */ ?>
<div id="info_site" class="<?php print $block_classes . ' ' . $block_zebra; ?>">
  <div class="block-inner">

    <?php if (!empty($block->subject)): ?>
      <h2 class="title block-title"><?php print $block->subject; ?></h2>
    <?php endif; ?>

    <div class="content">
      <?php print $block->content; ?>
    </div>

    <?php print $edit_links; ?>

  </div> <!-- /block-inner -->
</div> <!-- /block -->