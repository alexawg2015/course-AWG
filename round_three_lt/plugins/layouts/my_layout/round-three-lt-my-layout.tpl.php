<?php
/**
 * @file   round-three-lt-my-layout.tpl.php
 */
?>
<div class="panel-display clearfix" <?php if (!empty($css_id)) {
  print "id=\"$css_id\"";
} ?>>

  <div id="my-layout-content-top" class="clearfix">
    <div class="section clearfix">
      <?php print $content['top']; ?>
    </div>
  </div>
  <div id="my-layout-content-main" class="clearfix">
    <div id="my-layout-content">
      <div class="section clearfix">
        <?php print $content['main']; ?>
      </div>
    </div>

    <div id="my-layout-right">
      <div class="section clearfix">
        <?php print $content['right']; ?>
      </div>
    </div>
  </div>
  <div id="my-layout-content-bottom" class="clearfix">
    <div class="section clearfix">
      <?php print $content['bottom']; ?>
    </div>
  </div>
</div>