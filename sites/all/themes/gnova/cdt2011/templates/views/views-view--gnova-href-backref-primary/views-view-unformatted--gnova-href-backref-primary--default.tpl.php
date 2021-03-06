<?php
// $Id: views-view-unformatted.tpl.php,v 1.6 2008/10/01 20:52:11 merlinofchaos Exp $
/**
 * @file views-view-unformatted.tpl.php
 * Default simple view template to display a list of rows.
 *
 * @ingroup views_templates
 */
 
 $iend=0;
 $i=0;
 $step = 4;
 $fin = count($rows);
?>
<?php if (!empty($title)): ?>
  <h3><?php print $title; ?></h3>
<?php endif; ?>
<?php foreach ($rows as $id => $row): ?>
  
  <?php if($i%$step==0): ?>
  	<?php $iend=$i+$step; ?>
  	<div class="col col-<?php print $i; ?>">
  <?php endif; ?>
  
  <div class="<?php print $classes[$id]; ?>">
    <?php print $row; ?>
  </div>
  
  <?php if($iend==$i+1 || $i+1==$fin): ?>
  	</div>
  <?php endif; ?>

  <?php $i++; ?>

<?php endforeach; ?>
