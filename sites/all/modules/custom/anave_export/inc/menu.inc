<?php

/**
 * @file
 * This file has all functionality related to menu pages.
 */

/**
 * Implements hook_menu().
 */
function anave_export_menu() {
  $items = array();

  $items['admin/export'] = array(
    'title' => 'Administración Global',
    'page callback' => 'anave_export_get_nodes',
    'access arguments' => array('access content'),
    'type' => MENU_CALLBACK,
  );

  return $items;
}

/**
 * Export Main Page.
 */
function anave_export_get_nodes() {
  drupal_set_title('Export Nodes');
  // Links.
  $output = array();
  $nodes = node_load_multiple(array(), array('type' => 'poliza'));

  $loop = 0;
  foreach ($nodes as $key => $node) {
    $nodeFields = array();

    require 'scripmenu1.inc';
    require 'scripmenu2.inc';
    require 'scripmenu3.inc';

    if ($loop++ == 5) {
      break;
    }
  }

  // Text output
  return theme('export-page', array('nodes' => $output));
  //return var_dump($output);
}
