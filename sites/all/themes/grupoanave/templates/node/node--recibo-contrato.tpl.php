<?php
/**
 * @file
 * Default theme implementation to display a node.
 *
 * Available variables:
 * - $title: the (sanitized) title of the node.
 * - $content: An array of node items. Use render($content) to print them all,
 *   or print a subset such as render($content['field_example']). Use
 *   hide($content['field_example']) to temporarily suppress the printing of a
 *   given element.
 * - $user_picture: The node author's picture from user-picture.tpl.php.
 * - $date: Formatted creation date. Preprocess functions can reformat it by
 *   calling format_date() with the desired parameters on the $created variable.
 * - $name: Themed username of node author output from theme_username().
 * - $node_url: Direct URL of the current node.
 * - $display_submitted: Whether submission information should be displayed.
 * - $submitted: Submission information created from $name and $date during
 *   template_preprocess_node().
 * - $classes: String of classes that can be used to style contextually through
 *   CSS. It can be manipulated through the variable $classes_array from
 *   preprocess functions. The default values can be one or more of the
 *   following:
 *   - node: The current template type; for example, "theming hook".
 *   - node-[type]: The current node type. For example, if the node is a
 *     "Blog entry" it would result in "node-blog". Note that the machine
 *     name will often be in a short form of the human readable label.
 *   - node-teaser: Nodes in teaser form.
 *   - node-preview: Nodes in preview mode.
 *   The following are controlled through the node publishing options.
 *   - node-promoted: Nodes promoted to the front page.
 *   - node-sticky: Nodes ordered above other non-sticky nodes in teaser
 *     listings.
 *   - node-unpublished: Unpublished nodes visible only to administrators.
 * - $title_prefix (array): An array containing additional output populated by
 *   modules, intended to be displayed in front of the main title tag that
 *   appears in the template.
 * - $title_suffix (array): An array containing additional output populated by
 *   modules, intended to be displayed after the main title tag that appears in
 *   the template.
 *
 * Other variables:
 * - $node: Full node object. Contains data that may not be safe.
 * - $type: Node type; for example, story, page, blog, etc.
 * - $comment_count: Number of comments attached to the node.
 * - $uid: User ID of the node author.
 * - $created: Time the node was published formatted in Unix timestamp.
 * - $classes_array: Array of html class attribute values. It is flattened
 *   into a string within the variable $classes.
 * - $zebra: Outputs either "even" or "odd". Useful for zebra striping in
 *   teaser listings.
 * - $id: Position of the node. Increments each time it's output.
 *
 * Node status variables:
 * - $view_mode: View mode; for example, "full", "teaser".
 * - $teaser: Flag for the teaser state (shortcut for $view_mode == 'teaser').
 * - $page: Flag for the full page state.
 * - $promote: Flag for front page promotion state.
 * - $sticky: Flags for sticky post setting.
 * - $status: Flag for published status.
 * - $comment: State of comment settings for the node.
 * - $readmore: Flags true if the teaser content of the node cannot hold the
 *   main body content.
 * - $is_front: Flags true when presented in the front page.
 * - $logged_in: Flags true when the current user is a logged-in member.
 * - $is_admin: Flags true when the current user is an administrator.
 *
 * Field variables: for each field instance attached to the node a corresponding
 * variable is defined; for example, $node->body becomes $body. When needing to
 * access a field's raw values, developers/themers are strongly encouraged to
 * use these variables. Otherwise they will have to explicitly specify the
 * desired field language; for example, $node->body['en'], thus overriding any
 * language negotiation rule that was previously applied.
 *
 * @see template_preprocess()
 * @see template_preprocess_node()
 * @see template_process()
 *
 * @ingroup themeable
 */
?>

<?php $parent_data = node_collection_api_get_parent_node_instance($node ->nid);

