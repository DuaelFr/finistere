<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<?php
  $head_title = 'Finistere Tourisme - Site-offline';
  $logo = 'sites/default/files/cdt2011_logo.png';

  // If your theme is set to display the site name, uncomment this line and replace the value:
  // $site_name = 'Your Site Name';

  // If your theme is set to *not* display the site name, uncomment this line:
  unset($site_name);

  // If your theme is set to display the site slogan, uncomment this line and replace the value:
  $site_slogan = '';

  // If your theme is set to *not* display the site slogan, uncomment this line:
  // unset($site_slogan);

  // Main message. Note HTML markup.

  $content = '<p>Le site est actuellement indisponible pour des raisons techniques. Nous faisons notre possible pour le rétablir.</p>';
?><html xmlns="http://www.w3.org/1999/xhtml" xml:lang="<?php print $language->language ?>" lang="<?php print $language->language ?>" dir="<?php print $language->dir ?>">
  <head>
    
    <title><?php print $head_title; ?></title>
    <meta name="robots" content="noindex,nofollow" />
    <?php print $head; ?>
    <?php print $styles; ?>
    <noscript><link href="<?php print $base_path . path_to_theme() ?>/css/no_script.css" rel="stylesheet" type="text/css" media="screen" /></noscript>
    
    <!--[if IE]>
			<link href="<?php print $base_path . path_to_theme() ?>/css/IE.css" rel="stylesheet" type="text/css" media="screen" />
		<![endif]-->
		
		<!--[if IE 7]>
			<link href="<?php print $base_path . path_to_theme() ?>/css/IE7.css" rel="stylesheet" type="text/css" media="screen" />
		<![endif]-->
    <?php if($cuss_inline): ?>
    	<style type="text/css"><?php print $cuss_inline; ?></style>
    <?php endif; ?>
  </head>

  <body class="<?php print $body_classes; ?> page_type">

		<!-- =================Header============================== -->
		<div id="<?php print $header_id; ?>">
			<div id="logo">
				<?php if (!empty($logo)): ?>
		          <a href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>" rel="home" id="logo">
		            <img src="<?php print $logo; ?>" alt="<?php print t('Home') . " " . $site_name; ?>"/>
		          </a>
		        <?php endif; ?>
		    </div>
		    <?php if($header): ?>
		    <div id="conteneur_menu_haut">
		    	<?php print $header; ?>
		    	<ul id="carnet">
				      <li><?php print l(t('Bookmarks'), 'carnet-de-voyage'); ?></li>
				    </ul>
		    </div>
				<?php endif; ?>
		    
		    <?php print $search_box; ?>
		
		</div>
		
		<?php if($primary_links): ?>
			<div id="conteneur_menu">
				<?php print menu_tree_output_level($primary_links); ?>
			</div>
		<?php endif; ?>
		
		<!-- =============Fin=Header============================== -->
		<div id="wrap-all-container" class="clearfix">
  		<div id="conteneur">
  		<!-- =============Conteneur LEFT============================== -->
  		  <div id="conteneur_left">  
  			<?php if ($breadcrumb || $messages || $help || $tabs): ?>
  		    <div id="content-header">
  		
  		      <?php print $breadcrumb; ?>
  		
  		      <?php print $messages; ?>
  		
  		      <?php print $help; ?> 
  		
  		      <?php if ($tabs): ?>
  		        <div class="tabs"><?php print $tabs; ?></div>
  		      <?php endif; ?>
  		
  		    </div> <!-- /#content-header -->
  		  <?php endif; ?>
  		
  			<?php if ($content_top): ?>
  		    <div id="content-top">
  		      <?php print $content_top; ?>
  		    </div> <!-- /#content-top -->
  		  <?php endif; ?>
  		
  				<div id="content-area">
  					<?php print $content; ?>
  				</div>
  		
  		  <?php if ($content_bottom): ?>
  		    <div id="content-bottom">
  		      <?php print $content_bottom; ?>
  		    </div><!-- /#content-bottom -->
  		  <?php endif; ?>
  			</div>
  		<!-- =========FIN=Conteneur LEFT============================== -->  
  		<?php if($right): ?> 
  		<!-- ==========Conteneur RIGHT============================== -->
  			<div id="conteneur_right">
  			  <?php print $right; ?>
  			</div>  <!-- =========FIN=Conteneur RIGHT============================== --> 
  		<?php endif; ?>
  		
  		<?php if($bottom): ?>
  			<?php print $bottom; ?>
  		<?php endif; ?>
  		
  		</div><!-- =========FIN=Conteneur ============================== -->   
		</div><!-- =========FIN=wrap-all-container ============================== -->
		<?php if($footer || $footer_message || $footer_top): ?>
		<!-- =============Conteneur Footer============================== --> 
		<div id="conteneur_footer">
			<?php if($footer_top): ?>
			<div id="conteneur_newsletter">
		    <div id="newsletters">
					<?php print $footer_top; ?>
				</div>
		  </div>
			<?php endif; ?>
		  <?php if($footer || $footer_message): ?>
			<div id="footer" class="clearfix">
				<?php print $footer; ?>
				<?php print menu_tree_output_footer(menu_tree_page_data(variable_get('menu_primary_links_source', 'primary-links')),'menu_footer'); ?>
				<div id="conteneur_mentions">
					<?php print $footer_message; ?>
				</div>
			</div>
		  <?php endif; ?>
		</div>
		<!-- =========FIN=Conteneur Footer============================== --> 
		<?php endif; ?>

    <?php print $closure; ?>
    <?php print $scripts; ?>
    
  </body>
</html>