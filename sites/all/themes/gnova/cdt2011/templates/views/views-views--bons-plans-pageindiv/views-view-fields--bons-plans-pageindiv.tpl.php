<?php
// $Id: views-view-fields.tpl.php,v 1.6 2008/09/24 22:48:21 merlinofchaos Exp $
/**
* @file views-view-fields.tpl.php
* Default simple view template to all the fields as a row.
*
* - $view: The view in use.
* - $fields: an array of $field objects. Each one contains:
* - $field->content: The output of the field.
* - $field->raw: The raw data for the field, if it exists. This is NOT output safe.
* - $field->class: The safe class id to use.
* - $field->handler: The Views field handler object controlling this field. Do not use
* var_export to dump this object, as it can't handle the recursion.
* - $field->inline: Whether or not the field should be inline.
* - $field->inline_html: either div or span based on the above flag.
* - $field->separator: an optional separator that may appear before a field.
* - $row: The raw result object from the query, with all data it fetched.
*
* @ingroup views_templates
*/

?>
<h2><?php print $fields['title']->content; ?></h2>
<div class="uboxpb_items">

<?php if($fields['tid']): ?>
<div class="ruban">
<h3><?php print $fields['tid']->content; ?></h3>
</div>
<?php endif; ?>

<div class="lien_img">
<?php print $fields['field_hqitem_teaserimg_fid']->content; ?>
</div>
<?php if($fields['field_bp_prix_value']): ?>
<div class="c_prix">
<span class="border left_b"></span>
<div class="prix">
<?php print $fields['field_bp_prix_value']->content; ?>
<?php if($fields['field_bp_ancienprix_value']) : ?>
<span>
<?php print t('instead of'); ?>&nbsp;
<del><?php print $fields['field_bp_ancienprix_value']->content; ?></del>
</span>
<?php endif; ?>
<div class="fond_gris"></div>
</div>
<span class="border right_b"></span>
</div>
<?php endif; ?>
</div>