// get field collections field_poliza_coberturas items from parent node
$fcentity = field_collection_item_load($parent_data->field_poliza_coberturas[LANGUAGE_NONE][0]['value'], $reset = FALSE);
// get field collection items from field_cobertura
$fcfields = field_collection_item_load($fcentity->field_cobertura[LANGUAGE_NONE][0]['value'], $reset = FALSE);


$fc_fields_array = $fcentity->field_cobertura[LANGUAGE_NONE];
//print_r($fc_fields_array);

foreach($fc_fields_array as $key => $value) {
  $fc_item_id = field_collection_item_load($fc_fields_array[$key]['value']);
  $keys_fc_list[] = $fc_item_id->field_cobertura_titulo[LANGUAGE_NONE][0]['value'];
}

$field_info = field_info_field('field_cobertura_titulo');
/*
foreach($keys_fc_list as $key => $value) {
  $label_list = $field_info['settings']['allowed_values'][$value];
  print_r($label_list);
}
*/
//print_r($label_list);
//exit;
//print_r($fcentity->field_cobertura[LANGUAGE_NONE][0]['value']); exit;
//print_r($fcfields); exit;
//print_r($fcfields->field_cobertura_titulo[LANGUAGE_NONE][0]['value']); exit;

// get the label from the list value field_cobertura_titulo 
$key = $fcfields->field_cobertura_titulo[LANGUAGE_NONE][0]['value']; // Or whatever
$field = field_info_field('field_cobertura_titulo');
$label = $field['settings']['allowed_values'][$key];
//print_r($key); exit;

$url = ($_SERVER['REQUEST_URI']);
$typePage = preg_split('[/]', $url);
$typePage = $typePage[1];

if ($typePage == "content") {
  $receiptClass = $typePage;
} else if ($typePage == "print") {
  $receiptClass = $typePage;
} else {
  $receiptClass = "";
}

function getDateFormat($date) {
  $day = date_create($date);
  $day = date_format($day,"d");
  
  $month = date_create($date);
  $month = date_format($month,"n");
  
  $year = date_create($date);
  $year = date_format($year,"Y");
  
  switch ($month) {
  case 1:
    $spanishMonth = "Enero";
  case 2:
    $spanishMonth = "Febrero";
    break;
  case 3:
    $spanishMonth = "Marzo";
    break;
  case 4:
    $spanishMonth = "Abril";
    break;
  case 5:
    $spanishMonth = "Mayo";
    break;
  case 6:
    $spanishMonth = "Junio";
    break;
  case 7:
    $spanishMonth = "Julio";
    break;
  case 8:
    $spanishMonth = "Agosto";
    break;
  case 9:
    $spanishMonth = "Septiembre";
    break;
  case 10:
    $spanishMonth = "Octubre";
    break;
  case 11:
    $spanishMonth = "Noviembre";
    break;
  case 12:
    $spanishMonth = "Diciembre";
    break;
  }
  return $day."/".$spanishMonth."/".$year;
}
//get serie
$serie = $node->field_serie_rc[LANGUAGE_NONE][0]['value'];
if ($serie) {
  //divide serie through "/" character
  $serie = preg_split("[/]", $serie);
  //get payments number
  $serie = $serie[1];
}


$payment_first = $node->field_primer_pago_rc[LANGUAGE_NONE][0]['value'];
$raw_payment = $parent_data->field_poliza_primas_recibos_subs[LANGUAGE_NONE][0]['value'];
$subsecuent_payment = $node->field_pago_subsecuente_rc[LANGUAGE_NONE][0]['value'];
$net_premium = $parent_data->field_poliza_prima_neta[LANGUAGE_NONE][0]['value'];
$net_premium = $net_premium / $serie;
$right_policy = $node->field_emision_recibo_ref_rc[LANGUAGE_NONE][0]['value'];
$iva = 0;


// calculate IVA
//$iva = $iva / $serie;
$raw_payment = $raw_payment - $iva;
$payment_first= $payment_first - $iva;

//$iva = round($iva, 2);
$raw_payment = round($raw_payment, 2);


