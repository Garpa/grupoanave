<?php

/**
 * @file
 * delete all Drush command
 */

/**
 * Implementation of hook_drush_command().
 */
function contract_export_drush_command() {
  $items = array();
  $items['export-contracts'] = [
    'callback' => 'contract_export_export',
    'description' => 'Export all contract nodes',
    'arguments' => [
       'export_file' => 'the output file name.',
       'year' => 'the site year for files.'
     ],
    'aliases' => ['ce_export'],
  ];
  return $items;
}

/**
 * Drush callback to delete content
 */
function contract_export_export($export_file = NULL, $year = NULL) {
  if ($export_file) {
    $export_file = DRUPAL_ROOT . "/dumps/" . $export_file;
  }
  else {
    $export_file = DRUPAL_ROOT . "/dumps/export.txt";
  }

  $file = fopen($export_file, "w");
  fwrite($file, '');
  fclose($file);
  $results = [];
  $limit = 50;
  $start = 0;

  // Users.
  do {
    $is_more = FALSE;
    $results = [];

    $query = db_select('users', 'n');
    $query->fields('n', array('uid'))
      ->range($start, $limit);
    $results = $query->execute()->fetchAll();

    $file = fopen($export_file, "a");
    foreach ($results as $result) {
      if ($result->uid == 0) {
        continue;
      }

      $user = user_load($result->uid, TRUE);
      $line = contract_export_export_get_user($user);
      fwrite($file, $line.PHP_EOL);
    }
    fclose($file);

    if (count($results) == $limit) {
      $is_more = TRUE;
      $start = $start + $limit;
      drush_print('Added ' . ($start) . ' users');
    }
    else {
      drush_print('Added ' . ($start + count($results)) . ' users');
    }

  } while ($is_more);

  $start = 0;

  // Contracts and payments.
  do {
    $is_more = FALSE;
    $results = [];

    $query = db_select('node', 'n');
    $query->fields('n', array('nid'))
      ->range($start, $limit)
      ->condition('n.type', 'poliza');
    $results = $query->execute()->fetchAll();

    $file = fopen($export_file, "a");
    foreach ($results as $result) {

      $node = node_load($result->nid, NULL, TRUE);
      $line = contract_export_export_get_contract($node, $year);
      fwrite($file, $line.PHP_EOL);
    }
    fclose($file);

    if (count($results) == $limit) {
      $is_more = TRUE;
      $start = $start + $limit;
      drush_print('Added ' . ($start) . ' contracts');
    }
    else {
      drush_print('Added ' . ($start + count($results)) . ' contracts');
    }

  } while ($is_more);

  $start = 0;

  // Sinisters.
  do {
    $is_more = FALSE;
    $results = [];

    $query = db_select('node', 'n');
    $query->fields('n', array('nid'))
      ->range($start, $limit)
      ->condition('n.type', 'siniestro');
    $results = $query->execute()->fetchAll();

    $file = fopen($export_file, "a");
    foreach ($results as $result) {
      $node = node_load($result->nid, NULL, TRUE);
      $line = contract_export_export_get_sinisters($node, $year);
      fwrite($file, $line.PHP_EOL);
    }
    fclose($file);

    if (count($results) == $limit) {
      $is_more = TRUE;
      $start = $start + $limit;
      drush_print('Added ' . ($start) . ' sinisters');
    }
    else {
      drush_print('Added ' . ($start + count($results)) . ' sinisters');
    }

  } while ($is_more);
}

function contract_export_export_get_user($user) {
  $data['type'] = 'user';
  $data['name'] = ($user->name ?? '');
  $data['mail'] = ($user->mail ?? '');
  $data['status'] = ($user->status ?? '');
  $data['created'] = ($user->created ?? '');
  $data['changed'] = ($user->changed ?? '');
  $data['uid'] = ($user->uid ?? '');

  // Text Fields.
  if ($user->field_agente_clave) {
    $data['field_agente_clave'] = contract_export_export_get_field_value($user->field_agente_clave, 'text');
  }

  if ($user->field_first_name) {
    $data['field_first_name'] = contract_export_export_get_field_value($user->field_first_name, 'text');
  }

  if ($user->field_last_name) {
    $data['field_last_name'] = contract_export_export_get_field_value($user->field_last_name, 'text');
  }

  if ($user->field_telefono_oficina) {
    $data['field_telefono_oficina'] = contract_export_export_get_field_value($user->field_telefono_oficina, 'text');
  }

  if ($user->field_telefono_movil) {
    $data['field_telefono_movil'] = contract_export_export_get_field_value($user->field_telefono_movil, 'text');
  }

  if ($user->field_poblacion_multiple) {
    $data['field_poblacion_multiple'] = contract_export_export_get_field_value($user->field_poblacion_multiple, 'text');
  }
  // Text Fields End.

  // Term Reference Fields.
  if ($user->field_estado) {
    $data['field_estado'] = contract_export_export_get_field_value($user->field_estado, 'term');
  }
  // Term Reference Fields End.

  // Roles.
  if ($user->roles) {
    foreach ($user->roles as $role) {
      $data['roles'][] = $role;
    }
  }
  // Roles End.

  // Address Field.
  if ($user->field_domicilio) {
    $data['field_domicilio'] = contract_export_export_get_field_value($user->field_domicilio, 'address');
  }
  // Address Field End.

  return json_encode($data);
}

