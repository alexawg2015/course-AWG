<?php
/**
 * Plugins are described by creating a $plugin array which will be used
 * by the system that includes this file.
 */
$plugin = array(
  'title' => t('Ticket form for user.'),
  'description' => t('ctools content types - Ticket form for user'),
  'single' => TRUE,
  'content_types' => array('no_context_content_type'),
  'render callback' => 'ticket_user_form_block_render',
  'defaults' => array(),
  'icon' => 'favicon.ico',
  'category' => array('Ticket', -9),
);

/**
 * the block with user ticket's form.
 *
 */
function ticket_user_form_block_render($subtype, $conf, $args, $context) {
  $block = new stdClass();
  $block->title = check_plain("Ticket form");
  $entity = entity_get_controller('ticket')->create();
  $form = drupal_get_form('ticket_form', $entity);
  $block->content = $form;
  return $block;
}