if ($right_policy == 0) {
  $right_policy = "0.00";
}

?>
<div id="node-<?php print $node->nid; ?>" class="<?php print $classes; ?> clearfix"<?php print $attributes; ?>>

  <?php print $user_picture; ?>

  <?php print render($title_prefix); ?>
  <?php if (!$page): ?>
<!--     <h2<?php print $title_attributes; ?>><a href="<?php print $node_url; ?>"><?php print $title; ?></a></h2> -->
  <?php endif; ?>
  <?php print render($title_suffix); ?>

  <?php if ($display_submitted): ?>
    <div class="submitted">
      <?php print $submitted; ?>
    </div>
  <?php endif; ?>

  <div class="content"<?php print $content_attributes; ?>>
    <div id="main-payment-receip">

    <div class="print-header main-payment-header">
      <table>
        <tbody>
          <tr>
            <td class="print-logo">
              <strong>MN Global Protec A.C.</strong><br>
              Calzada Independencia  Norte No. 1131, Colonia <br>
              Independencia, Guadalajara, Jalisco, Mexico<br>
              C.P. 44290 <br>
            </td>
            <td class="print-title">
              <h1>CONCENTRACION EMPRESARIAL DE PAGO PARA USO EXCLUSIVO DEL BANCO</h1>
            </td>
          </tr>
        </tbody>
      </table>
    </div>

    <div class="recibo">
      
      <div class="col6 one">
        <table>
          <tr>
            <td>
              <div class="barcode"><?php print render($content['field_codigo_de_barras_rc'][0]['#svg']); ?></div>
              <?php print render($node->field_codigo_de_barras_rc[LANGUAGE_NONE][0]['safe_value']); ?>
            </td>
          </tr>
          <tr>
        </table>    
      </div>
      
      <div class="col6 two">
        <table>
          <tr>
            <td> 
              <strong>Serie:</strong>
              <?php /* if(isset()): */?>
              <?php print render($node->field_serie_rc[LANGUAGE_NONE][0]['value']); ?>
              <?php /* endif; */?>
              <strong>Folio del Recibo:</strong>
              <?php /* if(isset()): */?>
              <?php print render($node->title); ?>
              <?php /* endif; */?>
            </td>
          </tr>
          
          <tr>
            <td> 
              <strong>Vencimiento del Recibo:</strong>
              <?php /* if(isset()): */?>
              <?php
                if(isset($node->field_vencimiento_rc[LANGUAGE_NONE][0]['value'])) {
                  $due_date = $node->field_vencimiento_rc[LANGUAGE_NONE][0]['value'];
                  $dateFormate = getDateFormat($due_date);
                  print render($dateFormate);
                }
              ?>
              <?php /* endif; */?>
          </tr>
          
          <tr>
            <td> 
              <strong>Periodo de cobertura del:</strong>
              <?php /* if(isset()): */?>
              <?php
                $dateFormate = getDateFormat($node->field_periodo_cobertura_rc[LANGUAGE_NONE][0]['value']);
                print render($dateFormate); 
              ?>
              <?php /* endif; */?>
            </td>
          </tr>
          
          <tr>
            <td> 
              <strong class="to">al:</strong>
              <?php /* if(isset()): */?>
              <?php
                $dateFormate = getDateFormat($node->field_periodo_cobertura_rc[LANGUAGE_NONE][0]['value2']);
                print render($dateFormate); 
              ?>
              <?php /* endif; */?>
            </td>
          </tr>
          
          <tr class="tr-contract-number">
            <td> 
              <strong>Contrato No:</strong>
              <?php /* if(isset()): */?>
              <?php print render($parent_data->title);?>
              <?php /* endif; */?>
            </td>
          </tr>
          
          <tr class="tr-payment">
            <td> 
              <strong>Forma de Pago:</strong>
              <?php /* if(isset()): */?>
              <?php print render($parent_data->field_poliza_forma_pago[LANGUAGE_NONE][0]['value']);?>
              <?php /* endif; */?>
            </td>
          </tr>
          
          <tr class="tr-type-contract">
            <td> 
              <strong>Tipo de Contrato:</strong>
              <?php /* if(isset()): */?>
              <?php
                print render ($fcentity->field_poliza_tipo[LANGUAGE_NONE][0]['value']);
