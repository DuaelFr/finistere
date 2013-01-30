<?php
// $Id: print.tpl.php,v 1.8.2.17 2010/08/18 00:33:34 jcnventura Exp $

/**
 * @file
 * Default print module template
 *
 * @ingroup print
 */
?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" lang="<?php print $print['language']; ?>" xml:lang="<?php print $print['language']; ?>">
  <head>
    <?php print $print['head']; ?>
    <?php print $print['base_href']; ?>
    <title><?php print $print['title']; ?></title>
    <?php print $print['scripts']; ?>
    <?php print $print['sendtoprinter']; ?>
    <?php print $print['robots_meta']; ?>
    <?php print $print['favicon']; ?>
    <?php print $print['css']; ?>
  </head>
  <body>
    <?php if (!empty($print['message'])) {
      print '<div class="print-message">'. $print['message'] .'</div><p />';
    } ?>
    <div class="print-logo"><?php print $print['logo']; ?></div>
    <div class="print-site_name"><?php print $print['site_name']; ?></div>
    <p />
    <div class="print-breadcrumb"><?php print $print['breadcrumb']; ?></div>
    <hr class="print-hr" />
		<h1 class="title"><?php print $title; ?></h1>
    <div class="print-content">

      <div class="uboxpb_items">

			<div class="uboxpb_items_left">

				<?php print $print['node']->content['field_fl_photos_imgs']['#children']; ?>

			<div class="uboxpb_items_left">
				<div class="uboxbp_content">

					<?php if($map): ?>
						<div class="node-map">
							<?php print $map; ?>
						</div>
					<?php endif; ?>

					<div class="uboxpb_items_content">
						<?php print $presentationzone; ?>
					</div>

					<?php if($zone2): ?>
					<div class="uboxpb_items_content">
						<?php print $zone2; ?>
					</div>
					<?php endif; ?>

				</div>
			</div>

				<div class="uboxbp_content">
					<div class="uboxpb_items_content addresszone">
						<?php print $addresszone; ?>
					</div>
					<?php if(count($node->field_fl_tarif_label)>0 && strlen($node->field_fl_tarif_label[0]['value'])>0): ?>
						<h4 class="lower"><?php print t('Prices'); ?></h4>
						<table id="table_tarif">
							<tr><td class="no_border"></td><td class="grey"><?php print t('Min');?></td><td class="grey"><?php print t('Max');?></td></tr>
							<?php
								$i=0;
								foreach($node->field_fl_tarif_label as $item){
									print '<tr><td class="grey">'.$item['value'].'</td><td class="grey">'.$node->field_fl_tarif_min[$i]['value'].'</td><td class="grey">'.$node->field_fl_tarif_max[$i]['value'].'</td></tr>';
									$i++;
								}
							?>
						</table>
					<?php endif; ?>

					<?php if($zone1): ?>
					<div class="uboxpb_items_content">
						<?php print $zone1; ?>
					</div>
					<?php endif; ?>
				</div>

			</div>

		</div> <!-- /uboxpb_items -->


    </div>
    <div class="print-footer"><?php print $print['footer_message']; ?></div>
    <hr class="print-hr" />
    <div class="print-source_url"><?php print $print['source_url']; ?></div>
    <img src="/sites/all/themes/gnova/cdt2011/images/print-footer.jpg" />
  </body>
</html>
