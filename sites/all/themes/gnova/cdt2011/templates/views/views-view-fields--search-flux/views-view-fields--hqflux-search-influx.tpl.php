<div class="box_agenda clearfix file-item">
  <?php print $fields['field_fl_photos_imgs_fid']->content; ?>
  <div class="content_box_agenda">

    <h3>
      <?php
      print $fields['title']->content;
      if (isset($fields['field_fl_categorie_strs_value'])) {
        print cdt2011_term_to_img($fields['field_fl_categorie_strs_value']->content, ' - ');
      }
      if (isset($fields['field_fl_classement_label_strs_value'])) {
        print cdt2011_term_to_img($fields['field_fl_classement_label_strs_value']->content, ' - ');
      }
      print cdt2011_new_norm($fields);
      if (isset($fields['field_fl_chaines_strs_value']) && $fields['field_fl_chaines_strs_value']->content != '') {
        print ' - ' . $fields['field_fl_chaines_strs_value']->content;
      }
      ?>
    </h3>

    <div class="date_agenda">
      <?php print $fields['city']->content; ?>
      <?php //print $fields['postal_code']->content; ?>
      <?php //print (isset($fields['street']) ? ' - '.$fields['street']->content : ''); ?>
      <?php print (isset($fields['field_fixfl_maintelephone_value']) ? ' - ' . t('Tél') . ' : ' . $fields['field_fixfl_maintelephone_value']->content : ''); ?>
      <?php print (isset($fields['field_fl_coord_telecom_fi_strs_value']) ? ' - ' . t('Tél') . ' : ' . $fields['field_fl_coord_telecom_fi_strs_value']->content : ''); ?>
    </div>

    <div class="item-body">
      <?php print strip_tags($fields['body']->content, '<p><strong>'); ?>
    </div>

    <?php
    // Bouton Réserver
    print cdt2011_booking_button($fields);
    ?>
  </div>
</div>