/*
                 foreach($keys_fc_list as $key => $value) {
                   $label_list = $field_info['settings']['allowed_values'][$value];
                   print("$label_list <br>");
                  }
*/
               ?>
            </td>
          </tr>
          
          <tr>
            <td> 
              <?php /* endif; */?>
              <strong>Moneda:</strong>
              <?php /* if(isset()): */?>
              <?php print render($parent_data->field_poliza_moneda[LANGUAGE_NONE][0]['value']);?>
              <?php /* endif; */?>
            </td>
          </tr>
        </table>
      </div>
      
      <div class="col6 three">
        <table>
          <tr>
            <td> 
              <strong>Fecha de expedicion:</strong>
              <?php /* if(isset()): */?>
              <?php
                $dateFormate = getDateFormat($node->field_fecha_de_expedicion_rc[LANGUAGE_NONE][0]['value']);
                print render($dateFormate); 
              ?>
              <?php /* endif; */?>
            </td>
          </tr>
          
          <tr>
            <td>
              <strong>Solicitante de contrato:</strong>
              <?php /* if(isset()): */?>
              <?php
                if ($parent_data->field_asegurado_nombre[LANGUAGE_NONE][0]['value']) {
                  $insured = $parent_data->field_asegurado_nombre[LANGUAGE_NONE][0]['value'];
                  $insured = strtoupper($insured);
                  print render($insured);
                }
              ?>
              <?php /* endif; */?>
            </td>
          </tr>
          
          <tr>
            <td>
              <strong>Calle y No:</strong>
              <?php /* if(isset()): */?>
              <?php
                if ($parent_data->field_asegurado_domicilio[LANGUAGE_NONE][0]['thoroughfare']) {
                  $street = $parent_data->field_asegurado_domicilio[LANGUAGE_NONE][0]['thoroughfare'];
                  $street = strtoupper($street);
                  print render($street);
                }
              ?>
              <?php /* endif; */?>
            </td>
          </tr>
          
<!--
          <tr>
            <td>
              <strong>Colonia:</strong>
              <?php /* if(isset()): */?>
              <?php print render($parent_data->field_asegurado_domicilio[LANGUAGE_NONE][0]['premise']);?>
              <?php /* endif; */?>
            </td>
          </tr>
-->
          <tr>
            <td>
              <strong>Municipio:</strong>
              <?php /* if(isset()): */?>
              <?php
                if ($parent_data->field_asegurado_domicilio[LANGUAGE_NONE][0]['locality']) {
                  $town = $parent_data->field_asegurado_domicilio[LANGUAGE_NONE][0]['locality'];
                  $town = strtoupper($town);
                  print render($town);
                }
              ?>
              <?php /* endif; */?>
            </td>
          </tr>
          
          <tr>
            <td>
              <strong>C.P:</strong>
              <?php /* if(isset()): */?>
              <?php
                if ($parent_data->field_asegurado_domicilio[LANGUAGE_NONE][0]['postal_code']) {
                  $post_code = $parent_data->field_asegurado_domicilio[LANGUAGE_NONE][0]['postal_code'];
                  $post_code = strtoupper($post_code);
                  print render($post_code);
                }
              ?>
              <?php /* endif; */?>
            </td>
          </tr>
      
          <tr class="last amount">
            <td>
              <strong>Importe con Letra:</strong>
              <?php /* if(isset()): */?>
              (<?php print render($node->field_importe_con_letra_rc[LANGUAGE_NONE][0]['value']); ?>)
              <?php /* endif; */?>
            </td>
          </tr>
        </table>
      </div>
      
      <div class="col6 last">
        <table>
          <tr>
            <td> 
              <strong class="netpremium">Prima Neta:</strong>
              <?php /* if(isset()): */?>
              $<?php
                 $newRaw_payment = number_format($raw_payment, 2, '.', '');
                print render($newRaw_payment);
                 ?>
              <?php /* endif; */?>
            </td>
          </tr>
          
          <tr>
            <td> 
              <strong class="emission">Emision:</strong>
              <?php /* if(isset()): */?>
              $<?php print render($right_policy);?>
              <?php /* endif; */?>
            </td>
          </tr>
          
