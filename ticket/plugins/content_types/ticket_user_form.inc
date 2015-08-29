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
  'edit form' => 'ticket_user_form_content_type_edit_form',
);

/**
 * the block with user ticket's form.
 *
 */
function ticket_user_form_block_render($subtype, $conf, $args, $context) {
  $block = new stdClass();
  $block->title = check_plain("Ticket form");
  $entity = entity_get_controller('ticket')->create();
  $form_state['build_info']['args'] = array($entity);
  $form_state['conf'] = $conf;
  $form = drupal_build_form('ticket_form', $form_state);
//  $form = drupal_get_form('ticket_form', $entity);
  $block->content = $form;
  return $block;
}


function ticket_user_form_content_type_edit_form($form, &$form_state) {
  $conf = $form_state['conf'];
  $form['ticket_redirect_admin'] = array(
    '#type' => 'textfield',
    '#title' => t('Link of redirect for admin'),
    '#default_value' => empty($conf['ticket_redirect_admin']) ? '' : $conf['ticket_redirect_admin'],
    '#size' => 60,
    '#maxlength' => 128,
    '#required' => TRUE,
  );
  $form['ticket_redirect_user'] = array(
    '#type' => 'textfield',
    '#title' => t('Link of redirect for user'),
    '#default_value' => empty($conf['ticket_redirect_user']) ? '' : $conf['ticket_redirect_user'],
    '#description' => 'use %ticket for id_ticket',
    '#size' => 60,
    '#maxlength' => 128,
    '#required' => TRUE,
  );
 /*
  * ниже форма для автоматического заполнения мероприятия.
  * Например. Мы создаём словарь "Мероприятия" и добавляем поле Term Referance к нашему ticket.
  * Теперь при добавление формы тикета из плагина нам достаточно указать название этого поля и ИД мероприятия.
  * Когда пользователь будет заказывать билет на этой странице, данное поле заполнится автоматически.
  * Пользователю данное поле не будет показано.
  */
  $form['auto_complete'] = array(
    '#type' => 'fieldset',
    '#title' => t('Auto-complete field'),
  );

  $form['auto_complete']['ticket_name_field_place'] = array(
    '#type' => 'textfield',
    '#title' => t('Ticket name field for place'),
    '#default_value' => empty($conf['ticket_name_field_place']) ? '' : $conf['ticket_name_field_place'],
    '#size' => 60,
    '#maxlength' => 128,
  );
  $form['auto_complete']['ticket_place'] = array(
    '#type' => 'textfield',
    '#title' => t('Id place'),
    '#default_value' => empty($conf['ticket_place']) ? 0 : $conf['ticket_place'],
    '#size' => 60,
    '#maxlength' => 128,
  );

  return $form;
}

function ticket_user_form_content_type_edit_form_validate($form, &$form_state) {
  $item = &$form_state['values'];
  $my_links = array(
    'ticket_redirect_admin',
    'ticket_redirect_user'
  );
  foreach ($my_links as $my_link) {
    if (strpos($item[$my_link], '%ticket')) {
      continue;
    }
    if (!trim($item[$my_link]) || !drupal_valid_path($item[$my_link], TRUE)) {
      form_set_error($my_link, t("The path '@link_path' is either invalid or you do not have access to it.", array('@link_path' => $item[$my_link])));
    }
  }
}

function ticket_user_form_content_type_edit_form_submit($form, &$form_state) {
  foreach (element_children($form) as $key) {
    if (!empty($form_state['values'][$key])) {
      $form_state['conf'][$key] = $form_state['values'][$key];
    }
  }
}

function ticket_form_ticket_form_alter(&$form, &$form_state, $form_id) {
  $conf = $form_state['conf'];
  if(!empty($conf['ticket_name_field_place']) && isset($form[$conf['ticket_name_field_place']])){
    $form[$conf['ticket_name_field_place']]['und']['#type'] = 'hidden';
    $form[$conf['ticket_name_field_place']]['und']['#value'] = $conf['ticket_place'];
  }
  $form ['#submit'][] = 'ticket_user_form_content_type_submit';
}

function ticket_user_form_content_type_submit($form, &$form_state) {
  if(!empty($form_state['conf'])){
    $conf = $form_state['conf'];
    if (user_access('administer ticket entities')) {
      $path = $conf['ticket_redirect_admin'];
    }
    else {
      $path = $conf['ticket_redirect_user'];
    }
      //если в настройках панели пути не были указаны, то redirect согласно глобальных настроек
    if ($path) {
      if (strpos($path, '%ticket')) {
        $entity = $form_state['entity'];
        $path = str_replace('%ticket', $entity->tid, $path);
      }
      $form_state['redirect'] = $path;
    }
  }
}