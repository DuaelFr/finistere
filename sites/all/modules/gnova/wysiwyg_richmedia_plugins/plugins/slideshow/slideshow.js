// $Id$
 
(function ($) {
 
Drupal.wysiwyg.plugins['slideshow'] = {
 
  /**
   *	Dialog object
   */
  dialog: null,
  
  /**
   *	String content
   */
  content: '',
  
  /**
   *	Array contents
   */
  contents: new Array(),
  
  /**
   * Return whether the passed node belongs to this plugin (note that "node" in this context is a JQuery node, not a Drupal node).
   *
   * We identify code managed by this FOO plugin by giving it the HTML class
   * 'wysiwyg_richmedia_slideshow'.
   */
  isNode: function(node) {
    res = $(node).is('img.wysiwyg_richmedia_slideshow');
    return ($(node).is('img.wysiwyg_richmedia_slideshow'));
  },
  
  init: function(comments){
  	if ( comments != null) {
			for ( i = 0; i < comments.length; i++ ) {
				var comment = comments[i];
				this.contents.push(this._getContentFromComment(comment));
			}
		}
  },
 
  /**
   * Invoke is called when the toolbar button is clicked.
   */
  invoke: function(data, settings, instanceId) {
     // Typically, an icon might be added to the WYSIWYG, which HTML gets added
     // to the plain-text version.
     
     // CALL IMCE :
     //	window.open('/imce?app=myApp|imceload@initiateMyApp', '', 'width=760,height=560,resizable=1');
      
      // Check if content already exist
      if (this.isNode(data.node)) { 
      	this._setContentFromImage(data.node);
      }
      
      // Build Dialog fo first time
      this._createDialog();

      this.settings = settings;
      
      var _this = this;
      
			$('#wysiwyg-richmedia-slideshow-submit').click(function(){
	      _this.submit(data, settings, instanceId);			
			});
			
			$('#wysiwyg-richmedia-slideshow-cancel').click(function(){
		  	_this._destroyDialog();
			});
					
	  	// Add Fieldset Bundle when click on Adding Bundle button
	  	$('#wysiwyg-richmedia-slideshow-addBundle-button').click(function(){
	  		$('#wysiwyg-richmedia-slideshow-bundleRecipient').append(_this._createFieldsetBundle(new Array()));
	  	});
   },

	/**
	 * Submit action
	 */
	submit: function(data, settings, instanceId){
		this.content = this._getContent();
    this.contents.push(this.content);
		if (data.format == 'html') {
			var content = this._getPlaceholder(settings, this.contents.length-1);
		}else{
			var content = this.content;
		}
		if (typeof content != 'undefined') {
			Drupal.wysiwyg.instances[instanceId].insert(content);
		}
		
  	this._destroyDialog();
	},

  /**
   * Replace all <!--wysiwyg_richmedia_slideshow--> tags with the icon.
   */
  attach: function(content, settings, instanceId) {
		
  	var comments = content.match(/<!--wysiwyg_richmedia_slideshow-[0-9]+(\[.+?\])-->/g);

	  // Check if it's first invoke
	  if(comments != null && this.contents.length == 0 && comments.length > 0){
	  	this.init(comments);
	  }
	  
	  content = content.replace( new RegExp("<!--wysiwyg_richmedia_slideshow-([0-9]+).+?-->", "g"), this._getPlaceholder1(settings) );

    return content;
  },
 	
  /**
   * Replace the icons with <!--wysiwyg_richmedia_slideshow--> tags in content upon detaching editor.
   */
  detach: function(content, settings, instanceId) {
  	var _this = this;
    var $content = $('<div>' + content + '</div>');
    $.each($('img.wysiwyg_richmedia_slideshow', $content), function (i, elem) {
    	var commentNumber = $(this).attr('alt').match(new RegExp("[0-9]+", "g"))[0];
    	//var content = _this.contents[commentNumber];
    	//var data = _this._arrayToTube(content);
    	var data = _this.contents[commentNumber];
      elem.parentNode.insertBefore(document.createComment($(this).attr('alt')+data), elem);
      elem.parentNode.removeChild(elem);
    });
    return $content.html();
  },
 	
 	/**
   * Helper function to return a HTML placeholder.
   *
   * Here we provide an image to visually represent the hidden HTML in the Wysiwyg editor.
   */
  _getPlaceholder1: function (settings) {
    return '<img src="' + settings.path + '/images/slideshow.content.png" alt="wysiwyg_richmedia_slideshow-$1" title="&lt;--wysiwyg_richmedia_slideshow--&gt;" class="wysiwyg_richmedia_slideshow drupal-content" />';
  },  
 	
  /**
   * Helper function to return a HTML placeholder.
   *
   * Here we provide an image to visually represent the hidden HTML in the Wysiwyg editor.
   */
  _getPlaceholder: function (settings, contentNumber) {
    return '<img src="' + settings.path + '/images/slideshow.content.png" alt="wysiwyg_richmedia_slideshow-' + contentNumber + '" title="&lt;--wysiwyg_richmedia_slideshow--&gt;" class="wysiwyg_richmedia_slideshow drupal-content" />';
  },  
  
  /**
   *	Transform array to tube string
   *	@param Array : contents
   *  @return String : contents separated by tube
   */
  _arrayToTube: function(contents){
  	var string = "";
  	if(contents != null){
  		for(var i = 0; i < contents.length; i++){
  			if(string != ""){
  				string += "|";
  			}
	  		string += contents[i];
  		}
  	}
  	return string;
  },
  
  /**
   *	Generate and display dialog window
   */
  _createDialog: function () {
  	
  	// Buttons
  	var $submit = this._createTag('input', {'type':'button', 'value':Drupal.t('Submit'), 'id':'wysiwyg-richmedia-slideshow-submit', 'class':'form-submit'});
  	var $cancel = this._createTag('input', {'type':'button', 'value':Drupal.t('Cancel'), 'id': 'wysiwyg-richmedia-slideshow-cancel', 'class':'form-submit'});
  	var $submitBundleDiv = this._createTag('div', {'id':'wysiwyg-richmedia-slideshow-submitBundle', 'class':'buttons'}, [$cancel, $submit]);

  	
  	// Add fieldset button
  	var $addBundleButton = this._createTag('input', {'type':'button', 'value':Drupal.t('Add new image'), 'id':'wysiwyg-richmedia-slideshow-addBundle-button', 'class':'form-submit'});
  	var $addBundleDiv = this._createTag('div', {'id':'wysiwyg-richmedia-slideshow-addBundle', 'class':'buttons'}, $addBundleButton);
  	
  	// Bundle Recipient
  	var $bundleRecipient = this._createTag('div', {'id':'wysiwyg-richmedia-slideshow-bundleRecipient'});
  	
  	// Add a fieldset per existant values
  	var aValues = this._getValues();

  	if(aValues != null && aValues.length > 0){
  		for(var i= 0; i < aValues.length ; i++){
  			$bundleRecipient.append(this._createFieldsetBundle(aValues[i]));
  		}
  	}else{ // Or add empty fieldset
  		$bundleRecipient.append(this._createFieldsetBundle(new Array()));
  	}
  	
  	var $dialog = this._createTag('div', {'id':'dialog-wysiwyg-richmedia-slideshow'}, [$bundleRecipient, $addBundleDiv, $submitBundleDiv]);
  	
  	// Call dialog box
  	$dialog.dialog({
      title: Drupal.t('Wysiwyg Richmedia Slideshow'),
      modal: true
    });
    
    this.dialog = $dialog;
  },
  
  /**
   *	Destroy
   */
  _destroyDialog: function () {
  	this.dialog.dialog('destroy');
  	this.dialog.remove();
  	this.dialog = null;
  },
  
  /**
   * GetContent to display
   */
  _getContent: function(){
  	var content = "";
  	$('.wysiwyg_richmedia_slideshow_image_fieldset').each(function(){
  		var src = $(this).find('input[name|="wysiwyg_richmedia_slideshow_image_src"]').val();
  		var imageDesc = $(this).find('input[name|="wysiwyg_richmedia_slideshow_image_description"]').val();
  		var description = $(this).find('textarea[name|="wysiwyg_richmedia_slideshow_text_description"]').val();
  		var href = $(this).find('input[name|="wysiwyg_richmedia_slideshow_image_href"]').val();
  		
  		// escape '"' and ';' characters
  		src.replace('"', '\\\"');
  		imageDesc.replace('"', '\\\"');
  		description.replace('"', '\\\"');
  		href.replace('"', '\\\"');
  		
  		var data = '"' + src + '","' + imageDesc + '","' + description + '","' + href + '"';
  		
  		if(content.length)
  			content += "|" + data;
  		else
  			content = data;
  		
  	});
  	
  	content = "[" + content + "]";
  	return content;
  },
  
  /**
   *	Helper to get content form comment
   *	@param String comment
   *	@return String content
   */
  _getContentFromComment: function(comment){
  	var commentData = comment.match(/\[.+?\]/g);
  	return commentData;
  },
  
  /**
   *	Helper to set content form image
   *	@param String image
   */
  _setContentFromImage: function(image){
  	var alt = $(image).attr('alt');
  	var isset = alt.replace('wysiwyg_richmedia_slideshow-','');
  	this.content = this.contents[isset];
  },
  
  /**
   *	Helper to get values from current content
   *	@return String content
   */
  _getValues: function(){
  	var values = new Array();

  	if(this.content[0]){
  		// Split multiple images information
	  	var re= new RegExp ('\\[(.+?)\\]',"igm");
	  	var commentData = re.exec(this.content[0]);
	  	if(commentData != null){
		  	commentData = commentData[1];

		  	var datas = commentData.split('|');
		  	if(datas != null){
		  		
		  		// For each image information, get each data (description, href, url etc)
		  		for (var i = 0; i < datas.length; i++ ) {
		  			var re= new RegExp ('^"(.*)","(.*)","(.*)","(.*)"$',"igm");
						var data = re.exec(datas[i]);
	
						if(data != null && data.length > 1){
				  		data.shift();
				  	}
				  	if(data != null && data.length > 0){			  		
							values.push(data);
						}
					}
		  	}
		  }
		}
  	return values;
  },  
  
  /**
   *	Helper to build Tags
   *  @param 
   *		String name : Tag name
   *		Map attributes : Attributes of tag
   *		Jquery Object or String content : Content of tag
   *	@return Jquery Object
   */
  _createTag: function(name, attributes, content){
  	var $input = $('<' + name + '>'); 
	  $input.attr(attributes);
	  if(content){
		  $.each(content, function(index, value) { 
			  $input.append(value); 
			});
		}
		return $input;
  },
  
  /**
   *	Helper to build FieldsetBundle (multiple inputs and tags)
   *	@param Array (url, imagesdescription, textarea, href)
   *	@return Jquery Object
   */
  _createFieldsetBundle: function(values){
  	// Href to make link around image
  	var $inputHref = this._createTag('input', {'type': 'text', 'name': 'wysiwyg_richmedia_slideshow_image_href', 'value': values[3], 'title':Drupal.t('Url destination'), 'class':'form-text'});
  	var $labelHref = this._createTag('label', {'class':'wysiwyg_richmedia_slideshow_image_href'}, Drupal.t('Url destination'));
  	var $divHref = this._createTag('div', {'class':'wysiwyg_richmedia_slideshow_image_href_container form-item'}, [$labelHref, $inputHref]);
  	
  	// Text Description
  	var $textareaDescription = this._createTag('textarea', {'name': 'wysiwyg_richmedia_slideshow_text_description', 'title':Drupal.t('Text description'), 'class':'form-textarea'}).append(values[2]);
  	var $labelTextDescription = this._createTag('label', {'class':'wysiwyg_richmedia_slideshow_text_description'}, Drupal.t('Text description'));
  	var $divTextDescription = this._createTag('div', {'class':'wysiwyg_richmedia_slideshow_text_description_container form-item'}, [$labelTextDescription, $textareaDescription]);
  	
  	
  	// Image Description
  	var $inputDescription = this._createTag('input', {'type': 'text', 'name': 'wysiwyg_richmedia_slideshow_image_description', 'value': values[1], 'title':Drupal.t('Image description'), 'class':'form-text'});
  	var $labelDescription = this._createTag('label', {'class':'wysiwyg_richmedia_slideshow_image_description'}, Drupal.t('Image description'));
  	var $divDescription = this._createTag('div', {'class':'wysiwyg_richmedia_slideshow_image_description_container form-item'}, [$labelDescription, $inputDescription]);
  	
  	// Image source URL
  	var $inputSrc = this._createTag('input', {'type': 'text', 'name': 'wysiwyg_richmedia_slideshow_image_src', 'value': values[0], 'title':Drupal.t('Image source url'), 'class':'form-text'});
  	var $labelSrc = this._createTag('label', {'class':'wysiwyg_richmedia_slideshow_image_src'}, Drupal.t('Image source url'));
  	var $divSrc = this._createTag('div', {'class':'wysiwyg_richmedia_slideshow_image_src_container form-item'}, [$labelSrc, $inputSrc]);

		// Fieldset
		var $legend = this._createTag('legend', {}, Drupal.t('Image informations'));
		var $fieldset = this._createTag('fieldset', {'class':'wysiwyg_richmedia_slideshow_image_fieldset form-item'}, [$legend, $divSrc, $divDescription, $divTextDescription, $divHref]);
		
		return $fieldset;
  }
  
};

 
})(jQuery);