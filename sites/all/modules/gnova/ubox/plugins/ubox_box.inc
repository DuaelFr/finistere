<?php
// $Id: ubox_box.inc,v 1.1.2.5 2010/08/04 14:38:02 yhahn Exp $
 
/**
 * Abstract base class defining a box. A ubox content plugin provides a
 * form of options for configuring content and renders content for display.
 *
 * @see ubox_simple.
 */
abstract class ubox_box {
  static $ubox_ubox; // Static cache of box objects.
  public $vid;
 
 	/**
   * Load existing box by ubox database resultset $object.
   */
  public static function load($object, $reset = false) {
    if (!isset(self::$ubox_ubox[$object->vid]) || $reset) {
      
        self::$ubox_ubox[$object->vid] = self::factory($object);
      }
    }
    return isset(self::$ubox_ubox[$object->vid]) ? self::$ubox_ubox[$object->vid] : NULL;
  }
 
  /**
   * Instantiate, populate and return a box object.
   *
   *
   * @param $object
   * database resultset for build box object
   *   
   */
  public static function factory($object) {
    if(!is_object($object)){
    	throw new Exception(t('Cannot build ubox_box factory because $object is not object.'));
    }
    $this->vid = $object->vid;
    /**
		 * On récupère les items et les intègre au contenu de l'ubox
		 */
		  /*$query = "SELECT cfue.field_uboxa_existingcontent_nid
	FROM {content_field_uboxa_existingcontent} cfue 
	WHERE cfue.vid = %n
	ORDER BY cfue.delta ASC";
			while($niditem = db_fetch_object(db_query($query, $this->vid))){
				//$node = node_load($niditem);
				
			}*/
  }
 
  /**
   * Create a new box item.
   */
  protected function __construct() {
  }
 
  /**
   * Reset the ubox cache.
   * 
   * Both ctools and ubox current maintain caches, ctools of the config and
   * ubox of the loaded box objects. We clear them both.
   */
  public static function reset() {
    self::$ubox_ubox = array();
  }
 
  /**
   * Save a box.
   */
  public function save() {
  }
 
  /**
   * Delete a box.
   */
  public function delete() {
    self::reset();
    unset(self::$ubox_ubox[$this->vid]);
  }
 
  /**
   * Render a block. Must return an array with the keys
   * 'delta', 'title', 'subject' (same as title) and 'content'.
   *
   * title AND subject need to be present to avoid that block module overrides
   * title.
   */
  abstract public function render();
}
