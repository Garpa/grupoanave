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

    $field_vehiculo_serie = isset($node->field_vehiculo_serie) ?
      $node->field_vehiculo_serie['und'][0]['value'] : "";

    //var_dump($field_vehiculo_serie['und'][0]['value']);

    array_push($nodeFields, $field_vehiculo_serie);

    array_push($output, array($node->nid => $nodeFields));

    if ($loop++ == 5) {
      break;
    }
  }

  return var_dump($output);
}
