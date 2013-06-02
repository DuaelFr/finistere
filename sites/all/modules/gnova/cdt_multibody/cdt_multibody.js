;(function($, Drupal, window, document, undefined) {
  var Tabs = window.Tabs || {};

  Tabs.refresh = function() {
    $('.tab-content', Tabs.parent).hide();
    $('.tab-content.active', Tabs.parent).show();
  };

  Tabs.init = function() {
    Tabs.parent = $('.cdt-multibody-tabs');

    $('.tab-title', Tabs.parent).click(function() {
      $('.tab-content.active', Tabs.parent).removeClass('active');
      $('.tab-title.active', Tabs.parent).removeClass('active');

      $(this).addClass('active');
      $('#' + $(this).attr('id').replace('title', 'content')).addClass('active');

      Tabs.refresh();
    });

    Tabs.refresh();
  };
  $(document).ready(Tabs.init);
})(jQuery, Drupal, window, document);