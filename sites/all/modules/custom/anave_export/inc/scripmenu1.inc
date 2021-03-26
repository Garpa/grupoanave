<?php

/**
 * @file
 * This file has scrip Agustin.
 */

// Policy fields.
$field_poliza_emision = isset($node->field_poliza_emision) ?
  $node->field_poliza_emision['und'][0]['value'] : "";

$field_poliza_vigencia = isset($node->field_poliza_vigencia) ?
  $node->field_poliza_emision['und'][0]['value'] : "";

$field_poliza_coberturas = isset($node->field_poliza_coberturas) ?
  $node->field_poliza_coberturas['und'][0]['value'] : "";

$field_poliza_forma_pago = isset($node->field_poliza_forma_pago) ?
  $node->field_poliza_forma_pago['und'][0]['value'] : "";

$field_poliza_moneda = isset($node->field_poliza_moneda) ?
  $node->field_poliza_moneda['und'][0]['value'] : "";

// Insured fields.
$field_asegurado_nombre = isset($node->field_asegurado_nombre) ?
  $node->field_asegurado_nombre['und'][0]['value'] : "";

$field_asegurado_rfc = isset($node->field_asegurado_rfc) ?
  $node->field_asegurado_rfc['und'][0]['value'] : "";

$field_asegurado_telefono = isset($node->field_asegurado_telefono) ?
  $node->field_asegurado_telefono['und'][0]['value'] : "";

$field_asegurado_benef_pref = isset($node->field_asegurado_benef_pref) ?
  $node->field_asegurado_benef_pref['und'][0]['value'] : "";

// Vehicle fields.
$field_vehiculo_modelo = isset($node->field_vehiculo_modelo) ?
  $node->field_vehiculo_modelo['und'][0]['value'] : "";

$field_vehiculo_color = isset($node->field_vehiculo_color) ?
  $node->field_vehiculo_color['und'][0]['value'] : "";

$field_vehiculo_transmision = isset($node->field_vehiculo_transmision) ?
  $node->field_vehiculo_transmision['und'][0]['value'] : "";

$field_vehiculo_cilindros = isset($node->field_vehiculo_cilindros) ?
  $node->field_vehiculo_cilindros['und'][0]['value'] : "";

$field_vehiculo_serie = isset($node->field_vehiculo_serie) ?
  $node->field_vehiculo_serie['und'][0]['value'] : "";

$field_vehiculo_motor = isset($node->field_vehiculo_motor) ?
  $node->field_vehiculo_motor['und'][0]['value'] : "";

$field_vehiculo_placas = isset($node->field_vehiculo_placas) ?
  $node->field_vehiculo_placas['und'][0]['value'] : "";

$field_vehiculo_capacidad = isset($node->field_vehiculo_capacidad) ?
  $node->field_vehiculo_capacidad['und'][0]['value'] : "";

$field_vehiculo_servicio = isset($node->field_vehiculo_servicio) ?
  $node->field_vehiculo_servicio['und'][0]['value'] : "";

$field_vehiculo_tonelaje = isset($node->field_vehiculo_tonelaje) ?
  $node->field_vehiculo_tonelaje['und'][0]['value'] : "";

$field_vehiculo_tipo_carga = isset($node->field_vehiculo_tipo_carga) ?
  $node->field_vehiculo_tipo_carga['und'][0]['value'] : "";

$field_vehiculo_descripcion_carga = isset($node->field_vehiculo_descripcion_carga) ?
  $node->field_vehiculo_descripcion_carga['und'][0]['value'] : "";

$field_vehiculo_remolque = isset($node->field_vehiculo_remolque) ?
  $node->field_vehiculo_remolque['und'][0]['value'] : "";

$field_vehiculo_tipo_remolque = isset($node->field_vehiculo_tipo_remolque) ?
  $node->field_vehiculo_tipo_remolque['und'][0]['value'] : "";

// Status fields.
$field_periodo_de_gracia = isset($node->field_periodo_de_gracia) ?
  $node->field_periodo_de_gracia['und'][0]['value'] : "";

$field_poliza_status = isset($node->field_poliza_status) ?
  $node->field_poliza_status['und'][0]['value'] : "";

$field_fecha_de_pagado = isset($node->field_fecha_de_pagado) ?
  $node->field_fecha_de_pagado['und'][0]['value'] : "";

