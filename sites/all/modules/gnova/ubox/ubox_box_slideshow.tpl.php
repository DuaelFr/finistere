<?php $current_url = check_plain(request_uri()); ?>
<div id="ubox_box_<?php print $ubox->nid; ?>" class="ubox ubox_box_slideshow <?php print $ubox->field_ubox_proportionsdisplay_class; ?> ubox_items_<?php print $ubox->field_ubox_itemsnb_value ?> clearfix">
	<?php if(!empty($ubox->field_ubox_header_label_value) || !empty($ubox->field_ubox_displayedtitle_value)): ?><h2><?php if(!empty($ubox->field_ubox_header_url_value)): ?><a href="<?php print $ubox->field_ubox_header_url_value; ?>"><?php endif; ?><?php print $ubox->field_ubox_displayedtitle_value; ?><?php if(!empty($ubox->field_ubox_header_label_value)): ?><span><?php print $ubox->field_ubox_header_label_value; ?></span><?php endif; ?><?php if(!empty($ubox->field_ubox_header_url_value)): ?></a><?php endif; ?></h2><?php endif; ?>
<?php if(isset($ubox->items) && !empty($ubox->items)): ?>
<?php if(user_access('edit any ubox content')): ?><div class="edit"><a class="block-config" title="<?php print t('edit this ubox') ?>" href="<?php print $base_path . "/node/" . $ubox->nid . "/edit?destination=" ?><?php if(empty($current_url)): print "<front>"; else: print $current_url; endif; ?>"><span><?php print t('edit'); ?></span></a></div><?php endif; ?>
<?php $i=0; ?>
	<a class="prev browse left">&lt;</a>
	<div class="scrollable">
		<div class="ubox">
			<?php $nbItems = sizeof($ubox->items); ?>
			<?php foreach($ubox->items as $cle=>$item): ?>
				<?php if($i== 0 || $i%$ubox->field_ubox_itemsnb_value == 0): ?>
			<div class="ubox_items">
				<?php endif; ?>
				<div class="ubox_item">
				<?php print $item; ?>
				</div>
				<?php if((($i+1)%$ubox->field_ubox_itemsnb_value == 0) || $nbItems == $i+1): ?>
			</div><!-- END ubox_items -->
				<?php endif; ?>
				<?php $i++; ?>
			<?php endforeach; ?>
		</div>
	</div>
	<a class="next browse right">&gt;</a>
	<?php if(!empty($ubox->field_ubox_footer_label_value)): ?>
		<?php if(!empty($ubox->field_ubox_footer_url_value)): ?>
	<a class="ubox_footer_label" href="<?php print $ubox->field_ubox_footer_url_value; ?>">
		<?php else: ?>
	<span class="ubox_footer_label">
		<?php endif; ?>
	<?php print $ubox->field_ubox_footer_label_value; ?>
		<?php if(!empty($ubox->field_ubox_footer_url_value)): ?>
	</a>
		<?php else: ?>
	</span>
		<?php endif; ?>
	<?php endif; ?>
<?php else: ?>
	<div class="ubox_items">
		<div class="ubox_item_content"><?php print $ubox->body; ?></div>
	</div>
<?php endif; ?>
</div>