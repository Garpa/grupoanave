<?php

/**
 * @file
 * Retrieves data from sinister.
 */

/**
 * Returns all of the sinisters assign to an ajustdor user.
 */
function sinister_get_ajustador_sinisters($uid, $type) {
  static $sinisters;
  if (isset($sinisters[$uid][$type])) {
    return $sinisters[$uid][$type];
  }

  $key = 'sinister_get_ajustador_sinisters_' . $uid . '_' . $type;
  if (($cache = cache_get($key))) {
    $sinisters[$uid][$type] = $cache->data;
    return $sinisters[$uid][$type];
  }

  $sql = 'SELECT ajustador.entity_id nid FROM field_data_field_ajustador ajustador
    INNER JOIN field_data_field_status_sinister status ON ajustador.entity_id = status.entity_id
    WHERE ajustador.field_ajustador_target_id = %d AND
    status.field_status_sinister_value = %d';
  $sql = sprintf($sql, $uid, $type);
  $results = db_query($sql);
  $sinisters[$uid][$type] = array();
  while (($row = $results->fetchAssoc())) {
    $sinisters[$uid][$type][$row['nid']] = $row['nid'];
  }

  cache_set($key, $sinisters[$uid][$type], 'cache', strtotime('+1 hour'));
  return $sinisters[$uid][$type];
}

/**
 * Returns sinister folio.
 *
 * @return INT
 *   Returns the Contract Folio.
 */
function sinister_number_folio_get($i = 0) {
  $month_digit = intval(date('n'));
  $months = array(
    0 => 'None',
    1 => 'A',
    2 => 'B',
    3 => 'C',
    4 => 'D',
    5 => 'E',
    6 => 'F',
    7 => 'G',
    8 => 'H',
    9 => 'I',
    10 => 'J',
    11 => 'K',
    12 => 'L',
  );
  $month = $months[$month_digit];
  $year = date('y');
  $sinister_number = (variable_get('sinister_number', 0001) + $i);
  $sinister_number_string = sprintf("%'.05d", $sinister_number);
  $sinister_folio = "{$year}{$month}{$sinister_number_string}";
  return $sinister_folio;
}

/**
 * Increases the Sinister Number by 1.
 */
function sinister_number_increase($i = 0) {
  if (!($sinister_number = variable_get('sinister_number', FALSE))) {
    return FALSE;
  }

  $sinister_number = intval($sinister_number) + 1 + $i;

  variable_set('sinister_number', $sinister_number);
  return TRUE;
}

/**
 * Returns TRUE if a given sinister is found at the database.
 */
function sinister_number_folio_exists($sinister_folio, $nid) {

  if (!empty($nid)) {
    $nid = explode('', $nid);
    $sinister_folio = explode('', $sinister_folio);
    $query = db_query("SELECT nid FROM {nodes} WHERE title = '%s' AND nid != %d" . $sinister_folio, $nid);
    if ($item = $query->fetchArray()) {
      return $item['nid'];
    }
  }

  return FALSE;
}