/**
 * Helper function to get all contract data.
 */
function contract_export_export_get_contract($node, $year) {
  $data = [];
  $author = user_load($node->uid, TRUE);
  $data = [
    'type' => 'contract',
    'title' => ($node->title ?? ''),
    'author' => $author->name,
    'site' => variable_get('site_name'),
    'year' => $year,
    'id' => $node->nid,
    'status' => $node->status,
  ];

  +"revision_uid": "194"

  if ($node->revision_uid) {
    $data['revision_uid'] = $node->revision_uid;
  }

  if ($node->created) {
    $data['changed'] = $node->changed;
  }

  // Text Fields.
  if ($node->field_asegurado_benef_pref) {
    $data['field_asegurado_benef_pref'] = contract_export_export_get_field_value($node->field_asegurado_benef_pref, 'text');
  }

  if ($node->field_asegurado_io) {
    $data['field_asegurado_io'] = contract_export_export_get_field_value($node->field_asegurado_io, 'text');
  }

  if ($node->field_asegurado_nombre) {
    $data['field_asegurado_nombre'] = contract_export_export_get_field_value($node->field_asegurado_nombre, 'text');
  }

  if ($node->field_asegurado_rfc) {
    $data['field_asegurado_rfc'] = contract_export_export_get_field_value($node->field_asegurado_rfc, 'text');
  }

  if ($node->field_asegurado_telefono) {
    $data['field_asegurado_telefono'] = contract_export_export_get_field_value($node->field_asegurado_telefono, 'text');
  }

  if ($node->field_poliza_moneda) {
    $data['field_poliza_moneda'] = contract_export_export_get_field_value($node->field_poliza_moneda, 'text');
  }

  if ($node->field_poliza_oficina) {
    $data['field_poliza_oficina'] = contract_export_export_get_field_value($node->field_poliza_oficina, 'text');
  }

  if ($node->field_vehiculo_capacidad) {
    $data['field_vehiculo_capacidad'] = contract_export_export_get_field_value($node->field_vehiculo_capacidad, 'text');
  }

  if ($node->field_vehiculo_carroceria) {
    $data['field_vehiculo_carroceria'] = contract_export_export_get_field_value($node->field_vehiculo_carroceria, 'text');
  }

  if ($node->field_vehiculo_categoria) {
    $data['field_vehiculo_categoria'] = contract_export_export_get_field_value($node->field_vehiculo_categoria, 'text');
  }

  if ($node->field_vehiculo_cilindros) {
    $data['field_vehiculo_cilindros'] = contract_export_export_get_field_value($node->field_vehiculo_cilindros, 'text');
  }

  if ($node->field_vehiculo_clave_sbg) {
    $data['field_vehiculo_clave_sbg'] = contract_export_export_get_field_value($node->field_vehiculo_clave_sbg, 'text');
  }

  if ($node->field_vehiculo_color) {
    $data['field_vehiculo_color'] = contract_export_export_get_field_value($node->field_vehiculo_color, 'text');
  }

  if ($node->field_vehiculo_descripcion_carga) {
    $data['field_vehiculo_descripcion_carga'] = contract_export_export_get_field_value($node->field_vehiculo_descripcion_carga, 'text');
  }

  if ($node->field_vehiculo_motor) {
    $data['field_vehiculo_motor'] = contract_export_export_get_field_value($node->field_vehiculo_motor, 'text');
  }

  if ($node->field_vehiculo_placas) {
    $data['field_vehiculo_placas'] = contract_export_export_get_field_value($node->field_vehiculo_placas, 'text');
  }

  if ($node->field_vehiculo_referencia) {
    $data['field_vehiculo_referencia'] = contract_export_export_get_field_value($node->field_vehiculo_referencia, 'text');
  }

  if ($node->field_vehiculo_remolque) {
    $data['field_vehiculo_remolque'] = contract_export_export_get_field_value($node->field_vehiculo_remolque, 'text');
  }

  if ($node->field_vehiculo_serie) {
    $data['field_vehiculo_serie'] = contract_export_export_get_field_value($node->field_vehiculo_serie, 'text');
  }

  if ($node->field_vehiculo_tipo_carga) {
    $data['field_vehiculo_tipo_carga'] = contract_export_export_get_field_value($node->field_vehiculo_tipo_carga, 'text');
  }

  if ($node->field_vehiculo_tipo_remolque) {
    $data['field_vehiculo_tipo_remolque'] = contract_export_export_get_field_value($node->field_vehiculo_tipo_remolque, 'text');
  }

  if ($node->field_vehiculo_transmision) {
    $data['field_vehiculo_transmision'] = contract_export_export_get_field_value($node->field_vehiculo_transmision, 'text');
  }

  if ($node->field_vehiculo_uso) {
    $data['field_vehiculo_uso'] = contract_export_export_get_field_value($node->field_vehiculo_uso, 'text');
  }
  // Text Fields End.

  // Number Fields.
  if ($node->field_vehiculo_modelo) {
    $data['field_vehiculo_modelo'] = contract_export_export_get_field_value($node->field_vehiculo_modelo, 'number');
  }

  if ($node->field_vehiculo_numero_inventario) {
    $data['field_vehiculo_numero_inventario'] = contract_export_export_get_field_value($node->field_vehiculo_numero_inventario, 'number');
  }

  if ($node->field_vehiculo_numero_pedimento) {
    $data['field_vehiculo_numero_pedimento'] = contract_export_export_get_field_value($node->field_vehiculo_numero_pedimento, 'number');
  }

  if ($node->field_vehiculo_tonelaje) {
    $data['field_vehiculo_tonelaje'] = contract_export_export_get_field_value($node->field_vehiculo_tonelaje, 'number');
  }

  if ($node->field_pago_fraccionado) {
    $data['field_pago_fraccionado'] = contract_export_export_get_field_value($node->field_pago_fraccionado, 'number');
  }

  if ($node->field_poliza_derecho_poliza) {
    $data['field_poliza_derecho_poliza'] = contract_export_export_get_field_value($node->field_poliza_derecho_poliza, 'number');
  }

  if ($node->field_poliza_impuesto_iva) {
    $data['field_poliza_impuesto_iva'] = contract_export_export_get_field_value($node->field_poliza_impuesto_iva, 'number');
  }

  if ($node->field_poliza_prima_1er_recibo) {
    $data['field_poliza_prima_1er_recibo'] = contract_export_export_get_field_value($node->field_poliza_prima_1er_recibo, 'number');
  }

  if ($node->field_poliza_prima_neta) {
    $data['field_poliza_prima_neta'] = contract_export_export_get_field_value($node->field_poliza_prima_neta, 'number');
  }

  if ($node->field_poliza_prima_total) {
    $data['field_poliza_prima_total'] = contract_export_export_get_field_value($node->field_poliza_prima_total, 'number');
  }

  if ($node->field_poliza_primas_recibos_subs) {
    $data['field_poliza_primas_recibos_subs'] = contract_export_export_get_field_value($node->field_poliza_primas_recibos_subs, 'number');
  }

  if ($node->field_poliza_reduccion) {
    $data['field_poliza_reduccion'] = contract_export_export_get_field_value($node->field_poliza_reduccion, 'number');
  }

  if ($node->field_poliza_rgo_pago_fracc) {
    $data['field_poliza_rgo_pago_fracc'] = contract_export_export_get_field_value($node->field_poliza_rgo_pago_fracc, 'number');
  }
  // Number Fields End.

  // Date Fields.
  if ($node->field_fecha_de_cancelacion) {
    $data['field_fecha_de_cancelacion'] = contract_export_export_get_field_value($node->field_fecha_de_cancelacion, 'date');
  }

  if ($node->field_fecha_de_pagado) {
    $data['field_fecha_de_pagado'] = contract_export_export_get_field_value($node->field_fecha_de_pagado, 'date');
  }

  if ($node->field_poliza_emision) {
    $data['field_poliza_emision'] = contract_export_export_get_field_value($node->field_poliza_emision, 'date');
  }

  if ($node->field_poliza_vigencia) {
    $data['field_poliza_vigencia'] = contract_export_export_get_field_value($node->field_poliza_vigencia, 'date');
  }
  // Date Fields End.

  // List Fields.
  if ($node->field_derecho_de_poliza2) {
    $data['field_derecho_de_poliza2'] = contract_export_export_get_field_value($node->field_derecho_de_poliza2, 'list', 'field_derecho_de_poliza2');
  }

  if ($node->field_periodo_de_gracia) {
    $data['field_periodo_de_gracia'] = contract_export_export_get_field_value($node->field_periodo_de_gracia, 'list', 'field_periodo_de_gracia');
  }

  if ($node->field_poliza_forma_pago) {
    $data['field_poliza_forma_pago'] = contract_export_export_get_field_value($node->field_poliza_forma_pago, 'list', 'field_poliza_forma_pago');
  }

  if ($node->field_poliza_status) {
    $data['field_poliza_status'] = contract_export_export_get_field_value($node->field_poliza_status, 'list', 'field_poliza_status');
  }

  if ($node->field_uso_vehiculo) {
    $data['field_uso_vehiculo'] = contract_export_export_get_field_value($node->field_uso_vehiculo, 'list', 'field_uso_vehiculo');
  }

  if ($node->field_vehiculo_servicio) {
    $data['field_vehiculo_servicio'] = contract_export_export_get_field_value($node->field_vehiculo_servicio, 'list', 'field_vehiculo_servicio');
  }
  // List Fields End.

  // Term Reference Fields.
  if ($node->field_motivos_de_cancelacion) {
    $data['field_motivos_de_cancelacion'] = contract_export_export_get_field_value($node->field_motivos_de_cancelacion, 'term');
  }

  if ($node->field_plz_vehiculo_marca) {
    $data['field_plz_vehiculo_marca'] = contract_export_export_get_field_value($node->field_plz_vehiculo_marca, 'term');
  }

  if ($node->field_vehiculo_carroceria_select) {
    $data['field_vehiculo_carroceria_select'] = contract_export_export_get_field_value($node->field_vehiculo_carroceria_select, 'term');
  }

  if ($node->field_vehiculo_descripcion) {
    $data['field_vehiculo_descripcion'] = contract_export_export_get_field_value($node->field_vehiculo_descripcion, 'term');
  }

  if ($node->field_vehiculo_submarca) {
    $data['field_vehiculo_submarca'] = contract_export_export_get_field_value($node->field_vehiculo_submarca, 'term');
  }
  // Term Reference Fields End.

  // User Reference Fields.
  if ($node->field_asignar_promotor) {
    $data['field_asignar_promotor'] = contract_export_export_get_field_value($node->field_asignar_promotor, 'user');
  }

  if ($node->field_usuario_de_cancelado) {
    $data['field_usuario_de_cancelado'] = contract_export_export_get_field_value($node->field_usuario_de_cancelado, 'user');
  }

  if ($node->field_usuario_de_pagado) {
    $data['field_usuario_de_pagado'] = contract_export_export_get_field_value($node->field_usuario_de_pagado, 'user');
  }
  // User Reference Fields End.

  if ($node->field_asegurado_domicilio) {
    $data['field_asegurado_domicilio'] = contract_export_export_get_field_value($node->field_asegurado_domicilio, 'address');
  }


  if ($node->field_ficha_de_pago) {
    $value = $node->field_ficha_de_pago[LANGUAGE_NONE][0];
    $image['uri'] = $value['uri'];
    $image['filename'] = $value['filename'];

    $data['field_ficha_de_pago'] = $image;
  }

  // Field collection field.
  $collection = $node->field_poliza_coberturas;

  if ($collection) {
    $cid = $collection[LANGUAGE_NONE][0]['value'];
    $entity = entity_load('field_collection_item', [$cid], [], TRUE);
    $entity = $entity[$cid];

    if ($entity->field_poliza_tipo) {
      $data['field_poliza_tipo'] = contract_export_export_get_field_value($entity->field_poliza_tipo, 'list', 'field_poliza_tipo');
    }

    $collection_items = $entity->field_cobertura;
    if ($collection_items) {
      $items_data = [];

      foreach ($collection_items[LANGUAGE_NONE] as $item) {
        $cid = $item['value'];
        $entity = entity_load('field_collection_item', [$cid], [], TRUE);
        $entity = $entity[$cid];
        $item_data = [];

        if ($entity->field_cobertura_titulo) {
          $item_data['field_cobertura_titulo'] = contract_export_export_get_field_value($entity->field_cobertura_titulo, 'list', 'field_cobertura_titulo');
        }

        if ($entity->field_cobertura_deducible) {
          $item_data['field_cobertura_deducible'] = contract_export_export_get_field_value($entity->field_cobertura_deducible, 'list', 'field_cobertura_deducible');
        }

        if ($entity->field_cobertura_limite_riesgo) {
          $item_data['field_cobertura_limite_riesgo'] = contract_export_export_get_field_value($entity->field_cobertura_limite_riesgo, 'text');
        }

        $items_data[] = $item_data;
      }
    }

    $data['field_cobertura'] = $items_data;
  }
  // Field collection field End.

  // Payments.
  $data['payments'] = contract_export_export_get_contract_get_payments($node->nid);
  // Payments End.

  return json_encode($data);
}

