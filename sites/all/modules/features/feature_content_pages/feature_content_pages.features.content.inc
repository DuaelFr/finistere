<?php

/**
 * Implementation of hook_content_default_fields().
 */
function feature_content_pages_content_default_fields() {
  $fields = array();

  // Exported field: field_hidesimpleshare
  $fields['hqitem-field_hidesimpleshare'] = array(
    'field_name' => 'field_hidesimpleshare',
    'type_name' => 'hqitem',
    'display_settings' => array(
      'weight' => '25',
      'parent' => '',
      '2' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      '3' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      'ubox_resume' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      'ubox_slideshow' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      'ubox_ruban' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      'ubox_ruban_slideshow' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      'label' => array(
        'format' => 'hidden',
      ),
      'teaser' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      'full' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      '4' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '5' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'token' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'number_integer',
    'required' => '0',
    'multiple' => '0',
    'module' => 'number',
    'active' => '1',
    'prefix' => '',
    'suffix' => '',
    'min' => '',
    'max' => '',
    'allowed_values' => '0|Non
1|Oui',
    'allowed_values_php' => '',
    'widget' => array(
      'default_value' => array(
        '0' => array(
          'value' => '0',
        ),
      ),
      'default_value_php' => NULL,
      'label' => 'Cacher le partage réseaux',
      'weight' => '27',
      'description' => '',
      'type' => 'optionwidgets_select',
      'module' => 'optionwidgets',
    ),
  );

  // Exported field: field_hq_file
  $fields['hqitem-field_hq_file'] = array(
    'field_name' => 'field_hq_file',
    'type_name' => 'hqitem',
    'display_settings' => array(
      'weight' => '22',
      'parent' => '',
      '2' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      '3' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      'ubox_resume' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      'ubox_slideshow' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      'ubox_ruban' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      'ubox_ruban_slideshow' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      'label' => array(
        'format' => 'hidden',
      ),
      'teaser' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      'full' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      '4' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '5' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'token' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'filefield',
    'required' => '0',
    'multiple' => '0',
    'module' => 'filefield',
    'active' => '1',
    'list_field' => '0',
    'list_default' => 1,
    'description_field' => '0',
    'widget' => array(
      'file_extensions' => 'pdf doc docx xls xlsx',
      'file_path' => 'hqfiles',
      'progress_indicator' => 'bar',
      'max_filesize_per_file' => '',
      'max_filesize_per_node' => '',
      'label' => 'Fichier attaché',
      'weight' => '24',
      'description' => '',
      'type' => 'filefield_widget',
      'module' => 'filefield',
    ),
  );

  // Exported field: field_hq_view_name
  $fields['hqitem-field_hq_view_name'] = array(
    'field_name' => 'field_hq_view_name',
    'type_name' => 'hqitem',
    'display_settings' => array(
      'weight' => '5',
      'parent' => '',
      '2' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      '3' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      'ubox_resume' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'ubox_slideshow' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'ubox_ruban' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'ubox_ruban_slideshow' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'label' => array(
        'format' => 'hidden',
      ),
      'teaser' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      'full' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      '4' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '5' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'token' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'text',
    'required' => '0',
    'multiple' => '0',
    'module' => 'text',
    'active' => '1',
    'text_processing' => '0',
    'max_length' => '',
    'allowed_values' => 'hq_affichage_list|Affichage liste
hq_affichage_files|Liste de fichiers
hqflux_display_list_as_hqchild|Flux sans formulaire
hqflux_search_influx|Recherche dans un flux',
    'allowed_values_php' => '',
    'widget' => array(
      'default_value' => array(
        '0' => array(
          'value' => '',
        ),
      ),
      'default_value_php' => NULL,
      'label' => 'Type d\'affichage des fils',
      'weight' => '7',
      'description' => 'Laisser vide pour l\'affichage par défaut.',
      'type' => 'optionwidgets_select',
      'module' => 'optionwidgets',
    ),
  );

  // Exported field: field_hqitem_childrenlist_title
  $fields['hqitem-field_hqitem_childrenlist_title'] = array(
    'field_name' => 'field_hqitem_childrenlist_title',
    'type_name' => 'hqitem',
    'display_settings' => array(
      'weight' => '7',
      'parent' => '',
      '2' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      '3' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      'ubox_resume' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      'ubox_slideshow' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      'ubox_ruban' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      'ubox_ruban_slideshow' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      'label' => array(
        'format' => 'hidden',
      ),
      'teaser' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      'full' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      '4' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '5' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'token' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'text',
    'required' => '0',
    'multiple' => '0',
    'module' => 'text',
    'active' => '1',
    'text_processing' => '0',
    'max_length' => '',
    'allowed_values' => '',
    'allowed_values_php' => '',
    'widget' => array(
      'rows' => 5,
      'size' => '60',
      'default_value' => array(
        '0' => array(
          'value' => '',
          '_error_element' => 'default_value_widget][field_hqitem_childrenlist_title][0][value',
        ),
      ),
      'default_value_php' => NULL,
      'label' => 'Titre de la liste des fils',
      'weight' => '10',
      'description' => 'Entrez ici le titre de la liste des fils de ce contenu.',
      'type' => 'text_textfield',
      'module' => 'text',
    ),
  );

  // Exported field: field_hqitem_connexlist_title
  $fields['hqitem-field_hqitem_connexlist_title'] = array(
    'field_name' => 'field_hqitem_connexlist_title',
    'type_name' => 'hqitem',
    'display_settings' => array(
      'weight' => '8',
      'parent' => '',
      '2' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      '3' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      'ubox_resume' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      'ubox_slideshow' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      'ubox_ruban' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      'ubox_ruban_slideshow' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      'label' => array(
        'format' => 'hidden',
      ),
      'teaser' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      'full' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      '4' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '5' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'token' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'text',
    'required' => '0',
    'multiple' => '0',
    'module' => 'text',
    'active' => '1',
    'text_processing' => '0',
    'max_length' => '',
    'allowed_values' => '',
    'allowed_values_php' => '',
    'widget' => array(
      'rows' => 5,
      'size' => '60',
      'default_value' => array(
        '0' => array(
          'value' => '',
          '_error_element' => 'default_value_widget][field_hqitem_connexlist_title][0][value',
        ),
      ),
      'default_value_php' => NULL,
      'label' => 'Titre de la liste des contenus connexes',
      'weight' => '11',
      'description' => 'Entrez ici le titre de la liste des contenus connexe. Cette liste apparaît quand la liste des fils est vide (généralement dans les feuilles de l\'arbre hiérarchique).',
      'type' => 'text_textfield',
      'module' => 'text',
    ),
  );

  // Exported field: field_hqitem_fluxdisplay
  $fields['hqitem-field_hqitem_fluxdisplay'] = array(
    'field_name' => 'field_hqitem_fluxdisplay',
    'type_name' => 'hqitem',
    'display_settings' => array(
      'weight' => '6',
      'parent' => '',
      '2' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      '3' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      'ubox_resume' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'ubox_slideshow' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'ubox_ruban' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'ubox_ruban_slideshow' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'label' => array(
        'format' => 'hidden',
      ),
      'teaser' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      'full' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      '4' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '5' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'token' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'text',
    'required' => '0',
    'multiple' => '0',
    'module' => 'text',
    'active' => '1',
    'text_processing' => '0',
    'max_length' => '',
    'allowed_values' => 'block_1|Rechercher un chambre d\'hôte
block_38|Rechercher location meublé
block_2|Rechercher un hôtel
block_3|Rechercher un centre aquatique
block_4|Rechercher une thalasso
block_5|Rechercher une plage surveillée
block_6|Rechercher un centre aquatique
block_7|Rechercher un labyrinte
block_8|Rechercher une île
block_9|Rechercher les abers
block_10|Rechercher une baie
block_11|Rechercher un casino
block_12|Rechercher mongolfière
block_13|Rechercher un parc animalier
block_14|Rechercher un parc de loisirs
block_15|Rechercher promenade en bateau ou train
block_16|Rechercher un port de plaisance
block_17|Rechercher un port pittoresque
block_18|Rechercher un port de pêche
block_19|Rechercher un parc ou jardin
block_20|Rechercher un marché
block_21|Rechercher un restaurant
block_22|Rechercher un office de tourisme
block_23|Rechercher un phare
block_24|Rechercher un enclos
block_25|Rechercher un musée d\'art
block_26|Rechercher un musée d\'histoire
block_27|Rechercher un aquarium
block_28|Rechercher aviron
block_29|Rechercher canoë kayak
block_30|Rechercher char à voile
block_31|Rechercher sports sous-marins
block_32|Rechercher voile légère
block_45|Rechercher voile traditionnelle
block_46|Rechercher voile habitable
block_33|Rechercher kite surf
block_34|Rechercher wave ski
block_35|Rechercher funboard
block_36|Rechercher ski nautique
block_37|Rechercher campings
block_39|Rechercher résidence de tourisme
block_40|Rechercher gîte étape
block_41|Rechercher village vacance
block_42|Rechercher aires de camping car
block_43|Rechercher un château
block_44|Rechercher maison de site
block_47|EN HOT Hôtel
block_48|EN HPA Camping
block_49|EN HLO Meublés
block_50|EN HLO Chambres
block_51|EN HLO Résidences
block_52|EN HLO Gîtes d\'étape
block_53|EN VIL Villages vacances
block_54|EN B0018 Aires de camping car
block_55|EN RES Restaurant
block_56|EN LOI Plages surveillées
block_57|EN LOI Centres aquatiques
block_58|EN LOI Parcs de loisirs
block_59|EN LOI Zoo
block_60|EN LOI Promenade train + bateau
block_61|EN LOI Ports de plaisance
block_63|EN PNA Islands
block_64|EN PNA Port de Pêche
block_65|EN PNA Parcs et jardins
block_66|EN PCU Maison de site
block_67|EN PCU Phares
block_68|EN PCU Enclos
block_69|EN PCU Chateaux
block_70|EN PCU Musées art
block_71|EN PCU Musées histoire
block_72|EN ASC Voile légère
block_73|EN ORG Offices de tourisme',
    'allowed_values_php' => '',
    'widget' => array(
      'default_value' => array(
        '0' => array(
          'value' => '',
        ),
      ),
      'default_value_php' => NULL,
      'label' => 'Flux avec recherche',
      'weight' => '8',
      'description' => 'Si vous avez sélectionné "Recherche de fiches" dans le champ "Type d\'affichage des fils", vous devez sélectionner un flux sur lequel rechercher.',
      'type' => 'optionwidgets_select',
      'module' => 'optionwidgets',
    ),
  );

  // Exported field: field_hqitem_fluxtid
  $fields['hqitem-field_hqitem_fluxtid'] = array(
    'field_name' => 'field_hqitem_fluxtid',
    'type_name' => 'hqitem',
    'display_settings' => array(
      'weight' => '6',
      'parent' => '',
      '2' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      '3' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      'ubox_resume' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'ubox_slideshow' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'ubox_ruban' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'ubox_ruban_slideshow' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'label' => array(
        'format' => 'hidden',
      ),
      'teaser' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      'full' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      '4' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '5' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'token' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'number_integer',
    'required' => '0',
    'multiple' => '0',
    'module' => 'number',
    'active' => '1',
    'prefix' => '',
    'suffix' => '',
    'min' => '',
    'max' => '',
    'allowed_values' => '403|CCA Aires de comping car
422|FMA Festivals
288|FMA Machés
404|FMA Fêtes et manifestations
441|PNA Abers
442|PNA baies
443|PNA Grands sites de france
444|PNA Ports de pêche
417|PNA Ports pitoresques
445|PNA Spots
416|PNA Îles
415|PCU Châteaux
436|PCU Basilique
439|PCU Enclos
437|PCU Musée
438|PCU Musée histoire
435|PCU Parcs et jardins
440|PCU Phares
411|HPA Roulottes
419|VIL Auberges de jeunesse
424|LOI Thalasso
423|LOI Labyrinthe
428|LOI Casinos
430|LOI Montgolfière
432|LOI Golfs
434|LOI Yacht Clubs
5398|LOI Parcs à Thèmes
2637|ASC Parcours dans les arbres
285|Séjours
2628|HLO Agence immobilière
5035|PCU Visite entreprise
2738|EN PCU Phares
2739|EN PNA Abers
2740|EN PNA Baies
2726|EN LOI Casinos
2721|EN LOI Labyrinthe
2728|EN LOI Montgolfiere
2725|EN LOI Aquariums
2722|EN LOI Thalasso
2697|EN ASC Aviron
2708|EN ORG Offices de tourisme
2713|EN ASC Canoe Kayak
2699|EN CCA Camping Cars
2714|EN ASC Char à voile
2715|EN ASC Sports sous marin
2693|EN ASC Voile habitable
2695|EN ASC Voile traditionnelle
2716|EN ASC Kite surf
2717|EN ASC Wave ski
2718|EN ASC Funboard
2719|EN ASC Ski nautique
2732|EN LOI Yacht clubs
2730|EN LOI Golf
2700|EN HLO Agence immobiliere
2705|EN HPA Roulottes
6326|EN VIL Auberge de jeunesse',
    'allowed_values_php' => '',
    'widget' => array(
      'default_value' => array(
        '0' => array(
          'value' => '',
        ),
      ),
      'default_value_php' => NULL,
      'label' => 'Flux comme fils',
      'weight' => '9',
      'description' => 'Si vous avez choisi "Liste simple de fiches issues d\'un flux" comme type d\'affichage des fils, veuillez sélectionner ici le flux à afficher.',
      'type' => 'optionwidgets_select',
      'module' => 'optionwidgets',
    ),
  );

  // Exported field: field_hqitem_menuimg
  $fields['hqitem-field_hqitem_menuimg'] = array(
    'field_name' => 'field_hqitem_menuimg',
    'type_name' => 'hqitem',
    'display_settings' => array(
      'weight' => '11',
      'parent' => '',
      '2' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      '3' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      'ubox_resume' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      'ubox_slideshow' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      'ubox_ruban' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      'ubox_ruban_slideshow' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      'label' => array(
        'format' => 'hidden',
      ),
      'teaser' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      'full' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      '4' => array(
        'format' => 'image_plain',
        'exclude' => 0,
      ),
      '5' => array(
        'format' => 'image_plain',
        'exclude' => 0,
      ),
      'token' => array(
        'format' => 'image_plain',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'filefield',
    'required' => '0',
    'multiple' => '1',
    'module' => 'filefield',
    'active' => '1',
    'list_field' => '0',
    'list_default' => 1,
    'description_field' => '0',
    'widget' => array(
      'file_extensions' => 'png gif jpg jpeg',
      'file_path' => 'hqitems/menuimg',
      'progress_indicator' => 'bar',
      'max_filesize_per_file' => '',
      'max_filesize_per_node' => '',
      'max_resolution' => '300x300',
      'min_resolution' => '120x120',
      'alt' => '',
      'custom_alt' => 0,
      'title' => '',
      'custom_title' => 0,
      'title_type' => 'textfield',
      'default_image' => NULL,
      'use_default_image' => 0,
      'label' => 'Images de menu',
      'weight' => '14',
      'description' => 'Chercger ici les images qui seront affichées dans le menu au survol de l\'item concerné.',
      'type' => 'imagefield_widget',
      'module' => 'imagefield',
    ),
  );

  // Exported field: field_hqitem_pageimg
  $fields['hqitem-field_hqitem_pageimg'] = array(
    'field_name' => 'field_hqitem_pageimg',
    'type_name' => 'hqitem',
    'display_settings' => array(
      'weight' => '-3',
      'parent' => '',
      '2' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      '3' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      'ubox_resume' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      'ubox_slideshow' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      'ubox_ruban' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      'ubox_ruban_slideshow' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      'label' => array(
        'format' => 'hidden',
      ),
      'teaser' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      'full' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      '4' => array(
        'format' => 'image_plain',
        'exclude' => 0,
      ),
      '5' => array(
        'format' => 'image_plain',
        'exclude' => 0,
      ),
      'token' => array(
        'format' => 'image_plain',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'filefield',
    'required' => '0',
    'multiple' => '0',
    'module' => 'filefield',
    'active' => '1',
    'list_field' => '0',
    'list_default' => 1,
    'description_field' => '0',
    'widget' => array(
      'file_extensions' => 'png gif jpg jpeg',
      'file_path' => 'hqitem/pageimg',
      'progress_indicator' => 'bar',
      'max_filesize_per_file' => '',
      'max_filesize_per_node' => '',
      'max_resolution' => '800x800',
      'min_resolution' => '0',
      'alt' => '',
      'custom_alt' => 0,
      'title' => '',
      'custom_title' => 0,
      'title_type' => 'textfield',
      'default_image' => NULL,
      'use_default_image' => 0,
      'label' => 'Image de page',
      'weight' => '-3',
      'description' => '',
      'type' => 'imagefield_widget',
      'module' => 'imagefield',
    ),
  );

  // Exported field: field_hqitem_parent
  $fields['hqitem-field_hqitem_parent'] = array(
    'field_name' => 'field_hqitem_parent',
    'type_name' => 'hqitem',
    'display_settings' => array(
      'weight' => '1',
      'parent' => '',
      '2' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      '3' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      'ubox_resume' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      'ubox_slideshow' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      'ubox_ruban' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      'ubox_ruban_slideshow' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      'label' => array(
        'format' => 'hidden',
      ),
      'teaser' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      'full' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      '4' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '5' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'token' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'nodereference',
    'required' => '0',
    'multiple' => '0',
    'module' => 'nodereference',
    'active' => '1',
    'referenceable_types' => array(
      'hqitem' => 'hqitem',
      'custom_design' => 0,
      'hpa' => 0,
      'page' => 0,
      'ubox' => 0,
      'webform' => 0,
    ),
    'advanced_view' => '--',
    'advanced_view_args' => '',
    'widget' => array(
      'autocomplete_match' => 'contains',
      'size' => '60',
      'default_value' => array(
        '0' => array(
          'nid' => NULL,
          '_error_element' => 'default_value_widget][field_hqitem_parent][0][nid][nid',
        ),
      ),
      'default_value_php' => NULL,
      'label' => 'Contenu parent',
      'weight' => '2',
      'description' => 'Choisissez le contenu parent de celui-ci. Laissez vide pour considérer ce contenu comme "primaire".',
      'type' => 'nodereference_autocomplete',
      'module' => 'nodereference',
    ),
  );

  // Exported field: field_hqitem_poids
  $fields['hqitem-field_hqitem_poids'] = array(
    'field_name' => 'field_hqitem_poids',
    'type_name' => 'hqitem',
    'display_settings' => array(
      'weight' => '9',
      'parent' => '',
      '2' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      '3' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      'ubox_resume' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      'ubox_slideshow' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      'ubox_ruban' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      'ubox_ruban_slideshow' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      'label' => array(
        'format' => 'hidden',
      ),
      'teaser' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      'full' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      '4' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '5' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'token' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'number_integer',
    'required' => '0',
    'multiple' => '0',
    'module' => 'number',
    'active' => '1',
    'prefix' => '',
    'suffix' => '',
    'min' => '',
    'max' => '',
    'allowed_values' => '',
    'allowed_values_php' => '',
    'widget' => array(
      'default_value' => array(
        '0' => array(
          'value' => '0',
          '_error_element' => 'default_value_widget][field_hqitem_poids][0][value',
        ),
      ),
      'default_value_php' => NULL,
      'label' => 'Poids',
      'weight' => '12',
      'description' => 'Entrer ici le poids de l\'item. Ceci sert à ordonner les contenus dans les listes. Le poids le plus petit en premier.',
      'type' => 'number',
      'module' => 'number',
    ),
  );

  // Exported field: field_hqitem_primimg
  $fields['hqitem-field_hqitem_primimg'] = array(
    'field_name' => 'field_hqitem_primimg',
    'type_name' => 'hqitem',
    'display_settings' => array(
      'weight' => '4',
      'parent' => '',
      '2' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      '3' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      'ubox_resume' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      'ubox_slideshow' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      'ubox_ruban' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      'ubox_ruban_slideshow' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      'label' => array(
        'format' => 'hidden',
      ),
      'teaser' => array(
        'format' => 'prim_list_img_linked',
        'exclude' => 0,
      ),
      'full' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      '4' => array(
        'format' => 'image_plain',
        'exclude' => 0,
      ),
      '5' => array(
        'format' => 'image_plain',
        'exclude' => 0,
      ),
      'token' => array(
        'format' => 'image_plain',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'filefield',
    'required' => '0',
    'multiple' => '0',
    'module' => 'filefield',
    'active' => '1',
    'list_field' => '0',
    'list_default' => 1,
    'description_field' => '0',
    'widget' => array(
      'file_extensions' => 'png gif jpg jpeg',
      'file_path' => 'hqitem/primteaserimg',
      'progress_indicator' => 'bar',
      'max_filesize_per_file' => '',
      'max_filesize_per_node' => '',
      'max_resolution' => '400x400',
      'min_resolution' => '0',
      'alt' => '',
      'custom_alt' => 0,
      'title' => '',
      'custom_title' => 0,
      'title_type' => 'textfield',
      'default_image' => NULL,
      'use_default_image' => 0,
      'label' => 'Image de liste primaire',
      'weight' => '6',
      'description' => 'Charger ici l\'image affichée dans la liste principale (nécessaire uniquement pour les contenus primaires).',
      'type' => 'imagefield_widget',
      'module' => 'imagefield',
    ),
  );

  // Exported field: field_hqitem_rightbox
  $fields['hqitem-field_hqitem_rightbox'] = array(
    'field_name' => 'field_hqitem_rightbox',
    'type_name' => 'hqitem',
    'display_settings' => array(
      'weight' => 0,
      'parent' => '',
      '2' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      '3' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      'ubox_resume' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      'ubox_slideshow' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      'ubox_ruban' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      'ubox_ruban_slideshow' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      'label' => array(
        'format' => 'hidden',
      ),
      'teaser' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      'full' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      '4' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '5' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'token' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'text',
    'required' => '0',
    'multiple' => '0',
    'module' => 'text',
    'active' => '1',
    'text_processing' => '1',
    'max_length' => '',
    'allowed_values' => '',
    'allowed_values_php' => '',
    'widget' => array(
      'rows' => '10',
      'size' => 60,
      'default_value' => array(
        '0' => array(
          'value' => '',
          '_error_element' => 'default_value_widget][field_hqitem_rightbox][0][value',
        ),
      ),
      'default_value_php' => NULL,
      'label' => 'Encart droit',
      'weight' => '-1',
      'description' => 'Entrer ici le contenu à afficher dans l\'encart droit.',
      'type' => 'text_textarea',
      'module' => 'text',
    ),
  );

  // Exported field: field_hqitem_teaserimg
  $fields['hqitem-field_hqitem_teaserimg'] = array(
    'field_name' => 'field_hqitem_teaserimg',
    'type_name' => 'hqitem',
    'display_settings' => array(
      'weight' => '3',
      'parent' => '',
      '2' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      '3' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      'ubox_resume' => array(
        'format' => 'image_plain',
        'exclude' => 1,
      ),
      'ubox_slideshow' => array(
        'format' => 'image_plain',
        'exclude' => 1,
      ),
      'ubox_ruban' => array(
        'format' => 'image_plain',
        'exclude' => 1,
      ),
      'ubox_ruban_slideshow' => array(
        'format' => 'image_plain',
        'exclude' => 1,
      ),
      'label' => array(
        'format' => 'hidden',
      ),
      'teaser' => array(
        'format' => 'hqitem_teaser_linked',
        'exclude' => 0,
      ),
      'full' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      '4' => array(
        'format' => 'image_plain',
        'exclude' => 0,
      ),
      '5' => array(
        'format' => 'image_plain',
        'exclude' => 0,
      ),
      'token' => array(
        'format' => 'image_plain',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'filefield',
    'required' => '0',
    'multiple' => '0',
    'module' => 'filefield',
    'active' => '1',
    'list_field' => '0',
    'list_default' => 1,
    'description_field' => '0',
    'widget' => array(
      'file_extensions' => 'png gif jpg jpeg',
      'file_path' => 'hqitem/teaserimg',
      'progress_indicator' => 'bar',
      'max_filesize_per_file' => '',
      'max_filesize_per_node' => '',
      'max_resolution' => '400x400',
      'min_resolution' => '',
      'alt' => '',
      'custom_alt' => 0,
      'title' => '',
      'custom_title' => 0,
      'title_type' => 'textfield',
      'default_image' => NULL,
      'use_default_image' => 0,
      'label' => 'Image de liste',
      'weight' => '5',
      'description' => '',
      'type' => 'imagefield_widget',
      'module' => 'imagefield',
    ),
  );

  // Exported field: field_page_customdesign
  $fields['page-field_page_customdesign'] = array(
    'field_name' => 'field_page_customdesign',
    'type_name' => 'page',
    'display_settings' => array(
      'weight' => '-3',
      'parent' => '',
      'ubox_resume' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      'ubox_slideshow' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      'label' => array(
        'format' => 'above',
      ),
      'teaser' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'full' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '4' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '2' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '3' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'token' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'nodereference',
    'required' => '0',
    'multiple' => '0',
    'module' => 'nodereference',
    'active' => '1',
    'referenceable_types' => array(
      'custom_design' => 'custom_design',
      'decouv_item' => 0,
      'page' => 0,
      'ubox_area' => 0,
      'webform' => 0,
    ),
    'advanced_view' => '--',
    'advanced_view_args' => '',
    'widget' => array(
      'autocomplete_match' => 'contains',
      'size' => 60,
      'default_value' => array(
        '0' => array(
          'nid' => '',
        ),
      ),
      'default_value_php' => NULL,
      'label' => 'Custom Design',
      'weight' => '-3',
      'description' => '',
      'type' => 'nodereference_select',
      'module' => 'nodereference',
    ),
  );

  // Exported field: field_page_thumbnails
  $fields['page-field_page_thumbnails'] = array(
    'field_name' => 'field_page_thumbnails',
    'type_name' => 'page',
    'display_settings' => array(
      'weight' => 0,
      'parent' => '',
      'ubox_resume' => array(
        'format' => 'page_type_visuel_large_linked',
        'exclude' => 1,
      ),
      'ubox_slideshow' => array(
        'format' => 'image_nodelink',
        'exclude' => 0,
      ),
      'label' => array(
        'format' => 'hidden',
      ),
      'teaser' => array(
        'format' => 'image_plain',
        'exclude' => 0,
      ),
      'full' => array(
        'format' => 'image_plain',
        'exclude' => 0,
      ),
      '4' => array(
        'format' => 'image_plain',
        'exclude' => 0,
      ),
      '2' => array(
        'format' => 'image_plain',
        'exclude' => 0,
      ),
      '3' => array(
        'format' => 'image_plain',
        'exclude' => 0,
      ),
      'token' => array(
        'format' => 'image_plain',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'filefield',
    'required' => '0',
    'multiple' => '0',
    'module' => 'filefield',
    'active' => '1',
    'list_field' => '0',
    'list_default' => 1,
    'description_field' => '1',
    'widget' => array(
      'file_extensions' => 'png gif jpg jpeg',
      'file_path' => '',
      'progress_indicator' => 'bar',
      'max_filesize_per_file' => '',
      'max_filesize_per_node' => '',
      'max_resolution' => '0',
      'min_resolution' => '0',
      'alt' => '',
      'custom_alt' => 0,
      'title' => '',
      'custom_title' => 0,
      'title_type' => 'textfield',
      'default_image' => NULL,
      'use_default_image' => 0,
      'label' => 'Thumbnails',
      'weight' => 0,
      'description' => 'Thumbnails to show in teasers',
      'type' => 'imagefield_widget',
      'module' => 'imagefield',
    ),
  );

  // Exported field: field_page_topimages
  $fields['page-field_page_topimages'] = array(
    'field_name' => 'field_page_topimages',
    'type_name' => 'page',
    'display_settings' => array(
      'weight' => '-2',
      'parent' => '',
      'ubox_resume' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      'ubox_slideshow' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      'label' => array(
        'format' => 'above',
      ),
      'teaser' => array(
        'format' => 'image_plain',
        'exclude' => 0,
      ),
      'full' => array(
        'format' => 'image_plain',
        'exclude' => 0,
      ),
      '4' => array(
        'format' => 'image_plain',
        'exclude' => 0,
      ),
      '2' => array(
        'format' => 'image_plain',
        'exclude' => 0,
      ),
      '3' => array(
        'format' => 'image_plain',
        'exclude' => 0,
      ),
      'token' => array(
        'format' => 'image_plain',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'filefield',
    'required' => '0',
    'multiple' => '1',
    'module' => 'filefield',
    'active' => '1',
    'list_field' => '0',
    'list_default' => 1,
    'description_field' => '1',
    'widget' => array(
      'file_extensions' => 'png gif jpg jpeg',
      'file_path' => '',
      'progress_indicator' => 'bar',
      'max_filesize_per_file' => '',
      'max_filesize_per_node' => '',
      'max_resolution' => '0',
      'min_resolution' => '0',
      'alt' => '',
      'custom_alt' => 0,
      'title' => '',
      'custom_title' => 0,
      'title_type' => 'textfield',
      'default_image' => NULL,
      'use_default_image' => 0,
      'label' => 'Top images',
      'weight' => '-2',
      'description' => 'Images to display in top of content',
      'type' => 'imagefield_widget',
      'module' => 'imagefield',
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Cacher le partage réseaux');
  t('Contenu parent');
  t('Custom Design');
  t('Encart droit');
  t('Fichier attaché');
  t('Flux avec recherche');
  t('Flux comme fils');
  t('Image de liste');
  t('Image de liste primaire');
  t('Image de page');
  t('Images de menu');
  t('Poids');
  t('Thumbnails');
  t('Titre de la liste des contenus connexes');
  t('Titre de la liste des fils');
  t('Top images');
  t('Type d\'affichage des fils');

  return $fields;
}
