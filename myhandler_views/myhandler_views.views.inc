<?php

/**
 * Реализация hook_views_data()
 */
function myhandler_views_views_data() {
  $data ['myhandler_views']['table']['group'] = t('myhandler_views');

  $data ['myhandler_views']['table']['base'] = array(
    'field' => 'id', // This is the identifier field for the view.
    'title' => t('My test table'),
    'help' => t('My test table for my handlers'),
    'weight' => -10,
  );
  $data ['myhandler_views']['table']['join'] = array(
    'node' => array(
      'left_field' => 'nid',
      'field' => 'nid',
    ),
  );
  $data ['myhandler_views']['nid'] = array(
    'title' => t('nid'),
    'help' => t('content that references a node.'),
    'relationship' => array(
      'base' => 'node',
      'base field' => 'nid',
      'handler' => 'views_handler_relationship',
      'label' => t('Default label for the relationship'),
      'title' => t('Title shown when adding the relationship'),
      'help' => t('More information on this relationship'),
    ),
  );

  $data ['myhandler_views']['id'] = array(
    'title' => t('id registration'),
    'help' => t('id registration'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );

  $data ['myhandler_views']['date_registr'] = array(
    'title' => t('date registration'),
    'help' => t('date registration'),
    'field' => array(
      'handler' => 'views_handler_field_date',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort_date',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_date',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_date',
    ),
  );

  //подключаем свои хандлеры для этого поля
  $data ['myhandler_views']['tags'] = array(
    'title' => t('tags'),
    'help' => t('list of tags'),
    'field' => array(
      'handler' => 'myhandler_views_handler_field',
    ),
    'filter' => array(
      'handler' => 'myhandler_views_handler_filter_string',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );

  return $data;
}
