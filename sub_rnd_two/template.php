<?php
/**
 * Returns HTML for a checkbox form element.
 */
function sub_rnd_two_checkbox($variables) {
  //add my class to checkbox
  $variables['element']['#attributes']['class'][] = 'my-checkbox';
  return theme_checkbox($variables);
}