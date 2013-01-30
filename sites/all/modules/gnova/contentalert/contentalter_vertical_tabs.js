// $Id: scheduler_vertical_tabs.js,v 1.1.2.2 2010/01/17 16:24:33 ericschaefer Exp $

Drupal.verticalTabs = Drupal.verticalTabs || {};

Drupal.verticalTabs.contentalert_settings = function() {
  var vals = [];
  if ($('#edit-contentalert-datetime-tosend').val() || $('#edit-contentalert-datetime-tosend-datepicker-popup-0').val()) {
	  vals.push(Drupal.t('Date to alert'));
  }
  if (!vals.length) {
    vals.push(Drupal.t('No date'));
  }
  return vals.join(', ');
}