/**
 * Helper function to get all contract payments.
 */
function contract_export_export_get_contract_get_payments($id) {
  if (!$id) {
    return FALSE;
  }

  $query = db_select('field_data_field_poliza', 'n');
  $query->fields('n', ['entity_id'])
    ->condition('bundle', 'recibo_contrato')
    ->condition('field_poliza_target_id', $id);

  $results = $query->execute()->fetchAll();

  $payments = [];
  foreach ($results as $result) {
    $node = node_load($result->entity_id, NULL, TRUE);
    $author = user_load($node->uid, TRUE);
    $editor = user_load($node->revision_uid, TRUE);

    $payment = [
      'title' => $node->title,
      'site' => variable_get('site_name'),
      'id' => $node->nid,
      'status' => $node->status,
      'created' => $node->created,
      'changed' => $node->changed,
      'author' => $author->name,
      'editor' => $editor->name,
    ];

    // Text Fields.
    if ($node->field_codigo_de_barras_rc) {
      $payment['field_codigo_de_barras_rc'] = contract_export_export_get_field_value($node->field_codigo_de_barras_rc, 'text');
    }

    if ($node->field_asegurado_nombre) {
      $payment['field_asegurado_nombre'] = contract_export_export_get_field_value($node->field_asegurado_nombre, 'text');
    }

    if ($node->field_serie_rc) {
      $payment['field_serie_rc'] = contract_export_export_get_field_value($node->field_serie_rc, 'text');
    }

    if ($node->field_primer_pago_rc) {
      $payment['field_primer_pago_rc'] = contract_export_export_get_field_value($node->field_primer_pago_rc, 'text');
    }

    if ($node->field_pago_subsecuente_rc) {
      $payment['field_pago_subsecuente_rc'] = contract_export_export_get_field_value($node->field_pago_subsecuente_rc, 'text');
    }

    if ($node->field_importe_con_letra_rc) {
      $payment['field_importe_con_letra_rc'] = contract_export_export_get_field_value($node->field_importe_con_letra_rc, 'text');
    }

    if ($node->field_contract_type) {
      $payment['field_contract_type'] = contract_export_export_get_field_value($node->field_contract_type, 'text');
    }

    if ($node->field_currency) {
      $payment['field_currency'] = contract_export_export_get_field_value($node->field_currency, 'text');
    }
    // Text Fields End.

    // Number Fields.
    if ($node->field_poliza_prima_neta) {
      $payment['field_poliza_prima_neta'] = contract_export_export_get_field_value($node->field_poliza_prima_neta, 'text');
    }

    if ($node->field_issuance) {
      $payment['field_issuance'] = contract_export_export_get_field_value($node->field_issuance, 'text');
    }

    if ($node->field_total_premium) {
      $payment['field_total_premium'] = contract_export_export_get_field_value($node->field_total_premium, 'text');
    }
    // Number Fields End.

    // List Fields.
    if ($node->field_poliza_forma_pago) {
      $payment['field_poliza_forma_pago'] = contract_export_export_get_field_value($node->field_poliza_forma_pago, 'list', 'field_poliza_forma_pago');
    }
    // List Fields End.

    // Date Fields.
    if ($node->field_vencimiento_rc) {
      $payment['field_vencimiento_rc'] = contract_export_export_get_field_value($node->field_vencimiento_rc, 'date');
    }

    if ($node->field_periodo_cobertura_rc) {
      $payment['field_periodo_cobertura_rc'] = contract_export_export_get_field_value($node->field_periodo_cobertura_rc, 'date');
    }

    if ($node->field_vencimiento_rc) {
      $payment['field_fecha_de_expedicion_rc'] = contract_export_export_get_field_value($node->field_fecha_de_expedicion_rc, 'date');
    }

    // Address Field.
    if ($node->field_asegurado_domicilio) {
      $payment['field_asegurado_domicilio'] = contract_export_export_get_field_value($node->field_asegurado_domicilio, 'address');
    }
    // Address Field End.

    $payments[] = $payment;
  }

  return $payments;
}

