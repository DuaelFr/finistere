<?php
// $Id: ubox_box.inc,v 1.1.2.5 2010/08/04 14:38:02 yhahn Exp $
 
/**
 * Abstract base class defining a box. A ubox content plugin provides a
 * form of options for configuring content and renders content for display.
 *
 * @see ubox_simple.
 */
abstract class ubox_area_box {
  static $ubox_area; // Static cache of box objects.
  public $delta;
  public $title;
  public $description;
  public $options;
  public $plugin_key;
  public $new;
  public $export_type;
 
  /**
   * Load existing box by its unique identifier $delta.
   */
  public static function load($delta, $reset = false) {
    if (!isset(self::$ubox_area[$delta]) || $reset) {
      
      ctools_include('export');
      $box = ctools_export_load_object('ubox_area', 'names', array($delta));
      if (!empty($box) && $values = array_pop($box)) {
        self::$ubox_area[$delta] = self::factory($values->plugin_key, $values);
        self::$ubox_area[$delta]->new = false;
      }
    }
    return isset(self::$ubox_area[$delta]) ? self::$ubox_area[$delta] : NULL;
  }
 
  /**
   * Instantiate, populate and return a box object.
   *
   * @param $plugin_key
   *
   * @param $values
   *   An array with at least a plugin_key key identifying the plugin class to
   *   use for instantiating this box.
   */
  public static function factory($plugin_key, $values) {
    ctools_include('plugins');
    if ($class = ctools_plugin_load_class('ubox', 'plugins', $plugin_key, 'handler')) {

      // While we actually prefer to get objects, we need to allow for either,
      // so we convert it all to arrays.
      if (is_object($values)) {
        $values = (array)$values;
      }

      $box = new $class();
      $box->plugin_key = $plugin_key;

      foreach ($box as $key => $value) {
        if (isset($values[$key])) {
          $box->$key = $values[$key];
        }
      }
      foreach ($box->options_defaults() as $key => $value) {
        if (isset($values[$key])) {
          $box->options[$key] = $values[$key];
        }
      }
      return $box;
    }
    return false;
  }
 
  /**
   * Create a new box.
   */
  protected function __construct() {
    $this->new = TRUE; // A box is new unless it exists in the DB or in code.
    $this->options = $this->options_defaults();
  }
 
  /**
   * Reset the ubox cache.
   * 
   * Both ctools and ubox current maintain caches, ctools of the config and
   * ubox of the loaded box objects. We clear them both.
   */
  public static function reset() {
    ctools_include('export');
    ctools_export_load_object_reset('ubox');
    self::$ubox_area = array();
  }
 
  /**
   * Save a box.
   */
  public function save() {
    if (empty($this->delta)) {
      throw new Exception(t('Cannot save box without a specified delta.'));
    }
    self::reset();
    $existing = ubox_area_load($this->delta);
    if ($existing && ($existing->export_type & EXPORT_IN_DATABASE)) {
      drupal_write_record('ubox_area', $this, array('delta'));
    }
    else {
      drupal_write_record('ubox_area', $this);
    }
    $this->new = FALSE;
    self::reset();
  }
 
  /**
   * Delete a box.
   */
  public function delete() {
    self::reset();
    unset(self::$ubox_area[$this->delta]);
    db_query("DELETE FROM {ubox_area} WHERE delta = '%s'", $this->delta);
  }
 
  /**
   * Declare default options.
   */
  abstract public function options_defaults();
 
  /**
   * Provide options to configure content.
   */
  abstract public function options_form();
 
  /**
   * Render a block. Must return an array with the keys
   * 'delta', 'title', 'subject' (same as title) and 'content'.
   *
   * title AND subject need to be present to avoid that block module overrides
   * title.
   */
  abstract public function render();
}
