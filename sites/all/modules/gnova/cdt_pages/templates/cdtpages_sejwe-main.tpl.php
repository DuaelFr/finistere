<h1 class="none"><?php print $title; ?></h1>
<div id="wrap_left" class="clearfix">
	<?php print $topleft; ?>
	
	<h2 class="clear"><?php print t('OUR WEEKEND OFFERS'); ?></h2>
	<?php print $bottomleft; ?>
</div>

<div id="wrap_right" class="bons_plans">
	
	<ul class="resa_tabs clearfix"></ul>
	<div class="panes">
		<!--DEBUT CODE WIDGET-->
        <script type="text/javascript" xml:space="preserve">
			          	  
          	 function loadosformscript(sScriptSrc, oCallback) {
				var oHead = document.getElementsByTagName('head')[0];
				var oScript = document.createElement('script');
				oScript.type = 'text/javascript';
				oScript.src = sScriptSrc;
				// most browsers
				oScript.onload = oCallback;
				// IE 6 & 7
				oScript.onreadystatechange = function() {
				if (this.readyState == 'complete') {
					oCallback();
				}
				}
				oHead.appendChild(oScript);
				}
			  
			  function launchOSFG(){
			  	  
	              //jQuery.noConflict();
	              //Passage du code de Widget Open System Hôtel: 25810-1210
	              document.oswidget = new OsFG("OSRecherche","25810-1214", "<?php print $lang ?>", "/<?php print drupal_get_path('theme', 'cdt2011'); ?>/css/widget.css");
				  document.oswidget.SetOptionAffichage({"Navigation":"accordeon"});
	              jQuery(function () {
	                  //Passage du code unique Open System d'un hôtel, dans cet exemple: HRIT-7806
	                  document.oswidget.CodeOs("<?php print $node->field_fl_code_metier_tx[0]['value']; ?>-<?php print $node->field_fl_code_fournisseur_tx[0]['value']; ?>");
	                  //Provoque l'affichage du Widget
	                  document.oswidget.Affiche();		
	              });
              }
              
              
              function checkJquery(){
             	  if (window.jQuery) {
				        loadosformscript("http://gadget.open-system.fr/osform.min.js", launchOSFG);
				    } else {
				        window.setTimeout(checkJquery, 100);
				  }
			  }
			  
              checkJquery();
          </script>
          <div><div id="OSRecherche"></div></div>
          <div><div id="OSRecherche"></div></div>
          <!--FIN CODE WIDGET-->
	</div>
	
	<?php if($bottomright): ?>
	<h2><?php print $btmright_title; ?></h2>
	
	<?php print $bottomright; ?>
  <?php endif; ?>

</div>