<div class="<?php print $classes; ?>" id="node-<?php print $node->nid; ?>">
	<div class="ubox_item_content">
		
			<h3><a href="<?php print $node_url;?>"><?php print $title; ?></a></h3>
			<div class="teaser-mini-teaser">
				<?php print (strlen($node->content['body']['#value'])>70 ? truncate_utf8(strip_tags($node->content['body']['#value']), 65, TRUE, TRUE) : strip_tags($node->content['body']['#value'])); ?>
			</div>
			<?php if ($links): ?> 
		      <div class="links"> <?php print $links; ?></div>
		    <?php endif; ?>
	</div>
	<?php if($field_hqitem_teaserimg): ?>
		<?php print $field_hqitem_teaserimg[0]['view']; ?>
	<?php endif; ?>
</div>