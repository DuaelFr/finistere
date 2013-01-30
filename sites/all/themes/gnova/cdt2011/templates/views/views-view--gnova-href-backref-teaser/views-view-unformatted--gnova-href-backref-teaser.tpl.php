<?php
// $Id: views-view-unformatted.tpl.php,v 1.6 2008/10/01 20:52:11 merlinofchaos Exp $
/**
 * @file views-view-unformatted.tpl.php
 * Default simple view template to display a list of rows.
 *
 * @ingroup views_templates
 */
 $nbValues = 3;
 $nbItems = sizeof($rows);
?>
<?php if (!empty($title)): ?>
  <h3><?php print $title; ?></h3>
<?php endif; ?>
<?php $i=0; ?>
<?php foreach ($rows as $id => $row):?>
		<?php if($i == 0 || $i%$nbValues == 0): ?>
	<div class="ubox_items">
		<?php endif; ?>
		<div class="ubox_item">
			<?php print $row; ?>
		</div>
		<?php if(($i+1)%$nbValues == 0 || $nbItems == $i+1 ): ?>
	</div>
  <?php endif; ?>
  <?php $i++; ?>
<?php endforeach; ?>

