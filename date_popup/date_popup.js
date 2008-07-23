// $Id$

/**
 * Attaches the calendar behavior to all required fields
 */
Drupal.behaviors.date_popup = function (context) {
  for (var id in Drupal.settings.datePopup) {
    $('#'+ id).bind('focus', Drupal.settings.datePopup[id], function(e) {
      if (!$(this).hasClass('date-popup-init')) {
        var datePopup = e.data;
        // Explicitely filter the methods we accept.
        switch (datePopup.func) {
          case 'calendar':
            if (datePopup.settings.fromTo) {
              // TODO : unsure what the id's for 'From' and 'To' are actually supposed to be
              // datePopup.settings.minDate = (this.id == 'dTo' ? getDate($('#dFrom').val()) : null);
              // datePopup.settings.maxDate = (this.id == 'dFrom' ? getDate($('#dTo').val()) : null);
            }
            $(this)
              .calendar(datePopup.settings)
              .addClass('date-popup-init')
              .focus();
            break;

          case 'timeEntry':
            if (datePopup.settings.fromTo) {
              // TODO : unsure what the id's for 'From' and 'To' are actually supposed to be
              // datePopup.settings.minTime = (this.id == 'tTo' ? getDate($('#tFrom').val()) : null);
              // datePopup.settings.maxDate = (this.id == 'tFrom' ? getDate($('#tTo').val()) : null);
            }
            $(this)
              .timeEntry(datePopup.settings)
              .addClass('date-popup-init')
              .focus();
            break;
        }
      }
    });
  }
};
