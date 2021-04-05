<?php

/**
 * @file
 * This files implements hook_theme().
 */

/**
 * Implements hook_theme().
 */
function anave_export_theme() {
  return array(
    'export-page' => array(
      'arguments' => array(
        'sections' => NULL,
      ),
      'template' => 'templates/export-page',
    ),
    'menu' => array(
      'arguments' => array(
        'sections' => NULL,
      ),
      'menu' => 'inc/menu',
    ),
  );
}