/**
 * Helper function to get all contract sinister.
 */
function contract_export_export_get_sinisters($node, $year) {
  if (!$node) {
    return FALSE;
  }

  $author = node_load($node->uid);
  $editor = node_load($node->revision_uid);

  $sinister = [
    'title' => $node->title,
    'type' => 'sinister',
    'date' => $node->created,
    'site' => variable_get('site_name'),
    'year' => $year,
    'id' => $node->nid,
    'status' => $node->status,
    'created' => $node->created,
    'changed' => $node->changed,
    'author' => $author->name,
    'editor' => $editor->name,
  ];

  if ($node->field_poliza) {
    $sinister['field_poliza'] = contract_export_export_get_field_value($node->field_poliza, 'node');
  }

  // Text Fields.
  if ($node->field_poblacion) {
    $sinister['field_poblacion'] = contract_export_export_get_field_value($node->field_poblacion, 'text');
  }

  if ($node->field_poliza_comentarios) {
    $sinister['field_poliza_comentarios'] = contract_export_export_get_field_value($node->field_poliza_comentarios, 'text');
  }

  if ($node->field_lugar_referencias) {
    $sinister['field_lugar_referencias'] = contract_export_export_get_field_value($node->field_lugar_referencias, 'text');
  }

  if ($node->field_comentarios_de_siniestro) {
    $sinister['field_comentarios_de_siniestro'] = contract_export_export_get_field_value($node->field_comentarios_de_siniestro, 'text');
  }

  if ($node->field_lugar_atencion) {
    $sinister['field_lugar_atencion'] = contract_export_export_get_field_value($node->field_lugar_atencion, 'text');
  }

  if ($node->field_informe) {
    $sinister['field_informe'] = contract_export_export_get_field_value($node->field_informe, 'text');
  }
  // Text Fields End.

  // Number Fields.
  if ($node->field_danos_materiales) {
    $sinister['field_danos_materiales'] = contract_export_export_get_field_value($node->field_danos_materiales, 'number');
  }

  if ($node->field_robo) {
    $sinister['field_robo'] = contract_export_export_get_field_value($node->field_robo, 'number');
  }

  if ($node->field_resp_civil) {
    $sinister['field_resp_civil'] = contract_export_export_get_field_value($node->field_resp_civil, 'number');
  }

  if ($node->field_gastos_medicos) {
    $sinister['field_gastos_medicos'] = contract_export_export_get_field_value($node->field_gastos_medicos, 'number');
  }

  if ($node->field_rc_viajero) {
    $sinister['field_rc_viajero'] = contract_export_export_get_field_value($node->field_rc_viajero, 'number');
  }

  if ($node->field_reserva_total) {
    $sinister['field_reserva_total'] = contract_export_export_get_field_value($node->field_reserva_total, 'number');
  }
  // Number Fields End.

  // List Fields.
  if ($node->field_status_sinister) {
    $sinister['field_status_sinister'] = contract_export_export_get_field_value($node->field_status_sinister, 'list', 'field_status_sinister');
  }
  // List Fields End.

  // Date Fields.
  if ($node->field_fecha_arribo) {
    $sinister['field_fecha_arribo'] = contract_export_export_get_field_value($node->field_fecha_arribo, 'date');
  }
  // Date Fields End.

  // Term Reference Fields.
  if ($node->field_estado_single) {
    $sinister['field_estado_single'] = contract_export_export_get_field_value($node->field_estado_single, 'term');
  }
  // Term Reference Fields End.

  // User Fields.
  if ($node->field_ajustador) {
    $sinister['field_ajustador'] = contract_export_export_get_field_value($node->field_ajustador, 'user');
  }

  if ($node->field_abogado) {
    $sinister['field_abogado'] = contract_export_export_get_field_value($node->field_abogado, 'user');
  }

  if ($node->field_hospital) {
    $sinister['field_hospital'] = contract_export_export_get_field_value($node->field_hospital, 'user');
  }

  if ($node->field_taller) {
    $sinister['field_taller'] = contract_export_export_get_field_value($node->field_taller, 'user');
  }

  if ($node->field_grua) {
    $sinister['field_grua'] = contract_export_export_get_field_value($node->field_grua, 'user');
  }

  if ($node->field_proveedores) {
    $sinister['field_proveedores'] = contract_export_export_get_field_value($node->field_proveedores, 'user');
  }
  // User Fields End.

  // Geo Fields.
  if ($node->field_mapa_siniestro) {
    $sinister['field_mapa_siniestro'] = contract_export_export_get_field_value($node->field_mapa_siniestro, 'geo');
  }

  if ($node->field_mapa_arribo) {
    $sinister['field_mapa_arribo'] = contract_export_export_get_field_value($node->field_mapa_arribo, 'geo');
  }
  // Geo Fields End.

  // Field collection.
  if ($node->field_siniestro_archivo) {
    $archive_field = $node->field_siniestro_archivo;
    $archive_field = $archive_field[LANGUAGE_NONE];
    $archives = [];

    foreach($archive_field as $archive) {
      $archive = $archive['value'];
      $archive_item = [];
      $entity = entity_load('field_collection_item', [$archive], [], TRUE);
      $entity = $entity[$archive];

      if ($entity->field_fecha) {
        $archive_item['field_fecha'] = contract_export_export_get_field_value($entity->field_fecha, 'date');
      }

      if ($entity->field_archivo_autor) {
        $archive_item['field_archivo_autor'] = contract_export_export_get_field_value($entity->field_archivo_autor, 'user');
      }

      if ($entity->field_documentos) {
        $archive_item['field_documentos'] = contract_export_export_get_field_files($entity->field_documentos);
      }

      if ($entity->field_archivo_categoria) {
        $archive_item['field_archivo_categoria'] = contract_export_export_get_field_value($entity->field_archivo_categoria, 'list', 'field_archivo_categoria');
      }

      if ($entity->field_archivo_comentario) {
        $archive_item['field_archivo_comentario'] = contract_export_export_get_field_value($entity->field_archivo_comentario, 'text');
      }

      if ($entity->field_visualizador) {
        $archive_item['field_visualizador'] = contract_export_export_get_field_files($entity->field_visualizador);
      }

      if ($archive_item) {
        $archives[] = $archive_item;
      }
    }

    $sinister['field_siniestro_archivo'] = $archives;
  }

  if ($node->field_conductor) {
    $driver_field = $node->field_conductor;
    $driver_field = $driver_field[LANGUAGE_NONE][0]['value'];
    $driver = [];
    $entity = entity_load('field_collection_item', [$driver_field], [], TRUE);
    $entity = $entity[$driver_field];

    // Text Fields.
    if ($entity->field_nombre) {
      $driver['field_nombre'] = contract_export_export_get_field_value($entity->field_nombre, 'text');
    }

    if ($entity->field_rfc) {
      $driver['field_rfc'] = contract_export_export_get_field_value($entity->field_rfc, 'text');
    }

    if ($entity->field_licencia_numero) {
      $driver['field_licencia_numero'] = contract_export_export_get_field_value($entity->field_licencia_numero, 'text');
    }

    if ($entity->field_telefono) {
      $driver['field_telefono'] = contract_export_export_get_field_value($entity->field_telefono, 'text');
    }

    if ($entity->field_nombre_quien_reporta) {
      $driver['field_nombre_quien_reporta'] = contract_export_export_get_field_value($entity->field_nombre_quien_reporta  , 'text');
    }

    if ($entity->field_telefono_quien_reporta) {
      $driver['field_telefono_quien_reporta'] = contract_export_export_get_field_value($entity->field_telefono_quien_reporta, 'text');
    }
    // Text Fields End.

    // User Fields.
    if ($entity->field_licencia_tipo) {
      $driver['field_licencia_tipo'] = contract_export_export_get_field_value($entity->field_licencia_tipo, 'term');
    }

    if ($entity->field_licencia_alta_lugar) {
      $driver['field_licencia_alta_lugar'] = contract_export_export_get_field_value($entity->field_licencia_alta_lugar, 'term');
    }
    // User Fields End.

    // Fields.
    if ($entity->field_licencia_alta_fecha) {
      $driver['field_licencia_alta_fecha'] = contract_export_export_get_field_value($entity->field_licencia_alta_fecha, 'date');
    }

    if ($entity->field_conductor_reporta) {
      $driver['field_conductor_reporta'] = contract_export_export_get_field_value($entity->field_conductor_reporta, 'boolean');
    }
    // Fields End.

    if ($entity->field_domicilio) {
      $driver['field_domicilio'] = contract_export_export_get_field_value($entity->field_domicilio, 'address');
    }

    $sinister['field_conductor'] = $driver;
  }

  if ($node->field_vehiculo_tercero) {
    $vehicle_other_field = $node->field_vehiculo_tercero;
    $vehicle_other_field = $vehicle_other_field[LANGUAGE_NONE];
    $vehicle_others = [];

    foreach($vehicle_other_field as $vehicle_other) {
      $vehicle_other = $vehicle_other['value'];
      $vehicle_other_item = [];
      $entity = entity_load('field_collection_item', [$vehicle_other], [], TRUE);
      $entity = $entity[$vehicle_other];

      // Text Fields
      if ($entity->field_propietario_nombre) {
        $vehicle_other_item['field_propietario_nombre'] = contract_export_export_get_field_value($entity->field_propietario_nombre, 'text');
      }

      if ($entity->field_propietario_telefono) {
        $vehicle_other_item['field_propietario_telefono'] = contract_export_export_get_field_value($entity->field_propietario_telefono, 'text');
      }

      if ($entity->field_conductor_nombre) {
        $vehicle_other_item['field_conductor_nombre'] = contract_export_export_get_field_value($entity->field_conductor_nombre, 'text');
      }

      if ($entity->field_conductor_telefono) {
        $vehicle_other_item['field_conductor_telefono'] = contract_export_export_get_field_value($entity->field_conductor_telefono, 'text');
      }

      if ($entity->field_licencia_numero) {
        $vehicle_other_item['field_licencia_numero'] = contract_export_export_get_field_value($entity->field_licencia_numero, 'text');
      }

      if ($entity->field_3ro_vehiculo_placas) {
        $vehicle_other_item['field_3ro_vehiculo_placas'] = contract_export_export_get_field_value($entity->field_3ro_vehiculo_placas, 'text');
      }

      if ($entity->field_3ro_vehiculo_serie) {
        $vehicle_other_item['field_3ro_vehiculo_serie'] = contract_export_export_get_field_value($entity->field_3ro_vehiculo_serie, 'text');
      }

      if ($entity->field_3ro_numero_poliza) {
        $vehicle_other_item['field_3ro_numero_poliza'] = contract_export_export_get_field_value($entity->field_3ro_numero_poliza, 'text');
      }

      if ($entity->field_3ro_cobertura) {
        $vehicle_other_item['field_3ro_cobertura'] = contract_export_export_get_field_value($entity->field_3ro_cobertura, 'text');
      }

      if ($entity->field_3ro_deducible) {
        $vehicle_other_item['field_3ro_deducible'] = contract_export_export_get_field_value($entity->field_3ro_deducible, 'text');
      }

      if ($entity->field_3ro_siniestro) {
        $vehicle_other_item['field_3ro_siniestro'] = contract_export_export_get_field_value($entity->field_3ro_siniestro, 'text');
      }

      if ($entity->field_3ro_vehiculo_danos) {
        $vehicle_other_item['field_3ro_vehiculo_danos'] = contract_export_export_get_field_value($entity->field_3ro_vehiculo_danos, 'text');
      }
      // Text Fields End.

      // Term Fields.
      if ($entity->field_vehiculo_marca) {
        $vehicle_other_item['field_vehiculo_marca'] = contract_export_export_get_field_value($entity->field_vehiculo_marca, 'term');
      }

      if ($entity->field_vehiculo_tipo) {
        $vehicle_other_item['field_vehiculo_tipo'] = contract_export_export_get_field_value($entity->field_vehiculo_tipo, 'term');
      }

      if ($entity->field_3ro_vehiculo_color) {
        $vehicle_other_item['field_3ro_vehiculo_color'] = contract_export_export_get_field_value($entity->field_3ro_vehiculo_color, 'term');
      }

      if ($entity->field_3ro_aseguradora) {
        $vehicle_other_item['field_3ro_aseguradora'] = contract_export_export_get_field_value($entity->field_3ro_aseguradora, 'term');
      }

      if ($entity->field_3ro_ajustador) {
        $vehicle_other_item['field_3ro_ajustador'] = contract_export_export_get_field_value($entity->field_3ro_ajustador, 'term');
      }

      if ($entity->field_promotor) {
        $vehicle_other_item['field_promotor'] = contract_export_export_get_field_value($entity->field_promotor, 'term');
      }
      // Term Fields End.

      //Fields.
        if ($entity->field_3ro_vehiculo_modelo) {
          $vehicle_other_item['field_3ro_vehiculo_modelo'] = contract_export_export_get_field_value($entity->field_3ro_vehiculo_modelo, 'number');
        }

        if ($entity->field_conductor_es_propietario) {
          $vehicle_other_item['field_conductor_es_propietario'] = contract_export_export_get_field_value($entity->field_conductor_es_propietario, 'list', 'field_conductor_es_propietario');
        }

        if ($entity->field_3ro_vencimiento) {
          $vehicle_other_item['field_3ro_vencimiento'] = contract_export_export_get_field_value($entity->field_3ro_vencimiento, 'date');
        }

        if ($entity->field_taller) {
          $vehicle_other_item['field_taller'] = contract_export_export_get_field_value($entity->field_taller, 'user');
        }

        if ($entity->field_propietario_domicilio) {
          $vehicle_other_item['field_propietario_domicilio'] = contract_export_export_get_field_value($entity->field_propietario_domicilio, 'address');
        }

        if ($entity->field_conductor_domicilio) {
          $vehicle_other_item['field_conductor_domicilio'] = contract_export_export_get_field_value($entity->field_conductor_domicilio, 'address');
        }
      // Fields End.

      if ($vehicle_other_item) {
        $vehicle_others[] = $vehicle_other_item;
      }
    }

    $sinister['field_vehiculo_tercero'] = $vehicle_others;
  }

  if ($node->field_lesionado) {
    $injured_field = $node->field_lesionado;
    $injured_field = $injured_field[LANGUAGE_NONE];
    $injured_group = [];

    foreach($injured_field as $injured) {
      $injured = $injured['value'];
      $injured_item = [];
      $entity = entity_load('field_collection_item', [$injured], [], TRUE);
      $entity = $entity[$injured];

      // Text Fields
      if ($entity->field_lesionado_nombre) {
        $injured_item['field_lesionado_nombre'] = contract_export_export_get_field_value($entity->field_lesionado_nombre, 'text');
      }

      if ($entity->field_lesionado_telefono) {
        $injured_item['field_lesionado_telefono'] = contract_export_export_get_field_value($entity->field_lesionado_telefono, 'text');
      }

      if ($entity->field_lesionado_ambulancia_info) {
        $injured_item['field_lesionado_ambulancia_info'] = contract_export_export_get_field_value($entity->field_lesionado_ambulancia_info, 'text');
      }

      if ($entity->field_lesionado_pase_medico) {
        $injured_item['field_lesionado_pase_medico'] = contract_export_export_get_field_value($entity->field_lesionado_pase_medico, 'text');
      }

      if ($entity->field_lesionado_lesiones) {
        $injured_item['field_lesionado_lesiones'] = contract_export_export_get_field_value($entity->field_lesionado_lesiones, 'text');
      }
      // Text Fields End.

      //Fields.
        if ($entity->field_lesionado_edad) {
          $injured_item['field_lesionado_edad'] = contract_export_export_get_field_value($entity->field_lesionado_edad, 'number');
        }


        if ($entity->field_lesionado_riesgo_b) {
          $injured_item['field_lesionado_riesgo_b'] = contract_export_export_get_field_value($entity->field_lesionado_riesgo_b, 'list', 'field_lesionado_riesgo_b');
        }

        if ($entity->field_lesionado_ambulancia) {
          $injured_item['field_lesionado_ambulancia'] = contract_export_export_get_field_value($entity->field_lesionado_ambulancia, 'list', 'field_lesionado_ambulancia');
        }

        if ($entity->field_hospital) {
          $injured_item['field_hospital'] = contract_export_export_get_field_value($entity->field_hospital, 'user');
        }

        if ($entity->field_lesionado_domicilio) {
          $injured_item['field_lesionado_domicilio'] = contract_export_export_get_field_value($entity->field_lesionado_domicilio, 'address');
        }
      // Fields End.

      if ($vehicle_other_item) {
        $injured_group[] = $injured_item;
      }
    }

    $sinister['field_lesionado'] = $injured_group;
  }
  // Field collection End.

  return json_encode($sinister);
}

