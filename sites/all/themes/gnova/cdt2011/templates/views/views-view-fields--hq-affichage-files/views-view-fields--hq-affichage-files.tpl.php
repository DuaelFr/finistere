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

<div class="box_agenda clearfix file-item">
	<?php print $fields['field_hqitem_teaserimg_fid']->content; ?>
	<div class="content_box_agenda">
		<div class="date_agenda"><?php print $fields['created']->content; ?></div>
		<h3><?php print $fields['title']->content; ?></h3>
		<div class="item-body">
			<?php print strip_tags($fields['body']->content, '<p><strong>'); ?>
		</div>
		<a class="download" href="<?php print $fields['field_hq_file_fid']->content; ?>">
			<?php print t('Télécharger le fichier'); ?>
			<img alt="mini_pdf" src="<?php print base_path().drupal_get_path('theme', 'cdt2011').'/images/pdf_mini.jpg'; ?>">
		</a>
	</div>
</div>