<!--
          <tr>
            <td> 
              <strong class="iva">I.V.A:</strong>
              <?php /* if(isset()): */?>
              $<?php $newIva = number_format($iva, 2, '.', '');
                print render($newIva);?>
              <?php /* endif; */?>
            </td>
          </tr>
-->
          
          <tr>
            <td> 
              <strong>Prima Total:</strong>
              <?php /* if(isset()): */?>
              $<?php
               $total_premium = $payment_first + $subsecuent_payment  + $iva;
                  //$total_premium = $subsecuent_payment;
                
                $total_premium = round($total_premium,2);
                $newTotal_premium = number_format($total_premium, 2,'.', '');
                print render($newTotal_premium);?>
              <?php /* endif; */?>
            </td>
          </tr>
        </table>
      </div>
  
    </div>
    <div class="payment-copy">
      <p>En caso de no realizarce el pago del recibo de contrato, este sera cancelado.</p>
      <div class="row-payment">
        <div class="number">
          <p>1.</p>
        </div>
        <div class="text">
          <p>Los pagos deberan realizarce en cualquier sucursal de Santander y en las oficnas de MN Global Protec A.C. a travez de la referencia bancaria Proporcionada.</p>
        </div>
      </div>
      <div class="row-payment">
        <div class="number">
          <p>2.</p>
        </div>
        <div class="text">
          <p>Este documento solo sera valido mediente comprovante de pago en el banco, con el sello de la compañia, o certificacion del mismo.</p>
        </div>
      </div>
      <div class="row-payment">
        <div class="number">
          <p>3.</p>
        </div>
        <div class="text">
          <p>No se aceptara el pago si el recibo ha vencido su fecha de pago.</p>
        </div>
      </div>
      <div class="row-payment">
        <div class="number">
          <p>4.</p>
        </div>
        <div class="text">
          <p>Si el pago es realizadon con cheque, este sera recibido salvo buen cobro, el cual debera extenderce a nombre de MN Global Protec A.C.</p>
        </div>
      </div>
      <div class="row-payment">
        <div class="number">
          <p>5.</p>
        </div>
        <div class="text">
          <p>Los recibos deberan pagarce segun su orden en la serie que corresponda y en el orden marcado.</p>
        </div>
      </div>
      <div class="row-payment">
        <div class="number">
          <p>6.</p>
        </div>
        <div class="text last">
          <p>Este documento no es un comprobante fiscal. Puede obtener el comprovante fiscal en las oficinas de la compania, o marcando el 01800 999 00 69 o a travez de su intermediario.</p>
        </div>
      </div>
    </div>
    <?php print render($content['links']); ?>

    <?php print render($content['comments']); ?>
  </div>
  
  <div id="main-payment-2" class="<?php print $receiptClass; ?>">

    <div class="print-header">
      <table>
        <tbody>
          <tr>
            <td class="print-logo">
              <strong>MN Global Protec A.C.</strong><br>
              Calzada Independencia  Norte No. 1131, Colonia <br>
              Independencia, Guadalajara, Jalisco, Mexico<br>
              C.P. 44290 <br>
            </td>
            <td class="print-title">
              <h1>CONCENTRACION EMPRESARIAL DE PAGO PARA USO EXCLUSIVO DEL BANCO</h1>
            </td>
          </tr>
        </tbody>
      </table>
    </div>

    <div class="recibo">
      
      <div class="col6 one">
        <table>
          <tr>
            <td>
              <div class="barcode"><?php print render($content['field_codigo_de_barras_rc'][0]['#svg']); ?></div>
              <?php print render($node->field_codigo_de_barras_rc[LANGUAGE_NONE][0]['safe_value']); ?>
            </td>
          </tr>
          <tr>
        </table>    
      </div>
      
      <div class="col6 two">
        <table>
          <tr>
            <td> 
              <strong>Serie:</strong>
              <?php /* if(isset()): */?>
              <?php print render($node->field_serie_rc[LANGUAGE_NONE][0]['value']); ?>
              <?php /* endif; */?>
              <strong>Folio del Recibo:</strong>
              <?php /* if(isset()): */?>
              <?php print render($node->title); ?>
              <?php /* endif; */?>
            </td>
          </tr>
          
          <tr>
            <td> 
              <strong>Vencimiento del Recibo:</strong>
              <?php /* if(isset()): */?>
              <?php
                if(isset($node->field_vencimiento_rc[LANGUAGE_NONE][0]['value'])) {
                  $due_date = $node->field_vencimiento_rc[LANGUAGE_NONE][0]['value'];
                  $dateFormate = getDateFormat($due_date);
                  print render($dateFormate);
                }
              ?>
              <?php /* endif; */?>
          </tr>
          
          <tr>
            <td> 
              <strong>Periodo de cobertura del:</strong>
              <?php /* if(isset()): */?>
              <?php
                $dateFormate = getDateFormat($node->field_periodo_cobertura_rc[LANGUAGE_NONE][0]['value']);
                print render($dateFormate); 
              ?>
              <?php /* endif; */?>
            </td>
          </tr>
          
          <tr>
            <td> 
              <strong class="to">al:</strong>
              <?php /* if(isset()): */?>
              <?php
                $dateFormate = getDateFormat($node->field_periodo_cobertura_rc[LANGUAGE_NONE][0]['value2']);
                print render($dateFormate); 
              ?>
              <?php /* endif; */?>
            </td>
          </tr>
          
          <tr>
            <td> 
              <strong>Contrato No:</strong>
              <?php /* if(isset()): */?>
              <?php print render($parent_data->title);?>
              <?php /* endif; */?>
            </td>
          </tr>
          
          <tr>
            <td> 
              <strong>Forma de Pago:</strong>
              <?php /* if(isset()): */?>
              <?php print render($parent_data->field_poliza_forma_pago[LANGUAGE_NONE][0]['value']);?>
              <?php /* endif; */?>
            </td>
          </tr>
          
          <tr>
            <td> 
              <strong>Tipo de Contrato:</strong>
              <?php /* if(isset()): */?>
              <?php
                 print render ($fcentity->field_poliza_tipo[LANGUAGE_NONE][0]['value']);
