<?php

/**
 * @ingroup views_sort_handlers
 */
class views_handler_sort_date_advanced extends views_handler_sort_date {
  function option_definition() {
    $options = parent::option_definition();
    $options['tz_handling'] = array('default' => false);
    return $options;
  }

  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);
    $form['granularity'] = array_merge($form['granularity'], array(
      '#type' => 'select',
      '#multiple' => TRUE,
    ));
    $form['tz_handling'] = array(
      '#type' => 'checkbox',
      '#title' => t('Let Views handle timezone conversion.'),
      '#description' => t('With this unchecked, there will be no timezone conversion at all.'),
      '#default_value' => $this->options['tz_handling'],
    );
  }

  function query() {
    $this->ensure_my_table();
    $type = $this->definition['type'];

    $granularity = $this->options['granularity'];
    $format  = '';
    $format .= ( isset($granularity['year'])   ? 'Y' : '' );
    $format .= ( isset($granularity['month'])  ? 'm' : '' );
    $format .= ( isset($granularity['day'])    ? 'd' : '' );
    $format .= ( isset($granularity['hour'])   ? 'H' : '' );
    $format .= ( isset($granularity['minute']) ? 'i' : '' );
    $format .= ( isset($granularity['second']) ? 's' : '' );

    if ( $format=='YmdHis' || $format=='' ) {
      $this->query->add_orderby($this->table_alias, $this->real_field, $this->options['order']);
    } else {
      // @todo: an option for $offset like strtotime('January 1 UTC') - strtotime('yesterday UTC')
      $offset = ( $this->options['tz_handling'] ? NULL : 0 );
      $formula = views_date_sql_format($format, "$this->table_alias.$this->real_field", $type, $offset);
      $alias = $this->table_alias . '_' . $this->field . '_' . $format . '_' . ( is_null($offset) ? 'defaultoffset' : 'zerooffset' );
      $this->query->add_orderby(NULL, $formula, $this->options['order'], $alias);
    }
  }
}
