<?php
// $Id: views-view-fields.tpl.php,v 1.6 2008/09/24 22:48:21 merlinofchaos Exp $
/**
 * @file views-view-fields.tpl.php
 * Default simple view template to all the fields as a row.
 *
 * - $view: The view in use.
 * - $fields: an array of $field objects. Each one contains:
 *   - $field->content: The output of the field.
 *   - $field->raw: The raw data for the field, if it exists. This is NOT output safe.
 *   - $field->class: The safe class id to use.
 *   - $field->handler: The Views field handler object controlling this field. Do not use
 *     var_export to dump this object, as it can't handle the recursion.
 *   - $field->inline: Whether or not the field should be inline.
 *   - $field->inline_html: either div or span based on the above flag.
 *   - $field->separator: an optional separator that may appear before a field.
 * - $row: The raw result object from the query, with all data it fetched.
 *
 * @ingroup views_templates
 */
 
?>

<div class="box_resa <?php print $fields['field_sejwe_cssclass_value']->raw; ?>">
	
	<?php print $fields['field_sejweinf_img_mini_fid']->content; ?>
	<?php 
		$parts = split('#', $fields['tid']->content);
	?>
<?php if(count($parts)>1 && substr_count($parts[1],'Week-end')==1): ?>
  <?php if(count($parts)>1): ?>
	<h2><?php print $parts[1]; //l($parts[0], 'reservez/weekend-sejour/'.$fields['field_sejwe_typetid_value']->raw.'/'.$fields['field_sejwe_themetid_value']->raw); ?></h2>
	<?php endif; ?>
	<?php if(count($parts)>0): ?>
	<h3><?php print $parts[0];//l($parts[1], 'reservez/weekend-sejour/'.$fields['field_sejwe_typetid_value']->raw.'/'.$fields['field_sejwe_themetid_value']->raw); ?></h3>
	<?php endif; ?>
<?php else: ?>
	<?php if(count($parts)>0): ?>
	<h2><?php print $parts[0]; //l($parts[0], 'reservez/weekend-sejour/'.$fields['field_sejwe_typetid_value']->raw.'/'.$fields['field_sejwe_themetid_value']->raw); ?></h2>
	<?php endif; ?>
	<?php if(count($parts)>1): ?>
	<h3><?php print $parts[1];//l($parts[1], 'reservez/weekend-sejour/'.$fields['field_sejwe_typetid_value']->raw.'/'.$fields['field_sejwe_themetid_value']->raw); ?></h3>
	<?php endif; ?>
<?php endif; ?>	
</div>