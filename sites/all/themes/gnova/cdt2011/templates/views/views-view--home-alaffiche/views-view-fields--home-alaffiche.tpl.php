<div class="ubox_item_content">
<?php foreach ($fields as $id => $field): ?>
  <?php if (!empty($field->separator)): ?>
    <?php print $field->separator; ?>
  <?php endif; ?>

    <?php if ($field->label): ?>
      <label class="views-label-<?php print $field->class; ?>">
        <?php print $field->label; ?>:
      </label>
    <?php endif; ?>
      <?php
      // $field->element_type is either SPAN or DIV depending upon whether or not
      // the field is a 'block' element type or 'inline' element type.
      ?>
      <?php 
      $photo='';
      switch($field->class): 
        case 'title':
          print '<h3>'.$field->content.'</h3>';
          break;
        case 'field-fl-date-fin-date-value':
          print '<div class="ubox_date">'.$field->content.'</div>';
          break;
        case 'body':
          print '<div>'.$field->content.'</div>';
          break;
        case 'field-fl-photos-imgs-fid':
          $photo=$field->content;
          break;
        default:
          print $field->content;
      endswitch;
      ?>
<?php endforeach; ?>
</div>
<?php print $photo; ?>