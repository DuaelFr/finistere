(function ($) {
  $.fn.diaporama = function (options) {
    var defaults = {
      delay:         3,
      animationSpeed:"normal",
      controls:      true
    };
    var options = $.extend(defaults, options);

    // Affiche l'élément suivant
    var goTo = function(obj, i, options) {
      if ($(".titre_slide:hidden")) {
        $(".titre_slide").fadeIn("slow");
      }

      $(obj).find(".titre_slide").fadeOut(3000);

      $(obj).find("li.active").fadeOut(options.animationSpeed);

      $(obj).find("li.active").removeClass("active");
      $(obj).find("li").get(i).addClass("active");
      $(obj).find("li.active").fadeIn(options.animationSpeed);
    };

    // Affiche l'élément suivant
    var nextElt = function(obj, options) {
      if ($(".titre_slide:hidden")) {
        $(".titre_slide").fadeIn("slow");
      }

      $(obj).find(".titre_slide").fadeOut(3000);

      $(obj).find("li.active").fadeOut(options.animationSpeed);

      if (!$(obj).find("li.active").is(":last-child")) {
        $(obj).find("li.active").next().addClass("active").prev().removeClass("active");
        $(obj).find("li.active").fadeIn(options.animationSpeed);
      }
      else {
        $(obj).find("li:first-child").addClass("active").fadeIn(options.animationSpeed);
        $(obj).find("li:last-child").removeClass("active");
      }
    };

    // Affiche l'élément précédent
    var prevElt = function(obj, options) {
      $(obj).find("li.active").fadeOut(options.animationSpeed);
      if (!$(obj).find("li.active").is(":first-child")) {
        $(obj).find("li.active").prev().addClass("active").next().removeClass("active");
        $(obj).find("li.active").fadeIn(options.animationSpeed);
      }
      else {
        $(obj).find("li:last-child").addClass("active").fadeIn(options.animationSpeed);
        $(obj).find("li:first-child").removeClass("active");
      }
    };

    this.each(function () {
      var obj = $(this);
      if ($(obj).find("li").length > 1) {
        var inter = setInterval(function () {
          nextElt(obj, options);
        }, (options.delay * 1000));
        var sens = "right";
        var pause = false;
        $(obj).find("li").hide();
        $(obj).find("li:first-child").addClass("active").fadeIn(options.animationSpeed);

        // Controls
        if (options.controls) {
          $(obj).after("<div class='diaporama_controls'><div class='btns'><a href='#' class='prev'>Prec.</a> <a href='#' class='pause'>Pause</a> <a href='#' class='next'>Suiv.</a></div></div>");
          $(obj).siblings().find(".prev").click(function (evt) {
            evt.preventDefault();
            clearInterval(inter);
            prevElt(obj, options);
            if (!pause) {
              inter = setInterval(function () {
                prevElt(obj, options)
              }, (options.delay * 1000));
            }
            sens = "left";
          });
          $(obj).siblings().find(".next").click(function (evt) {
            evt.preventDefault();
            clearInterval(inter);
            nextElt(obj, options);
            if (!pause) {
              inter = setInterval(function () {
                nextElt(obj, options)
              }, (options.delay * 1000));
            }
            sens = "right";
          });
          $(obj).siblings().find(".pause").toggle(
            function (evt) {
              evt.preventDefault();
              $(this).removeClass("pause").addClass("play");
              clearInterval(inter);
              pause = true;
            },
            function (evt) {
              evt.preventDefault();
              $(this).removeClass("play").addClass("pause");
              inter = setInterval(function () {
                (sens == "right") ? nextElt(obj, options) : prevElt(obj, options)
              }, (options.delay * 1000));
              pause = false;
            }
          );
        }
      }
    });

    return this;
  };
})(jQuery);