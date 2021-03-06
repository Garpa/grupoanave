<?php

/**
 * @file
 * Retrieve file info from nid.
 */

/**
 * Return file data from sinister.
 */
function sinister_ws_files_resource_retrieve($nid) {
  $node = node_load($nid);
  $count = count($node->field_siniestro_archivo[LANGUAGE_NONE]);

  $results = array();

  // Get field collection field_siniestro_archivo item from node.
  for ($i = 0; $i < $count; $i++) {
    $fc_archivo[$i] = field_collection_item_load($node->field_siniestro_archivo[LANGUAGE_NONE][$i]['value'], $reset = FALSE);
    $results[] = get_files($fc_archivo[$i]);
  }

  return $results;
}

/**
 * Returns value from field_siniestros_archivo.
 */
function get_files($fc_archivo) {
  $percent = 0;

  if (!empty($fc_archivo->field_visualizador)) {
    // Get value from field_visualizador.
    $field_image = $fc_archivo->field_visualizador;
    // Get number of images from field_visualizador.
    $imgsNum = count($field_image[LANGUAGE_NONE]);
  }
  else {
    $imgsNum = 0;
  }

  if (!empty($fc_archivo->field_documentos)) {
    // Get value from field_documentos.
    $field_document = $fc_archivo->field_documentos;
    // Get number of documents from field_documentos.
    $docsNum = count($field_document[LANGUAGE_NONE]);
  }
  else {
    $docsNum = 0;
  }

  $files = array();

  if (!empty($fc_archivo->field_fecha[LANGUAGE_NONE][0]['value'])) {
    $date = $fc_archivo->field_fecha[LANGUAGE_NONE][0]['value'];
    $files['date'] = date('Y/m/d h:i a', $date);
  }

  if (!empty($fc_archivo->field_archivo_comentario[LANGUAGE_NONE][0]['value'])) {
    $comment_files = $fc_archivo->field_archivo_comentario[LANGUAGE_NONE][0]['value'];
    $files['comment'] = $comment_files;
  }

  for ($i = 0; $i < $imgsNum; $i++) {

    $j = $i + 1;

    if (!empty($field_image[LANGUAGE_NONE][$i]['uri'])) {
      $uri = $field_image[LANGUAGE_NONE][$i]['uri'];
      $path = file_create_url($uri);
      $files["images"][$i]['url'] = $path;
      $percent = 1.538461538461538;
    }

    if (!empty($field_image[LANGUAGE_NONE][$i]['metadata']['width'])) {
      $width = $field_image[LANGUAGE_NONE][$i]['metadata']['width'];
      $images["images"][$i]['width'] = $width;
    }

    if (!empty($field_image[LANGUAGE_NONE][$i]['metadata']['height'])) {
      $height = $field_image[LANGUAGE_NONE][$i]['metadata']['height'];
      $files["images"][$i]['height'] = $height;
    }

    if (!empty($field_image[LANGUAGE_NONE][$i]['filename'])) {
      $filename = $field_image[LANGUAGE_NONE][$i]['filename'];
      $files["images"][$i]['filename'] = $filename;
    }

  }

  for ($i = 0; $i < $docsNum; $i++) {

    $j = $i + 1;

    if (!empty($field_document[LANGUAGE_NONE][$i]['filename'])) {
      $filename = $field_document[LANGUAGE_NONE][$i]['filename'];
      $files["documents"][$i]['filename'] = $filename;
      $percent = 1.538461538461538;
    }

  }

  $files['percent'] = $percent;
  return $files;
}
