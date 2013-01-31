$(document).ready(function(){
	$(".view-filters.autosubmit form .form-item select").change(function(){
		submit_and_reappend_action(this);
	});
});

function submit_and_reappend_action(elt){
	$(elt).closest("form").submit();
}