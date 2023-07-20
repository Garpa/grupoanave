<table class="print coberturas">
  <thead>
    <tr>
      <th colspan="3">Tipo de Contrato:</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <td colspan="3">
        <?php print render($elements['field_poliza_tipo']);?>
      </td>
    </tr>
  </tbody>
  <thead>
    <tr>
      <th>Coberturas:</th>
      <th>Deducibles:</th>
      <th>Limites:</th>
    </tr>
  </thead>
  <tbody>
    <?php print render($elements['field_cobertura']);?>
  </tbody>
</table>
