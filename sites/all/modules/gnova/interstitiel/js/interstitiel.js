/**
 * Object init
 */
Drupal.settings.interstitiel = Drupal.settings.interstitiel || {}
Drupal.interstitiel = Drupal.interstitiel || {}

Drupal.interstitiel.block_interstitiel = function(element) {
  element
    .addClass('block-interstitiel-processed')
  var datas = { js: true };
  jQuery.ajax({
      type: 'GET',
      url: '/ajax/interstitiel/'+Drupal.settings.interstitiel.ad,
      data: datas,
      dataType: 'json',
      success: function (data) {
        if(data.ad){
          $("#block_interstitiel").fadeIn();
          $("html").css({
          	'overflow':'hidden'
          });
        }
      },
      error: function (xmlhttp) {}
  });
  $("#block_interstitiel").find('.close').live('click', function(){
  	$("#block_interstitiel").fadeOut(function(){
  		$("html").css({
          	'overflow':'visible'
          });
  	});
  });
  
  $("#block_interstitiel").find('.node').mouseleave(function(){
  	$("#block_interstitiel").click(function(){
	  	$("#block_interstitiel").fadeOut(function(){
	  		$("html").css({
	          	'overflow':'visible'
	          });
	  	});
	  });
  });

} // Drupal.interstitiel.block_interstitiel

Drupal.behaviors.interstitiel = function(context) {
  $('#block_interstitiel:not(.block-interstitiel-processed)', context).each(function(){
    Drupal.interstitiel.block_interstitiel($(this));
  });
}