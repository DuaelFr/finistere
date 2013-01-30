<?php
// $Id: textsize-image.tpl.php,v 1.1.2.6 2009/11/17 19:58:44 christianzwahlen Exp $

/**
 * @file
 * Image theme implementation for rendering a block.
 *
 * Available variables:
 * - $dest: The drupal function drupal_get_destination().
 * - $block_title: Block title: "Text Size" or "Zoom".
 * - $list_inline: Display the ul list "inline" or not.
 * - $current_inline: Display the current text size "inline" or not.
 * - $subtitle: The subtitle.
 * - $subtitle_text: "Text Size"/"Zoom" or inline "Text Size: "/"Zoom: ".
 * - $textsize_normal: The text size normal link.
 * - $display_links: Show or hide ("display_hidden") the text in the links.
 * - $current_textsize: The current text size.
 * - $display_current_textsize: Show or hide ("display_hidden") the text of the current textsize.
 * - $display_current_textsize_text: Show or hide ("display_hidden").
 * - $link_type: Return "variable" for variable or fix.
 * - $increment: The increment step (default 5%).
 * - $normal: The textsize normal (default 75%).
 * - $current_textsize_text: The current textsize text "Current Size" or "Current Zoom".
 * - $textsize: The current text size (default 100%).
 *
 * @see template_preprocess_textsize_text()
 */
?>
<?php  if ($subtitle): ?>
<h3 class="<?php print $list_inline; ?>"><?php print $subtitle_text; ?></h3>
<?php endif; ?>
<ul class="textsize_<?php print $list_inline .' '. $current_inline;  ?>">
  <li><?php print l('A', 'textsize/decrease', array('attributes' => array('title' => $block_title .': '. t('Decrease') .' -'. $increment .'%', 'class' => 'ts_decrease_'. $link_type .' text_display_hidden ts_rollover small textsize_decrease_fix', 'id'=>'small'), 'query' => $dest, 'html' => TRUE)); ?>
<?php  if ($textsize_normal): ?>
  <?php print l('A', 'textsize/normal', array('attributes' => array('title' => $block_title .': '. t('Normal') .' ='. $normal .'%', 'class' => 'ts_normal_'. $link_type .' text_display_hidden ts_rollover medium textsize_normal_fix', 'id'=>'medium'), 'query' => $dest, 'html' => TRUE)); ?>
<?php endif; ?>
  <?php print l('A', 'textsize/increase', array('attributes' => array('title' => $block_title .': '. t('Increase') .' +'. $increment .'%', 'class' => 'ts_increase_'. $link_type .' text_display_hidden ts_rollover big textsize_increase_fix', 'id'=>'large'), 'query' => $dest, 'html' => TRUE)); ?></li>
</ul>
<?php  if ($current_textsize): ?>
<p class="textsize_current <?php print $current_inline .' '. $display_current_textsize .' current_text_'. $display_current_textsize_text; ?>"><span class="<?php print $display_current_textsize_text; ?>"><?php print $current_textsize_text; ?>: </span><span id="textsize_current" title="<?php print $current_textsize_text .': '. $textsize .'%'; ?>"><?php print $textsize; ?>%</span></p>
<?php endif; ?>
<div class="ts_clear"></div>