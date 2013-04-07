<!--/there can't be a space between the input field and the button or IE adds unwanted margins -->
<input type="text" name="search_theme_form" id="search-input" class="text"
       value="" title="<?php print t('Search'); ?>"/>
<input type="submit" name="op" id="edit-submit-button"
       value="<?php print t('Search'); ?>" title="<?php print t('Search'); ?>"
       class="form-submit"/>
<input type="hidden" name="form_build_id"
       id="<?php print drupal_get_token('form_build_id'); ?>"
       value="<?php print drupal_get_token('form_build_id'); ?>"/>
<input type="hidden" name="form_token" id="edit-search-theme-form-form-token"
       value="<?php print drupal_get_token('search_theme_form'); ?>"/>
<input type="hidden" name="form_id" id="edit-search-theme-form"
       value="search_theme_form"/>
