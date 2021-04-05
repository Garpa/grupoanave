<?php

/**
 * @file
 * This file has scrip Raul.
 */

 // Contract content type.
 // Term references fields.
 $field_plz_vehiculo_marca = isset($node->field_plz_vehiculo_marca) &&
  count($node->field_plz_vehiculo_marca) !=0?
  $node->field_plz_vehiculo_marca['und']: "";

 $field_vehiculo_submarca	= isset($node->field_vehiculo_submarca) &&
  count($node->field_vehiculo_submarca) !=0?
  $node->field_vehiculo_submarca['und']: "";

 $field_vehiculo_descripcion	= isset($node->field_vehiculo_descripcion	) &&
  count($node->field_vehiculo_descripcion	) !=0?
  $node->field_vehiculo_descripcion['und']: "";

 $field_vehiculo_carroceria_select	= isset($node->field_vehiculo_carroceria_select) &&
  count($node->field_vehiculo_carroceria_select) > 0?
  $node->field_vehiculo_carroceria_select['und']: "";

 $field_motivos_de_cancelacion	= isset($node->field_motivos_de_cancelacion) &&
  count($node->field_motivos_de_cancelacion) > 0?
  $node->field_motivos_de_cancelacion['und']: "";

 // Entity References fields.
 $field_usuario_de_pagado = isset($node->field_usuario_de_pagado) &&
  count($node->field_usuario_de_pagado) > 0?
  $node->field_usuario_de_pagado['und']: "";

 $field_usuario_de_cancelado = isset($node->field_usuario_de_cancelado) &&
  count($node->field_usuario_de_cancelado) > 0?
  $node->field_usuario_de_cancelado['und']: "";

 $field_asignar_promotor = isset($node->field_asignar_promotor) &&
  count($node->field_asignar_promotor) > 0?
  $node->field_asignar_promotor['und']: "";

 // Comando para corroborar que existan datos dentro del campo mencionado
   //********************
   // var_dump($node->field_asignar_promotor
   //********************

 // Term references fields.
 array_push($node, $field_plz_vehiculo_marca);
 array_push($node, $field_vehiculo_submarca);
 array_push($node, $field_vehiculo_descripcion);
 array_push($node, $field_vehiculo_carroceria_select);
 array_push($node, $field_motivos_de_cancelacion);

 // Entity references fields.
 array_push($node, $field_usuario_de_pagado);
 array_push($node, $field_usuario_de_cancelado);
 array_push($node, $field_asignar_promotor);
 // Contract content type.

 // Array ouput.
 array_push($output, array($node->nid => $node));

 //echo '<pre>'.print_r($output, true).'</pre>';