/*
                 foreach($keys_fc_list as $key => $value) {
                   $label_list = $field_info['settings']['allowed_values'][$value];
                   print("$label_list <br>");
                  }
*/
               ?>
            </td>
          </tr>
          
          <tr>
            <td> 
              <?php /* endif; */?>
              <strong>Moneda:</strong>
              <?php /* if(isset()): */?>
              <?php print render($parent_data->field_poliza_moneda[LANGUAGE_NONE][0]['value']);?>
              <?php /* endif; */?>
            </td>
          </tr>
        </table>
      </div>
      
      <div class="col6 three">
        <table>
          <tr>
            <td> 
              <strong>Fecha de expedicion:</strong>
              <?php /* if(isset()): */?>
              <?php
                $dateFormate = getDateFormat($node->field_fecha_de_expedicion_rc[LANGUAGE_NONE][0]['value']);
                print render($dateFormate); 
              ?>
              <?php /* endif; */?>
            </td>
          </tr>
          
          <tr>
            <td>
              <strong>Solicitante de contrato:</strong>
              <?php /* if(isset()): */?>
              <?php
                if ($parent_data->field_asegurado_nombre[LANGUAGE_NONE][0]['value']) {
                  $insured = $parent_data->field_asegurado_nombre[LANGUAGE_NONE][0]['value'];
                  $insured = strtoupper($insured);
                  print render($insured);
                }
              ?>
              <?php /* endif; */?>
            </td>
          </tr>
          
          <tr>
            <td>
              <strong>Calle y No:</strong>
              <?php /* if(isset()): */?>
              <?php
                if ($parent_data->field_asegurado_domicilio[LANGUAGE_NONE][0]['thoroughfare']) {
                  $street = $parent_data->field_asegurado_domicilio[LANGUAGE_NONE][0]['thoroughfare'];
                  $street = strtoupper($street);
                  print render($street);
                }
              ?>
              <?php /* endif; */?>
            </td>
          </tr>
          
