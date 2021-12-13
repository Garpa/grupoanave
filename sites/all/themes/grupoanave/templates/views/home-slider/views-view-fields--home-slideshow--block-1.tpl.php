<?php

/**
 * @file
 * Default simple view template to all the fields as a row.
 *
 * - $view: The view in use.
 * - $fields: an array of $field objects. Each one contains:
 *   - $field->content: The output of the field.
 *   - $field->raw: The raw data for the field, if exists. NOT output safe.
 *   - $field->class: The safe class id to use.
 *   - $field->handler: Views field handler controlling this field. Don't use
 *     var_export to dump this object, as it can't handle the recursion.
 *   - $field->inline: Whether or not the field should be inline.
 *   - $field->inline_html: either div or span based on the above flag.
 *   - $field->wrapper_prefix: A wrapper containing the inline_html to use.
 *   - $field->wrapper_suffix: The closing tag for the wrapper.
 *   - $field->separator: an optional separator that may appear before a field.
 *   - $field->label: The wrap label text to use.
 *   - $field->label_html: The full HTML of the label to use including
 *     configured element type.
 * - $row: The raw result object from the query, with all data it fetched.
 *
 * @ingroup views_templates
 */
 $title = $fields['title']->content;
 $image = $fields['field_image']->content;
 $des = $fields['field_description']->content;
?>
<div class="layout-wrapper">
  <div class="info">
    <h3><?php print $title;?><span class="des"><?php print $des;?></span></h3>
  </div>
</div>
<div class="image">
  <?php print $image;?>
</div>
