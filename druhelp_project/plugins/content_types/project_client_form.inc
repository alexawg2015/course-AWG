<?php


/**
 * Plugins are described by creating a $plugin array which will be used
 * by the system that includes this file.
 */
$plugin = array(
  'title' => t('Project client form'),
  'description' => t('ctools content types - roject client form'),
  'single' => TRUE,
  'content_types' => array('no_context_content_type'),
  'render callback' => 'druhelp_project_client_form_block_render',
  'defaults' => array(),
  'icon' => 'favicon.ico',
  'category' => array('druhelp', -9),
  'edit form' => 'druhelp_project_client_form_content_type_edit_form',
);

/**
 * the block with user ticket's form.
 *
 */
function druhelp_project_client_form_block_render($subtype, $conf, $args, $context) {
  $block = new stdClass();
  $block->title = check_plain("Add project");
  module_load_include('inc', 'alpha_project', 'includes/alpha_project.admin');
  $form = druhelp_project_alpha_project_prepare_form('alpha_project', 'support', $conf);
  $block->content = $form;
  return $block;
}

function druhelp_project_alpha_project_prepare_form($entity_type, $bundle_name, $conf) {
  $info = entity_get_info($entity_type);
  $bundle_key = $info['entity keys']['bundle'];

  if (!$bundle_key) {
    $options = array();
  }
  else {
    $options = array($bundle_key => $bundle_name);
  }
  $entity = entity_create($entity_type, $options);

  return drupal_get_form($entity_type . '_form', $entity, $conf);
}




function druhelp_project_client_form_content_type_edit_form($form, &$form_state) {
  $conf = $form_state['conf'];
  $form['project_redirect_admin'] = array(
    '#type' => 'textfield',
    '#title' => t('Link of redirect for admin'),
    '#default_value' => empty($conf['project_redirect_admin']) ? '' : $conf['project_redirect_admin'],
    '#size' => 60,
    '#maxlength' => 128,
    '#required' => TRUE,
  );
  $form['project_redirect_client'] = array(
    '#type' => 'textfield',
    '#title' => t('Link of redirect for client'),
    '#default_value' => empty($conf['project_redirect_client']) ? '' : $conf['project_redirect_client'],
    '#size' => 60,
    '#maxlength' => 128,
    '#required' => TRUE,
  );
  return $form;
}


function druhelp_project_client_form_content_type_edit_form_submit($form, &$form_state) {
  foreach (element_children($form) as $key) {
    if (!empty($form_state['values'][$key])) {
      $form_state['conf'][$key] = $form_state['values'][$key];
    }
  }
}

function druhelp_project_form_alpha_project_form_alter(&$form, &$form_state, $form_id) {
  if (!user_access('Create projects of any type')) {
    $form['uid']['#type'] = 'hidden';
    $form['uid']['#value'] = $form['uid']['#default_value'];
    $form['status']['#type'] = 'hidden';
    $form['status']['#value'] = 1;
    global $user;

    if($spacework = druhelp_project_get_spacework_by_uid($user->uid)){
      $form['field_project_workspace_ref']['und'][0]['target_id']['#type'] = 'hidden';
      $form['field_project_workspace_ref']['und'][0]['target_id']['#value'] = $spacework['id'];
      $form['field_project_workspace_ref']['und'][0]['target_id']['#element_validate'] = array();
    }

//Workspace, Status, Project Owner

  }
  $form ['#submit'][] = 'druhelp_project_client_form_submit';
}

function druhelp_project_client_form_submit($form, &$form_state) {
  if(!empty($form_state['conf'])){
    $conf = $form_state['conf'];
    if (user_access('Create projects of any type')) {
      $path = $conf['project_redirect_admin'];
    }
    else {
      $path = $conf['project_redirect_client'];
    }
    if ($path) {
      $form_state['redirect'] = $path;
    }
  }
}