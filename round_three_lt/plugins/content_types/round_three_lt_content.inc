<?php
/**
 * Plugins are described by creating a $plugin array which will be used
 * by the system that includes this file.
 */
$plugin = array(
  'title' => t('Round three. My form.'),
  'description' => t('My ctools content types'),
  'single' => TRUE,
  'content_types' => array('no_context_content_type'),
  'render callback' => 'round_three_lt_block_render',
  'defaults' => array(),
  'icon' => 'favicon.ico',
  'category' => array('Round three', -9),
);

/**
 * Run-time rendering of the body of the block.
 *
 * @param $subtype
 * @param $conf
 *   Configuration as done at admin time.
 * @param $args
 * @param $context
 *   Context - in this case we don't have any.
 *
 * @return
 *   An object with at least title and content members.
 */
function round_three_lt_block_render($subtype, $conf, $args, $context) {
  $block = new stdClass();
  $block->title = check_plain("Round three. My form.");
  $form_state['build_info']['args'] = array();
  $form = drupal_build_form('curse_two_form', $form_state); //form from round two
  $block->content = $form;
  return $block;
}
