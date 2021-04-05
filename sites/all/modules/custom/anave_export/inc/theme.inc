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
    'export-page-section' => array(
      'arguments' => array(
        'id' => NULL,
        'title' => NULL,
        'description' => NULL,
      ),
      'template' => 'templates/export-page-section',
    ),
  );
}