$field_fecha_de_cancelacion = isset($node->field_fecha_de_cancelacion) ?
  $node->field_fecha_de_cancelacion['und'][0]['value'] : "";

// General fields.
$field_vehiculo_uso = isset($node->field_vehiculo_uso) ?
  $node->field_vehiculo_uso['und'][0]['value'] : "";

$field_vehiculo_clave_sbg = isset($node->field_vehiculo_clave_sbg) ?
  $node->field_vehiculo_clave_sbg['und'][0]['value'] : "";

$field_vehiculo_categoria = isset($node->field_vehiculo_categoria) ?
  $node->field_vehiculo_categoria['und'][0]['value'] : "";

$field_vehiculo_numero_pedimento = isset($node->field_vehiculo_numero_pedimento) ?
  $node->field_vehiculo_numero_pedimento['und'][0]['value'] : "";

$field_vehiculo_carroceria = isset($node->field_vehiculo_carroceria) ?
  $node->field_vehiculo_carroceria['und'][0]['value'] : "";

$field_poliza_derecho_poliza = isset($node->field_poliza_derecho_poliza) ?
  $node->field_poliza_derecho_poliza['und'][0]['value'] : "";

$field_vehiculo_numero_inventario = isset($node->field_vehiculo_numero_inventario) ?
  $node->field_vehiculo_numero_inventario['und'][0]['value'] : "";

$field_vehiculo_referencia = isset($node->field_vehiculo_referencia) ?
  $node->field_vehiculo_referencia['und'][0]['value'] : "";

// Others fields.
$field_poliza_impuesto_iva = isset($node->field_poliza_impuesto_iva) ?
  $node->field_poliza_impuesto_iva['und'][0]['value'] : "";

// General policy fields.
$field_poliza_reduccion = isset($node->field_poliza_reduccion) ?
  $node->field_poliza_reduccion['und'][0]['value'] : "";
  //var_dump($node);

// Policy fields.
array_push($nodeFields, $field_poliza_oficina);
array_push($nodeFields, $field_poliza_emision);
array_push($nodeFields, $field_poliza_vigencia);
array_push($nodeFields, $field_poliza_coberturas);
array_push($nodeFields, $field_poliza_forma_pago);
array_push($nodeFields, $field_poliza_moneda);

// Insured fields.
array_push($nodeFields, $field_asegurado_nombre);
array_push($nodeFields, $field_asegurado_rfc);
array_push($nodeFields, $field_asegurado_telefono);
array_push($nodeFields, $field_asegurado_benef_pref);

// Vehicle fields.
array_push($nodeFields, $field_vehiculo_modelo);
array_push($nodeFields, $field_vehiculo_color);
array_push($nodeFields, $field_vehiculo_transmision);
array_push($nodeFields, $field_vehiculo_cilindros);
array_push($nodeFields, $field_vehiculo_serie);
array_push($nodeFields, $field_vehiculo_motor);
array_push($nodeFields, $field_vehiculo_placas);
array_push($nodeFields, $field_vehiculo_capacidad);
array_push($nodeFields, $field_vehiculo_servicio);
array_push($nodeFields, $field_vehiculo_tonelaje);
array_push($nodeFields, $field_vehiculo_tipo_carga);
array_push($nodeFields, $field_vehiculo_descripcion_carga);
array_push($nodeFields, $field_vehiculo_remolque);
array_push($nodeFields, $field_vehiculo_tipo_remolque);

// Status fields.
array_push($nodeFields, $field_periodo_de_gracia);
array_push($nodeFields, $field_poliza_status);
array_push($nodeFields, $field_fecha_de_pagado);
array_push($nodeFields, $field_fecha_de_cancelacion);

// General fields.
array_push($nodeFields, $field_vehiculo_uso);
array_push($nodeFields, $field_vehiculo_clave_sbg);
array_push($nodeFields, $field_vehiculo_categoria);
array_push($nodeFields, $field_vehiculo_numero_pedimento);
array_push($nodeFields, $field_vehiculo_carroceria);
array_push($nodeFields, $field_poliza_derecho_poliza);
array_push($nodeFields, $field_vehiculo_numero_inventario);
array_push($nodeFields, $field_vehiculo_referencia);

// Others fields.
array_push($nodeFields, $field_poliza_impuesto_iva);

// General policy fields.
array_push($nodeFields, $field_poliza_reduccion);

array_push($output, array($node->nid => $nodeFields));
