<?php

/**
* @file
* This file has scrip Alexa.
*/
  $field_vehiculo_serie = isset($node->field_vehiculo_serie) ?
    $node->field_vehiculo_serie["und"][0]["value"] : "";

  $field_poliza_prima_neta = isset($node->field_poliza_prima_neta) ?
    $node->field_poliza_prima_neta['und'][0]['value'] : "";

  $field_derecho_de_poliza2 = isset($node->field_derecho_de_poliza2) &&
    count($node->field_derecho_de_poliza2) != 0 ?
    $node->field_derecho_de_poliza2['und'][0]['value'] : "";

  $field_pago_fraccionado = isset($node->field_pago_fraccionado) &&
    count($node->field_derecho_de_poliza2) != 0 ?
    $node->field_pago_fraccionado['und'][0]['value'] : "";

  $field_poliza_prima_total = isset($node->field_poliza_prima_total) ?
    $node->field_poliza_prima_total['und'][0]['value'] : "";

  $field_poliza_prima_1er_recibo = isset($node->field_poliza_prima_1er_recibo) ?
    $node->field_poliza_prima_1er_recibo ['und'][0]['value'] : "";

  $field_poliza_primas_recibos_subs = isset($node->field_poliza_primas_recibos_subs) ?
    $node->field_poliza_primas_recibos_subs['und'][0]['value'] : "";

  $field_asegurado_io = isset($node->field_asegurado_io) &&
    count($node->field_asegurado_io) != 0 ?
    $node->field_asegurado_io['und']: "";

  //Vigencia
  $field_poliza_rgo_pago_fracc = isset($node->field_poliza_rgo_pago_fracc) &&
    count($node->field_poliza_rgo_pago_fracc) != 0?
    $node->field_poliza_rgo_pago_fracc['und']: "";

  $field_poliza_coberturas = isset($node->field_poliza_coberturas) &&
    count($node->field_poliza_coberturas) != 0?
    $node->field_poliza_coberturas['und']: "";

  //Status
  $field_ficha_de_pago = isset($node->field_ficha_de_pago) &&
  count($node->field_ficha_de_pago) != 0?
  $node->field_ficha_de_pago['und']:"";

  array_push($nodeFields, $field_vehiculo_serie);
  array_push($nodeFields, $field_poliza_prima_neta);
  array_push($nodeFields, $field_derecho_de_poliza2);
  array_push($nodeFields, $field_pago_fraccionado);
  array_push($nodeFields, $field_poliza_prima_total);
  array_push($nodeFields, $field_poliza_prima_1er_recibo);
  array_push($nodeFields, $field_poliza_primas_recibos_subs);
  array_push($nodeFields, $field_poliza_coberturas);
  array_push($nodeFields, $field_asegurado_io);
  array_push($nodeFields, $field_poliza_rgo_pago_fracc);
  array_push($nodeFields, $field_ficha_de_pago);

  array_push($output, array($node->nid => $nodeFields));
