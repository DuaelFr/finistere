
/**
 * Edited by Fabien CLEMENT : http://blog.fclement.info
 */

// THIS IS REALLY FREAKING BIZARRE 
    // I SHOULD NOT HAVE TO DO THIS BUT IE (6 & 7) ARE PRETTY MESSED UP.
	//var height_content = $('#content').height();
	/*
	 * MAGICAL SCROLLING NAV
	 * (not that magical)
	 * 
 	 * This is using lots of vars because it gets called all the time 
 	 * on scroll, so it needs to be fast.
	 */
$(document).ready(function(){
	var COLUMNWRAPPER = $('#content .column-side .column-wrapper');

	if(COLUMNWRAPPER.length){		
		
		var CONTENTWRAPPER = $('#content > .content-wrapper');
		var COLUMNSIDE = $('#content > .content-wrapper .column-side');

		var nav = COLUMNWRAPPER;
		
	  var ORIGINAL_LEFT = COLUMNSIDE.css('margin-left');
		var PADDING_TOP = 63; // MAGIC NUMBER
	  
		var the_window = $(window);
		var NAV_IS_FIXED = (nav.css('position') == 'fixed');
		the_window.scroll(function () {
			var topmost_point = nav.offset().top;
	  	var left_point = COLUMNWRAPPER.offset().left;
			var WIDTH_BOX = COLUMNWRAPPER.width();

			var SCROLL_TOP = the_window.scrollTop();
			var menu_top = 0;
			
			var REAL_TOP = COLUMNSIDE.offset().top + menu_top;
			var number = CONTENTWRAPPER.height() + COLUMNSIDE.offset().top - COLUMNWRAPPER.height();

	    if (SCROLL_TOP > REAL_TOP && SCROLL_TOP < CONTENTWRAPPER.height() + COLUMNSIDE.offset().top - COLUMNWRAPPER.height() ) {
				// Scroll my box
				if ($.browser.msie && $.browser.version == "6.0") {
					nav.css('top', SCROLL_TOP + PADDING_TOP);
				} else if (!NAV_IS_FIXED) {
					nav.css({
						left: left_point,
						top: 10,
						position: 'fixed',
						width: WIDTH_BOX + 'px'
					});
					NAV_IS_FIXED = true;
				}
			
			}else if(SCROLL_TOP > CONTENTWRAPPER.height() + COLUMNSIDE.offset().top - COLUMNWRAPPER.height()){
				// Let my box DOWN
				NAV_IS_FIXED = false;
				nav.css({
					position: 'absolute',
					top: CONTENTWRAPPER.height() - COLUMNWRAPPER.height(),
					left: ORIGINAL_LEFT
				});
				
			} else {
				// Let my Box UP as it was
				if (NAV_IS_FIXED) {
					/*nav.css({
						position: 'absolute',
						top: $('.menu-block-1 > ul').height() + 10,
						left: 22
					});*/
					nav.css({position:'relative',float: 'left',left:0, top:menu_top});
					NAV_IS_FIXED = false;
				}
			}
		});
		
		the_window.resize(function () {
		    left_point = $('.last').offset().left;
		    if (NAV_IS_FIXED) {
	    	    nav.css('left', left_point);	        
		    }
		});
		
		COLUMNSIDE.css('margin-bottom', COLUMNWRAPPER.height());
	
	}
});