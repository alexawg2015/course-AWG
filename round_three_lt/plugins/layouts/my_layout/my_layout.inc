<?php
/**
 * @file   my_layout.inc
 */

$plugin = array(
  'title' => t('My Layout flex/300'),
  'category' => t('Columns: 2'),
  'icon' => 'my_layout.png',
  'theme' => 'round_three_lt_my_layout',
  'css' => 'my_layout.css',
  'regions' => array(
    'top' => t('Top region'),
    'main' => t('Main region'),
    'right' => t('Right region'),
    'bottom' => t('Bottom region'),
  ),
);