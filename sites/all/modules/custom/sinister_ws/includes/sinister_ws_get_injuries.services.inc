<?php

/**
 * @file
 * Retrieve injuries info from nid.
 */

/**
 * Return data from sinister injuries and damages.
 */
function sinister_ws_injuries_resource_retrieve($nid) {
  $node = node_load($nid);
  $count = count($node->field_lesionado[LANGUAGE_NONE]);

  $results = array();

  // Get field collection field_vehiculo item from node.
  for ($i = 0; $i < $count; $i++) {
    $fc_id = $node->field_lesionado[LANGUAGE_NONE][$i]['value'];
    $fc_injuries[$i] = field_collection_item_load($fc_id, $reset = FALSE);
    $results[] = get_injured($fc_injuries[$i], $count, $fc_id);
  }

  return $results;
}

/**
 * Returns array from field_lesionado.
 *
 * @params $fc_injured The id item of field_siniestro_archivo field.
 */
function get_injured($fc_injuries, $count, $fc_id) {
  $injuries = array();
  $injuries['fc_id'] = $fc_id;

  if (!empty($fc_injuries->field_lesionado_nombre[LANGUAGE_NONE][0]['value'])) {
    $injured_name = $fc_injuries->field_lesionado_nombre[LANGUAGE_NONE][0]['value'];
    $injuries['name'] = $injured_name;
  }
  else {
    $injuries['name'] = NULL;
  }

  if (!empty($fc_injuries->field_lesionado_edad[LANGUAGE_NONE][0]['value'])) {
    $injured_age = $fc_injuries->field_lesionado_edad[LANGUAGE_NONE][0]['value'];
    $injuries['age'] = $injured_age;
  }
  else {
    $injuries['age'] = NULL;
  }

  if (!empty($fc_injuries->field_lesionado_domicilio[LANGUAGE_NONE][0]['thoroughfare'])) {
    $injured_thoroughfare = $fc_injuries->field_lesionado_domicilio[LANGUAGE_NONE][0]['thoroughfare'];
    $injuries['thoroughfare'] = $injured_thoroughfare;
  }
  else {
    $injuries['thoroughfare'] = NULL;
  }

  if (!empty($fc_injuries->field_lesionado_domicilio[LANGUAGE_NONE][0]['locality'])) {
    $injured_locality = $fc_injuries->field_lesionado_domicilio[LANGUAGE_NONE][0]['locality'];
    $injuries['locality'] = $injured_locality;
  }
  else {
    $injuries['locality'] = NULL;
  }

  if (!empty($fc_injuries->field_lesionado_domicilio[LANGUAGE_NONE][0]['premise'])) {
    $injured_premise = $fc_injuries->field_lesionado_domicilio[LANGUAGE_NONE][0]['premise'];
    $injuries['premise'] = $injured_premise;
  }
  else {
    $injuries['premise'] = NULL;
  }

  if (!empty($fc_injuries->field_lesionado_domicilio[LANGUAGE_NONE][0]['administrative_area'])) {
    // Get administrative area field value.
    $key_admin_area = $fc_injuries->field_lesionado_domicilio[LANGUAGE_NONE][0]['administrative_area'];
    $injuries['administrative_area'] = $key_admin_area;
  }
  else {
    $injuries['administrative_area'] = NULL;
  }

  if (!empty($fc_injuries->field_lesionado_domicilio[LANGUAGE_NONE][0]['postal_code'])) {
    $injured_postal_code = $fc_injuries->field_lesionado_domicilio[LANGUAGE_NONE][0]['postal_code'];
    $injuries['postal_code'] = $injured_postal_code;
  }
  else {
    $injuries['postal_code'] = NULL;
  }

  if (!empty($fc_injuries->field_lesionado_telefono[LANGUAGE_NONE][0]['value'])) {
    $injured_phone = $fc_injuries->field_lesionado_telefono[LANGUAGE_NONE][0]['value'];
    $injuries['phone'] = $injured_phone;
  }
  else {
    $injuries['phone'] = NULL;
  }

  if (isset($fc_injuries->field_lesionado_riesgo_b[LANGUAGE_NONE][0]['value'])) {
    $injured_risk_b = $fc_injuries->field_lesionado_riesgo_b[LANGUAGE_NONE][0]['value'];
    $injuries['risk_b'] = $injured_risk_b;
  }
  else {
    $injuries['risk_b'] = NULL;
  }

  // Get info field_lesionado_riesgo_b.
  $field_risk_b = field_info_field('field_lesionado_riesgo_b');
  $allowed_values_risk_b = list_allowed_values($field_risk_b);
  // Add all allowed values.
  $injuries['risk_b_options'] = $allowed_values_risk_b;

  if (!empty($fc_injuries->field_lesionado_lesiones[LANGUAGE_NONE][0]['value'])) {
    $injured_injuries = $fc_injuries->field_lesionado_lesiones[LANGUAGE_NONE][0]['value'];
    $injuries['injuries'] = $injured_injuries;
  }
  else {
    $injuries['injuries'] = NULL;
  }

  if (!empty($fc_injuries->field_lesionado_ambulancia[LANGUAGE_NONE][0]['value'])) {
    $injured_ambulance = $fc_injuries->field_lesionado_ambulancia[LANGUAGE_NONE][0]['value'];
    $injuries['ambulance'] = $injured_ambulance;
  }
  else {
    $injuries['ambulance'] = '0';
  }

  if (!empty($fc_injuries->field_lesionado_ambulancia_info[LANGUAGE_NONE][0]['value'])) {
    $injured_ambulance_info = $fc_injuries->field_lesionado_ambulancia_info[LANGUAGE_NONE][0]['value'];
    $injuries['ambulance_description'] = $injured_ambulance_info;
  }
  else {
    $injuries['ambulance_description'] = NULL;
  }

  if (!empty($fc_injuries->field_hospital[LANGUAGE_NONE][0]['target_id'])) {
    // Get target id from hispital user role.
    $hospital_tid = $fc_injuries->field_hospital[LANGUAGE_NONE][0]['target_id'];
    $injuries['hospital'] = $hospital_tid;
  }
  else {
    $injuries['hospital'] = NULL;
  }

  return $injuries;
}
