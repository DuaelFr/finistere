<h1><?php print $title; ?></h1>
<?php /*if($nids): ?>

<?php print l(t('View result in the interactive map'), 'carte-interactive', array('query'=>array('nids'=>$nids))); ?>

<?php endif;*/ ?>

<img src="<?php print $base_path . path_to_theme() ?>/images/visuel-fma.jpg" alt="Évènements à Quimper" class="image_agenda" />

<?php print $top; ?>

<div id="conteneur_left_agenda_middle">

<?php print $middle; ?>
</div>