<!--
          <tr>
            <td>
              <strong>Colonia:</strong>
              <?php /* if(isset()): */?>
              <?php print render($parent_data->field_asegurado_domicilio[LANGUAGE_NONE][0]['premise']);?>
              <?php /* endif; */?>
            </td>
          </tr>
-->
          <tr>
            <td>
              <strong>Municipio:</strong>
              <?php /* if(isset()): */?>
              <?php
                if ($parent_data->field_asegurado_domicilio[LANGUAGE_NONE][0]['locality']) {
                  $town = $parent_data->field_asegurado_domicilio[LANGUAGE_NONE][0]['locality'];
                  $town = strtoupper($town);
                  print render($town);
                }
              ?>
              <?php /* endif; */?>
            </td>
          </tr>
          
          <tr>
            <td>
              <strong>C.P:</strong>
              <?php /* if(isset()): */?>
              <?php
                if ($parent_data->field_asegurado_domicilio[LANGUAGE_NONE][0]['postal_code']) {
                  $post_code = $parent_data->field_asegurado_domicilio[LANGUAGE_NONE][0]['postal_code'];
                  $post_code = strtoupper($post_code);
                  print render($post_code);
                }
              ?>
              <?php /* endif; */?>
            </td>
          </tr>
      
          <tr class="last amount">
            <td>
              <strong>Importe con Letra:</strong>
              <?php /* if(isset()): */?>
              (<?php print render($node->field_importe_con_letra_rc[LANGUAGE_NONE][0]['value']); ?>)
              <?php /* endif; */?>
            </td>
          </tr>
        </table>
      </div>
      
      <div class="col6 last">
        <table>
          <tr>
            <td> 
              <strong class="netpremium">Prima Neta:</strong>
              <?php /* if(isset()): */?>
              $<?php 
                $newRaw_payment = number_format($raw_payment, 2, '.', '');
                print render($newRaw_payment);
                
              ?>
              <?php /* endif; */?>
            </td>
          </tr>
          
          <tr>
            <td> 
              <strong class="emission">Emision:</strong>
              <?php /* if(isset()): */?>
              $<?php print render($right_policy);?>
              <?php /* endif; */?>
            </td>
          </tr>
          
<!--
          <tr>
            <td> 
              <strong class="iva">I.V.A:</strong>
              <?php /* if(isset()): */?>
              $<?php 
                $newIva = number_format($iva, 2, '.', '');
                print render($newIva);?>
              <?php /* endif; */?>
            </td>
          </tr>
-->
          
          <tr>
            <td> 
              <strong>Prima Total:</strong>
              <?php /* if(isset()): */?>
              $<?php
                  $total_premium = $payment_first + $subsecuent_payment  + $iva;
                  //$total_premium = $subsecuent_payment;
                
                $total_premium = round($total_premium,2);
                $newTotal_premium = number_format($total_premium, 2,'.', '');
                print render($newTotal_premium);?>
              <?php /* endif; */?>
            </td>
          </tr>
        </table>
      </div>
  
    </div>


</div>