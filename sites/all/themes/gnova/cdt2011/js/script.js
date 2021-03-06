(function($) {

  Drupal.behaviors.cdt2011 = function (context) {

    var debug = false;

    // Gestion du slideshow
    $('#homehead-toload li').each(function () {
      var search_url = $('#homehead-toload li:first-child').find(".url");
      var url = search_url.html();
      var search_text1 = $('#homehead-toload li:first-child').find(".text1");
      var text1 = search_text1.html();
      var search_text2 = $('#homehead-toload li:first-child').find(".text2");
      var text2 = search_text2.html();

      $(".diaporama").append('<li><div class="titre_slide">' + text1 + '<span>' + text2 + '</span></div><img src="' + url + '" alt="' + text1 + text2 + '" title="' + text1 + text2 + '" /></li>');

      $('#homehead-toload li:first-child').remove();
    });
    $(".diaporama").diaporama({
      animationSpeed: "slow",
      delay:          5,
      controls:       true
    });

    // Reorder Classement filter checkboxes to group them by "type" (clés, épis, étoiles...)
    var checkboxes = $('label[for="edit-classement"]', context).parent().find('.bef-checkboxes .form-item');
    var reordered = [], txt, parts, type, number, cbparent = checkboxes.parent();
    checkboxes.each(function() {
      txt = $(this).find('label').text();
      parts = txt.trim().split(' ');
      if (parts.length > 2) {
        type = 'special';
        number = txt.trim();
      } else {
        type = parts[1];
        number = parts[0];
      }
      // Remove final "s" to avoid plural issues
      if (type.charAt(type.length - 1) == 's') {
        type = type.substr(0, type.length - 1);
      }
      // Preset the array if it does not already exist
      if (!reordered[type]) {
        reordered[type] = [];
      }
      reordered[type][number] = $(this);
    });
    for (key in reordered) {
      for (elt in reordered[key]) {
        cbparent.append(reordered[key][elt]);
      }
    }

    // Ajout à la volée du picto lecture
    $("#ubox_box_89 .ubox_item_content #img_video").append('<span class="play"></span>');

    // Colorbox de la video
    $("#img_video").colorbox({iframe:true, innerWidth:425, innerHeight:344});

    // Wrap lonely pictures into a colorboxed link
    $('.uboxpb_items_left .field-item > .imagecache-bp_detail_big').each(function () {
      var img = $(this), link = $('<a>');
      link.attr('href', img.attr('src').replace('imagecache/bp_detail_big/', ''))
          .addClass('colorbox-load');
      img.wrap(link);
    });

    // Colorbox images fiches TS
    $('.colorbox-load').removeClass('colorbox-load')
      .addClass('colorbox-processed')
      .colorbox({
        rel:         'galery',
        maxWidth:    '95%',
        maxHeight:   '95%',
        scalePhotos: true
      });

    // Slide Panier
    $('#container-widget-panier').hover(
      function () {
        $('#widget-panier', this).stop(true, true).slideDown("fast");
      },
      function () {
        $('#widget-panier', this).stop(true, true).slideUp("fast");
      }
    );

    // Slide ssmenu
    // Gestion de l'ouverture et la fermeture du sous-menu
    $('.hover_ssmenu li').hover(
      function () {
        $('.hoverleft_ssmenu', this).stop(true, true).slideDown("fast");
      },
      function () {
        $('.hoverleft_ssmenu', this).stop(true, true).slideUp("fast");
      }
    );

    // Gestion de l'ouverture et la fermeture du sous-menu
    $(".hoverleft_ssmenu li").hover(function () {
        $('.ssmenu_img', this).data('hover', true).fadeIn("slow");
      },
      function () {
        $('.ssmenu_img', this).data('hover', false).fadeOut("slow");
      });

    // Apparition et disparition coup de coeur
    ($("#coup_de_coeur") || $("#coup_de_coeur a")).click(function () {
      $("#coup_de_coeur a").toggleClass('close');
      $(".box_hidden").slideToggle("slow");
    });

    // Slide Image
    ($(".scrollable") || $("#slide_agenda")).scrollable({circular:true});

    // ?
    $("#open_goodies").click(function () {
      $("#ssmenu_goodies").slideToggle("slow");
    });

    // Bons plans Détails Gallery
    $("ul.g-tabs").tabs(".lien_img");

    // Accordions
    $("body.page-carte-interactive #conteneur_right:not(.conteneur_right-processed)").addClass('conteneur_right-processed').tabs("#conteneur_right div.open_level_1", {tabs:'h3', effect:'slide', initialIndex:null});

    // Accordions
    $(".open_level_1 li.title > a:not(.open_level_1_a-processed)").addClass('open_level_1_a-processed').click(function () {
      // On empêche le navigateur de suivre le lien si le href ne contient pas de lien
      if ($(this).attr("href").substring(0, 10) != "javascript") {

      }
      else {
        // Si le sous-menu était déjà ouvert, on le referme :
        if ($(this).next("ul.open_level_2:visible").length != 0) {
          $(this).next("ul.open_level_2").slideUp("fast", function () {
            $(this).parent().removeClass("current")
          });
        }
        // Si le sous-menu est caché, on ferme les autres et on l'affiche :
        else {
          $(".open_level_1 ul.open_level_2").slideUp("fast", function () {
            $(this).parent().removeClass("current")
          });
          $(this).next("ul.open_level_2").slideDown("fast", function () {
            $(this).parent().addClass("current")
          });
        }
        return false;
      }
    });

    // Hover agenda bg white
    $(".box_agenda").hover(function () {
        $('.comments', this).data('hover', true).css({'background-color':'#FFF'});
      },
      function () {
        $('.comments', this).data('hover', true).css({'background-color':'#c6e0f8'});
      });

    // Tabs Widget
    $("ul.resa_tabs").tabs("div.panes > div");

    // Carnet bouton
    $(".add-to-carnet-btn:not(.add-to-carnet-btn-processed)").addClass('add-to-carnet-btn-processed').click(function (e) {
      e.preventDefault();
      var link = $(this);
      $.get(link.attr("href"), function () {
        link.replaceWith('<span class="add-to-carnet-added">' + Drupal.t('Added to carnet') + '</span>');
      });
    });

    // Ouverture du menu WE
    $(".wrap_content_we").hide();
    $(".see_WE").click(function () {
      $(".wrap_content_we").slideToggle("slow");
    });

    function loadOSPanierScript() {
      loadscript('http://gadget.open-system.fr/widgets/ospanier.min.js', loadOSPanier);
    }

    function loadOSPanier() {
      var infos = {
        GetLangue:     function () {
          return 'fr';
        },
        GetDomaine:    function () {
          return 'http://resa.finisteretourisme.com';
        },
        GetZoneDossier:function () {
          return 854;
        }
      };
      var widgetPanier = new AllianceReseaux.OsPanier('SUpJSUk', {canvas:'widget-panier', iInfosScenario:infos });
    }

    $(document).ready(function () {
      loadscript('http://gadget.open-system.fr/widgets/osbase.min.js', loadOSPanierScript);

      // Init collapsed to hide it
      $('.collapsed .collapse_box:not(.collapse-processed)').slideUp("slow").addClass('collapse-processed');

      if ($('.collapsable .collapse_title').length > 0) {
        $('.collapsable .collapse_title').click(function () {
          var context = $(this);
          $('.collapse_box', context.parent()).slideToggle("slow");
          context.parent().toggleClass('collapsed');
        });
      }
    });

    // Debug mode : change local images src to www ones.
    if (debug) {
      $('img').each(function () {
        var img = $(this);
        if (img.attr('src').indexOf('http://local.finisteretourisme.com') == 0) {
          img.attr('src', img.attr('src').replace('local.finisteretourisme.com', 'www.finisteretourisme.com'));
        }
      });
    }

    // Asynchronous javascript loading
    function loadscript(sScriptSrc, oCallback) {
      var oHead = document.getElementsByTagName('head')[0];
      var oScript = document.createElement('script');
      oScript.type = 'text/javascript';
      oScript.src = sScriptSrc;
      // most browsers
      oScript.onload = oCallback;
      // IE 6 & 7
      oScript.onreadystatechange = function () {
        if (this.readyState == 'complete') {
          oCallback();
        }
      }
      oHead.appendChild(oScript);
    } // End function loadscript

  } // End Drupal.behaviors.cdt2011

})(jQuery);