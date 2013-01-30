/*
 * @File:        jquery.gnova-formlabels.js
 * @Version:     1.0
 * @Author:      Fabien CLEMENT (fabien.clement@g-nova.fr)
 *
 * @Requires:    jQuery v1.4++
 */

$(document).ready(function(){
	$('input[title]').each(function() {
		if($(this).val() === '') {
			$(this).val($(this).attr('title'));	
		}
		
		$(this).focus(function() {
			if($(this).val() == $(this).attr('title')) {
				$(this).val('').addClass('focused');	
			}
		});
		$(this).blur(function() {
			if($(this).val() === '') {
				$(this).val($(this).attr('title')).removeClass('focused');	
			}
		});
	});
	
	$('textarea[title]').each(function() {
		if($(this).html() === '') {
			$(this).html($(this).attr('title'));	
		}
		
		$(this).focus(function() {
			if($(this).html() == $(this).attr('title')) {
				$(this).html('').addClass('focused');	
			}
		});
		$(this).blur(function() {
			if($(this).html() === '') {
				$(this).html($(this).attr('title')).removeClass('focused');	
			}
		});
	});
	
	$('form').submit(function(){
		$('input', this).each(function(){
			if($(this).val() == $(this).attr('title')) {
				$(this).val('');	
			}
		});
		$('textarea', this).each(function(){
			if($(this).html() == $(this).attr('title')) {
				$(this).html('');	
			}
		});
	});
});