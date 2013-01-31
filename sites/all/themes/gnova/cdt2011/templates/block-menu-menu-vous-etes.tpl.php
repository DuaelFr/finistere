<div id="box_profil" class="bloc_1_2 <?php print $block_classes . ' ' . $block_zebra; ?>">

    <?php if (!empty($block->subject)): ?>
      <h1><?php print $block->subject; ?></h1>
    <?php endif; ?>

    <div class="content">
      <?php print $block->content; ?>
    </div>

    <?php print $edit_links; ?>

</div> <!-- /block -->