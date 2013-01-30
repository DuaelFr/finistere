<?php if($ubox_resume): ?>
	
<div class="ubox_item_content">
  <h3><a href="<?php print $node_url ?>"><?php print $title; ?></a></h3>
  <?php echo $content; ?>
  <a href="<?php print $node_url ?>"><?php print t('More') ?></a>
</div>
<?php print $picture ?>
	
<?php else: ?>
<?php if($ubox_ruban_slideshow): ?>
<?php
if($node->field_bp_images[0]['view']){
 print $node->field_bp_images[0]['view'];
}
if($node->field_bp_prix[0]['view']){
	print '<div class="prix">'.$node->field_bp_prix[0]['view'];
	if($node->field_bp_ancienprix[0]['view']){
		print '<span>'.t('instead of').' <del>'.$node->field_bp_ancienprix[0]['view'].'</del></span>';
	}
	print '</div>';
}
?>

<h3><a href="<?php print $node_url ?>"><?php print $title; ?></a></h3>
<a href="<?php print $node_url ?>"><?php print t('More') ?></a>
	    
<?php else: ?>
<div class="box_categories node <?php print $classes; ?> uboxbp all clearfix" id="node-<?php print $node->nid; ?>">
	<?php if($teaser): ?>
	
		<h2><a href="<?php print $node_url; ?>"><?php print $title; ?></a></h2>
	
	<?php else : ?>
	
		<h1 class="title"><?php print $title; ?></h1>
		<?php if($add_carnet_link): ?>
			<?php print $add_carnet_link; ?>
		<?php endif; ?>
	
	<?php endif; ?>
  <div class="uboxpb_items">
	<div class="uboxpb_items_left">
		<?php if ($terms): ?>
	      <div class="ruban"><?php print $terms; ?></div>
	    <?php endif;?>
    	<?php print $img; ?>
		<?php print $img_thumbdails; ?>
	    <?php if($prix) : ?>
	    	<div class="c_prix">
	    		<span class="border left_b"></span>
		    	<?php print $prix; ?>
		    	<span class="border right_b"></span>
	    	</div>
	    <?php endif; ?>
	</div>
	<div class="uboxpb_items_left">
		<div class="uboxbp_content">
			<div class="uboxpb_items_content">
				<?php print $node->content['body']['#value']; ?>
			</div>
			<?php if($nboffers): ?>
				<div class="rest_offer">
					<?php print $nboffers; ?>
				</div>
			<?php endif;?>
			<?php if($reservez): ?>
				<?php print $reservez; ?>
			<?php endif; ?>
      <?php if(!$reservez && !empty($node->field_bp_email[0]['value'])): ?>
        <?php print l(t('Contact us to know free dates'), drupal_lookup_path('alias', 'node/5942'), array('attributes'=>array('id'=>'bouton'), 'query'=>array('bonplan'=>$node->nid))) ?>
      <?php endif; ?>
		</div>
	</div>
    <?php if ($submitted): ?>
      <span class="submitted"><?php print $submitted; ?></span>
    <?php endif; ?>

  </div> <!-- /uboxpb_items -->
  
  <?php print $sharethis; ?>
  
  <?php if ($links): ?> 
      <div class="links"> <?php print $links; ?></div>
    <?php endif; ?>
  
</div> <!-- /node-->
<?php endif; /* /ubox_simple */ ?>
<?php endif; ?>