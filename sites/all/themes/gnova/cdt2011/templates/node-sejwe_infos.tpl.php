<?php //dsm($node); ?>
<?php if($ubox_resume): ?>
<div class="ubox_item_content">
  <h3><a href="<?php print $node_url ?>"><?php print $title; ?></a></h3>
  <?php echo $content; ?>
  <a href="<?php print $node_url ?>"><?php print t('More') ?></a>
</div>
<?php print $picture ?>
	
<?php else: ?>
<?php if($list_theme_sejwe) print '<h2 class="see_WE">'.t('Toutes les thématiques week-end').'</h2><div class="wrap_content_we">'.$list_theme_sejwe.'</div>'; ?>
<div class="wrap_resa box_categories node <?php print $classes; ?> noborder clearfix" id="node-<?php print $node->nid; ?>">


    <div class="ubox_items <?php print ($node->field_sejwe_cssclass[0]['value'] ? $node->field_sejwe_cssclass[0]['value'] : ''); ?>">
      <div class="ubox_item">
      <div class="ubox_item_content">
      	<h2 class="title"><?php print $title; ?></h2>
      </div>
      <?php print $field_sejweinf_img_page_rendered; ?>
      </div>
    </div>
	<div style="clear:left;"></div>
  
  <div id="offer-list" class="clearfix">
  	<?php print $reservez_sejwe_by_theme; ?>
  </div>
  
</div> <!-- /node-->
<?php endif; /* /ubox_simple */ ?>