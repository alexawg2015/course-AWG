<?php

class myhandler_views_handler_field_markup extends views_handler_field {
  function render($values) {
    $value = $this->get_value($values);
    if ($value) {
      //выводим теги отсортированными, каждый с новой строки курсивом.
      $value = explode(", ", $value);
      sort($value);
      $value = '<i>' . implode('</i>,<br><i>', $value) . '</i>';
      return $value;
    }
  }
}