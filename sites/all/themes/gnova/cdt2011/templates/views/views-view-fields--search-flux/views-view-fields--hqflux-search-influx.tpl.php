
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
      if (isset($fields['field_fl_chaines_strs_value']) && $fields['field_fl_chaines_strs_value']->content!='') {
        print ' - '.$fields['field_fl_chaines_strs_value']->content;
      }
      ?>
    </h3>
		<div class="date_agenda">
			<?php print $fields['city']->content; ?>
			<?php //print $fields['postal_code']->content; ?>
			<?php //print (isset($fields['street']) ? ' - '.$fields['street']->content : ''); ?>
      <?php print (isset($fields['field_fixfl_maintelephone_value']) ? ' - '.t('Tél').' : '.$fields['field_fixfl_maintelephone_value']->content : ''); ?>
      <?php print (isset($fields['field_fl_coord_telecom_fi_strs_value']) ? ' - '.t('Tél').' : '.$fields['field_fl_coord_telecom_fi_strs_value']->content : ''); ?>
		</div>
		<div class="item-body">
			<?php print strip_tags($fields['body']->content, '<p><strong>'); ?>
		</div>
		<?php
		//Le bouton Réserver s'affiche que pour les hotels (152,2621), campings (410), chambres d'hôte (2402) et meublés (2629)
		$taxo = explode(',',$fields['tid_1']->content);
		$type = '';
		// Hotel
		if(in_array(152,$taxo) || in_array(2621,$taxo)) $type='z3132e9_fr';
		// Hotel EN
		if(in_array(2622,$taxo)) $type='z3132e9_uk';
		// Camping
		if(in_array(410,$taxo)) $type='z3130e9_fr';
		// Camping EN
		if(in_array(2704,$taxo)) $type='z3130e9_uk';
		// Chambres meublés
		if(in_array(2629,$taxo)) $type='z2852e3_fr';
		// Chambres meublés EN
		if(in_array(2701,$taxo)) $type='z2852e3_uk';
		// Chambres d'hôte
		if(in_array(2402,$taxo)) $type='z3131e9_fr';
		// Chambres d'hôte
		if(in_array(2623,$taxo)) $type='z3131e9_uk';
		if($type!=''):
		?>
		<?php if(($fields['field_fixfl_onlineresa_value']->content=='oui' || $fields['field_fixfl_onlineresa_value']->content=='yes') &&
		        isset($fields['field_fixfl_codemetier_value']) && 
		      isset($fields['field_fixfl_codefournisseur_value']) ): 
		?>
		<div class="wrap_btn clearfix">
		  <a class="rsv_btn" title="Réserver en ligne" href="http://<?php print variable_get('flux_booking_domain_url', 'resa.finisteretourisme.com') ?>/<?php print $type; ?>-.aspx?Param/CodeOs=<?php print $fields['field_fixfl_codemetier_value']->content; ?>-<?php print ((isset($fields['field_fixfl_codeproduit_value']) && strlen($fields['field_fixfl_codeproduit_value']->content)>0) ? $fields['field_fixfl_codefournisseur_value']->content.'-'.$fields['field_fixfl_codeproduit_value']->content : $fields['field_fixfl_codefournisseur_value']->content); ?>"><?php print t('Book') ?></a>
		</div>
		<?php endif; ?>
		<?php endif; ?>
	</div>
</div>