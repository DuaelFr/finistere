<?php if($ubox_resume): ?>
	
<div class="ubox_item_content">
  <h3><a href="<?php print $node_url ?>"><?php print $title; ?></a></h3>
  <?php echo $content; ?>
  <a href="<?php print $node_url ?>"><?php print t('More') ?></a>
</div>
<?php print $picture ?>
	
<?php else: ?>


<div class="node <?php print $classes; ?>" id="node-<?php print $node->nid; ?>">

	

  <div class="content">
        <div class="primlist-content-left">
        	<?php print $field_hqitem_primimg[0]['view']; ?>
        </div>
    	<div class="primlist-content-right">
			<h2 class="title"><a href="<?php print $node_url; ?>"><?php print $title; ?></a></h2>
    		<div class="teaser-body"><?php print $node->content['body']['#value']; ?></div>
  	        <?php print $node->content['backref']['#value']; ?>
    	</div>
      
      
    </div>

    <?php if (false && $terms): ?>
      <div class="taxonomy"><?php print $terms; ?></div>
    <?php endif;?>

  
  <?php if($content_right): ?>
  	<div class="content_right" ?>
  		<?php print $content_right; ?>
  	</div>
  <?php endif; ?>
  
</div> <!-- /node-->
<?php endif; /* /ubox_simple */ ?>