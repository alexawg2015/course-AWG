<?php

class myhandler_views_handler_filter_string extends views_handler_filter_string {
  function operators() {
  //оставляем только 1 оператор, чтобы искать теги внутри списка (в таблице они через запятую)
    $operators = array(
      'word' => array(
        'title' => t('Contains any tags'),
        'short' => t('has tags'),
        'method' => 'op_word',
        'values' => 1,
      ),
    );
    // if the definition allows for the empty operator, add it.
    if (!empty($this->definition['allow empty'])) {
      $operators += array(
        'empty' => array(
          'title' => t('Is empty (NULL)'),
          'method' => 'op_empty',
          'short' => t('empty'),
          'values' => 0,
        ),
        'not empty' => array(
          'title' => t('Is not empty (NOT NULL)'),
          'method' => 'op_empty',
          'short' => t('not empty'),
          'values' => 0,
        ),
      );
    }
    // Add regexp support for MySQL.
    if (Database::getConnection()->databaseType() == 'mysql') {
      $operators += array(
        'regular_expression' => array(
          'title' => t('Regular expression'),
          'short' => t('regex'),
          'method' => 'op_regex',
          'values' => 1,
        ),
      );
    }
    return $operators;
  }

}
