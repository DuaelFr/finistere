<?php if($ubox_resume || $ubox_slideshow || $ubox_ruban || $ubox_ruban_slideshow): /* Display ubox_resume */?>
	
	<div class="ubox_item_content">
	  <h3><a href="<?php print $node_url ?>"><?php print $title; ?></a></h3>
	  <?php echo $content; ?>
	  <a href="<?php print $node_url ?>"><?php print t('More') ?></a>
	</div>
	<?php print $picture ?>
	
<?php elseif($page): /* Display PAGE */?>

	<div class="box_categories node <?php print $classes; ?>" id="node-<?php print $node->nid; ?>">
	
	  <h1 class="title"><?php print $title; ?></h1>
		<?php if($add_carnet_link): ?>
			<?php print $add_carnet_link; ?>
		<?php endif; ?>
	
	  <?php if($field_hqitem_pageimg) : ?>
	  	<div class="ubox img_all clearfix">
	  		<div class="ubox_items">
	  			<div class="ubox_item">
	  				<?php print $field_hqitem_pageimg; ?>
	  			</div>
	  		</div>
	  	</div>
	  <?php endif; ?>
	  
	  <?php if($content_right): ?>
		<div class="content_right" >
			<?php print $content_right; ?>
		</div>
	  <?php endif; ?>
	  
	  <div class="content_box_categories <?php if($content_right): ?>col_2<?php else: ?>col_1<?php endif; ?>">
	
	    <div class="content">
	      <?php print $content; ?>
	    </div>
		
	    <?php if ($links): ?> 
	      <div class="links"> <?php print $links; ?></div>
	    <?php endif; ?>
	
	  </div> 
	  
	  
	  
	  
	</div> 
	
	<?php if($page && $href_content): ?>
		<?php print $href_content; ?>
	<?php endif; ?>


<?php else: /* Display TEASER */ ?>
	
	<div class="<?php print $classes; ?>" id="node-<?php print $node->nid; ?>">
		<?php if($field_hqitem_teaserimg): ?>
			<div class="hq-teaser-img clearfix">
				<?php print $field_hqitem_teaserimg[0]['view']; ?>
				
			</div>
		<?php endif; ?>
		<div class="ubox_item_content">
			<h2><a href="<?php print $node_url; ?>"><?php print $title; ?></a></h2>
			<div class="teaser-mini-teaser">
				<div class="content">
			      <?php print $node->content['body']['#value']; ?>
			    </div>
			</div>
		</div>
		<div style="clear:left;"></div>
	</div>

<?php endif;  ?>
