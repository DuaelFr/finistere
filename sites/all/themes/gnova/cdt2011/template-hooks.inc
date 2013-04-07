<?php

function cdt2011_menu_tree($tree, $attributes = array('class' => 'menu')) {

  foreach ($attributes as $cle => $val) {
    $attr_string .= ' ' . $cle . '="' . $val . '"';
  }
  return "<ul$attr_string>" . $tree . "</ul>";
}


function cdt2011_menu_item_custom($link, $has_children, $menu = '', $in_active_trail = FALSE, $extra_class = NULL) {
  $class = ($menu ? 'expanded' : ($has_children ? 'collapsed' : 'leaf'));
  if (!empty($extra_class)) {
    $class .= ' ' . $extra_class;
  }
  if ($in_active_trail) {
    $class .= ' active-trail';
  }

  return '<li class="' . $class . '">' . $link . $menu . "</li>\n";
}
