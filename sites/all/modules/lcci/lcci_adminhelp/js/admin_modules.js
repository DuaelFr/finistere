$(document).ready(function(){
	$("a.lcci-toogle-all-packages").click(function(){
		lccitoogle();
	});
});

function lccitoogle(){
	$("#page #content .form .fieldset.collapsible").addClass('collapsed');
	$("a.lcci-toogle-all-packages").removeClass("lcci-toogle-all-packages").addClass("lcci-expand-all-packages").html('Expand all').click(function(){
		lccicollapse();
	});
}

function lccicollapse(){
	$("#page #content .form .fieldset.collapsible").removeClass('collapsed');
	$("a.lcci-expand-all-packages").removeClass("lcci-expand-all-packages").addClass("lcci-toogle-all-packages").html('Toogle all').click(function(){
		lccitoogle();
	});
}