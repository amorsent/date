<?php
/**
 * @file
 * Views navigation style plugin for Date API.
 */

/**
 * Style plugin to create date back/next navigation.
 * 
 * The style plugin passes some argument values to the theme, and
 * ensures that the date argument is present and that the default
 * value is set to the current date.
 */
class date_navigation_plugin_style extends views_plugin_style {

  /**
   * Style validation.
   */
  function validate() {
    $errors = parent::validate();

    $arguments = $this->display->handler->get_option('arguments');
    $count = 0;
    $found = FALSE;
    foreach ($arguments as $id => $argument) {
      if ($argument['field'] == 'date_argument') {
        if ($count > 0) {
          $errors[] = t('The %style cannot use more than one Date: Date argument.', array('%style' => $this->definition['title']));          
        }
        elseif ($argument['default_argument_type'] != 'date') {
          $errors[] = t('The %style requires the Date: Date argument be set to default to the current date.', array('%style' => $this->definition['title']));      
        }
        $count++;
        $found = TRUE;
      }
    }
    if (!$found) {
      $errors[] = t('The %style requires the Date: Date argument.', array('%style' => $this->definition['title']));      
    }
    return $errors;
  }

  function query() {
    
    //$this->view->query->clear_fields();

    // Bring the argument information into the view so our theme can access it.
    $i = 0;    
    foreach ($this->view->argument as $id => $argument) {
      // The instanceof function makes this work for any handler that was derived 
      // from date_views_argument_handler_simple, including date_views_argument_handler.
      if ($argument instanceof date_views_argument_handler_simple) {
        $this->view->date_info->granularity = $argument->granularity;
        $this->view->date_info->date_arg = $argument->argument;
        $this->view->date_info->date_arg_pos = $i;
        $this->view->date_info->year = date_format($argument->date_range[0], 'Y');
        $this->view->date_info->month = date_format($argument->date_range[0], 'n');;
        $this->view->date_info->day = date_format($argument->date_range[0], 'j');
        $this->view->date_info->week = date_week(date_format($argument->date_range[0], DATE_FORMAT_DATE));
        $this->view->date_info->date_range = $argument->date_range;
        $this->view->date_info->limit = $argument->limit;
        $this->view->date_info->url = $this->view->get_url();
      }
      $i++;
    }
  }
}