/**
 * Helper function to get files data from given field.
 */
function contract_export_export_get_field_files($value) {
  $values = $value[LANGUAGE_NONE];
  $files = [];

  foreach ($values as $value) {
    $files[] = [
      'filename' => $value['filename'],
      'uri' => $value['uri'],
      'type' => $value['type'],
      'description' => !empty($value['description']) ? $value['description'] : '',
    ];
  }

  return $files;
}

/**
 * Helper function to get data from given field.
 */
function contract_export_export_get_field_value($value, $type, $field_name = '') {
  $value = $value[LANGUAGE_NONE][0];

  switch ($type) {
    case 'text':
    case 'number':
    case 'date':
    case 'boolean':
      if (!empty($value['value2'])) {
        $value = $value['value'] . ' TO ' . $value['value2'];
      }
      else {
        $value = $value['value'];
      }
      break;
    case 'list':
      $value = $value['value'];
      if ($field_name) {
        $field = field_info_field($field_name);
        $allowed_values = $field['settings']['allowed_values'];
        if (is_array($allowed_values)) {
          if (array_key_exists($value, $allowed_values)) {
            $value = $allowed_values[$value];
          }
        }
      }
      break;
    case 'term':
      $tid = $value['tid'];
      $term = taxonomy_term_load($tid);
      $value = $term->name;
      break;
    case 'user':
      $uid = '';
      if ($value['target_id']) {
       $uid = $value['target_id'];
      }
      elseif ($value['tid']) {
        $uid = $value['tid'];
      }
      if ($uid) {
        $user = user_load($uid, TRUE);
        $value = $user->name;
      }
      break;
    case 'geo':
      $value = [
        'lat' => $value['lat'],
        'lng' => $value['lng'],
      ];
      break;
    case 'address':
      $value = [
        'country' => !empty($value['country']) ? $value['country'] : 'MX',
        'administrative_area' => !empty($value['administrative_area']) ? $value['administrative_area'] : '',
        'locality' => !empty($value['locality']) ? $value['locality'] : '',
        'postal_code' => !empty($value['postal_code']) ? $value['postal_code'] : '',
        'thoroughfare' => !empty($value['thoroughfare']) ? $value['thoroughfare'] : '',
        'premise' => !empty($value['premise']) ? $value['premise'] : '',
      ];
      break;
    case 'node':
      $node = node_load($value['target_id'], NULL, TRUE);
      $value = [
        'title' => $node->title,
        'site' => variable_get('site_name'),
        'id' => $node->nid,
      ];
  }

  return $value;
}
