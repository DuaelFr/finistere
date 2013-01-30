<?php //dsm($node); ?>
<?php if($ubox_resume): ?>
	
	<div class="ubox_item_content">
		<h3><a href="<?php print $node_url ?>"><?php print $title; ?></a></h3>
		<?php echo $content; ?>
		<a href="<?php print $node_url ?>"><?php print t('More') ?></a>
	</div>
	<?php print $picture ?>
	
<?php else: ?>
	
	<div class="wrap_resa uboxbp node <?php print $classes; ?> all clearfix" id="node-<?php print $node->nid; ?>">
		
		<div class="title_we"><?php print $field_fl_type_tx[0]['view']; ?><?php print ($field_fl_type_tx_rendered && $field_fl_theme_tx_rendered ? ' ' : ''); ?><?php ($field_fl_theme_tx[0]['value'])?print ' "'.$field_fl_theme_tx[0]['value'].'"':''; ?></div>
		
		<?php if($teaser): ?>
			<h2 class="title"><a href="<?php print $node_link; ?>"><?php print $title; ?></a></h2>
		<?php else: ?>
			<h1 class="title"><?php print $title; ?></h1>
			<?php if($add_carnet_link): ?>
				<?php print $add_carnet_link; ?>
			<?php endif; ?>
		<?php endif; ?>
		
	  
	  	
	  	<div class="uboxpb_items">
	  		
			<div class="uboxpb_items_left">
				
				<?php print $field_fl_photo_imgs_rendered; ?>
				
				<?php if($field_fl_prix_prix[0]['view']) : ?>
					<div class="prix">
						<span class="border left_b"></span>
						<span class="middle_b"><?php print $field_fl_prix_prix[0]['view']; ?></span>
						<span class="border right_b"></span>
					</div>
				<?php endif; ?>
				
				<div class="uboxbp_content">
					<h4><?php print $title;?></h4>
					<div class="uboxpb_items_content addresszone">
						<?php print $addresszone; ?>
					</div>
					<?php if(count($field_fl_tarif_label)>0 && strlen($field_fl_tarif_label[0]['view'])>0): ?>
						<h4><?php print t('Prices'); ?></h4>
						<table id="table_tarif">
							<tr><td class="no_border"></td><td class="grey"><?php print t('Min');?></td><td class="grey"><?php print t('Max');?></td></tr>
							<?php 
								$i=0;
								foreach($field_fl_tarif_label as $item){
									print '<tr><td class="grey">'.$item['view'].'</td><td class="grey">'.$field_fl_tarif_min[$i]['view'].'</td><td class="grey">'.$field_fl_tarif_max[$i]['view'].'</td></tr>';
									$i++;
								}
							?>
						</table>
					<?php endif; ?>

          <div class="collapsable collapsed">
            <h4 class="info_we collapse_title"><?php print t('Further informations on this ') . $field_fl_type_tx[0]['view']; ?></h4>
            <div class="uboxpb_items_content collapse_box">
              <?php print $zone1; ?>
            </div>
          </div>
				</div>
				
			</div>
			
			<div class="uboxpb_items_left">
				<div class="uboxbp_content">
					
					<?php if($node->field_fixfl_typeresa[0]['value']): ?>
						<?php if(trim(strtolower($node->field_fixfl_typeresa[0]['value']))=='avec résa en ligne' && $node->field_fixfl_urlresa[0]['value']):?>
							<?php print l(t('BOOK ONLINE'), $node->field_fixfl_urlresa[0]['value']); ?>
						<?php elseif(trim(strtolower($node->field_fixfl_typeresa[0]['value']))=='sans résa en ligne' && $node->field_fl_coord_telecom_ma_strs[0]['value']): ?>
							<a href="mailto:<?php print $node->field_fl_coord_telecom_ma_strs[0]['value']; ?>"><?php print t('CONTACT BY EMAIL'); ?></a>
						<?php elseif($node->field_fixfl_typeresa[0]['value'] && $node->field_fixfl_urlresa[0]['value']): ?>
							<?php print l(t('KNOW MORE'), $node->field_fixfl_urlresa[0]['value']); ?>
						<?php endif; ?>
					<?php endif; ?>
				
					<?php if($map): ?>
						<!--<div class="node-map">
							<?php //print $map; 
							?>
						</div>-->
					<?php endif; ?>

					<div class="uboxpb_items_content">
            <?php if($node->field_fl_prix_prix[0]['value']) : ?>
              <div class="prix">
                <span class="left_b"></span>
                <span class="middle_b"><?php print $node->field_fl_prix_prix[0]['value']; ?>&euro;</span>
                <span class="right_b"></span>
                <?php if(isset($node->field_fl_prix_complement_strs[0]['value']) && !empty($node->field_fl_prix_complement_strs[0]['value'])): ?>
                <span><?php print $node->field_fl_prix_complement_strs[0]['value']; ?></span>
                <?php endif; ?>
              </div>
            <?php endif; ?>

            <?php if($field_fl_profil_tx): ?>
              <?php print $field_fl_profil_tx[0]['view'] ?>
            <?php endif; ?>
            
						<?php print $presentationzone; ?>
					</div>

					<div class="uboxpb_items_content">
						<?php print $zone2; ?>
					</div>
					
				</div>
			</div>
		
		</div> <!-- /uboxpb_items -->
		
		<?php print $sharethis; ?>
		
	  	<?php if (false && $terms): ?>
			<div class="ruban"><?php print $terms; ?></div>
		<?php endif;?>
	  	
		<?php  /*?>		  
	  	<div class="<?php if($content_right): ?>col_2<?php else: ?>col_1<?php endif; ?>">
	
		    <?php if ($submitted): ?>
		      <span class="submitted"><?php print $submitted; ?></span>
		    <?php endif; ?>
		
		    <div class="content">
		      <?php print $content; ?>
		    </div>
		
		    <?php if ($terms): ?>
		      <div class="taxonomy"><?php print $terms; ?></div>
		    <?php endif;?>
		
		    <?php if ($links): ?> 
		      <div class="links"> <?php print $links; ?></div>
		    <?php endif; ?>
	
	  	</div> <!-- /col -->
	  
		<?php if($content_right): ?>
			<div class="content_right" ?>
				<?php print $content_right; ?>
			</div>
		<?php endif; ?>
		
		*/ ?>
	  
	</div> <!-- /node-->
  <?php if($list_theme_sejwe_by_theme): ?>
    <?php print $list_theme_sejwe_by_theme; ?>
  <?php endif; ?>
	
<?php endif; /* /ubox_simple */ ?>