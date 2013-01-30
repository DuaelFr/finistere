Drupal.settings.interactivemapparameters = new Object;
Drupal.settings.interactivemapparameters.fluxparentterm = new Object;
Drupal.settings.interactivemapparameters.nid = new Object;
Drupal.settings.interactivemapparameters.nids = new Object;
Drupal.settings.interactivemapparameters.termand = new Object;
Drupal.settings.interactivemapparameters.city = "";
Drupal.settings.kml = new Array();

$(document).ready(function() {
	initialize();
	
	$(".cartpoints a").click(function(){
		if($(this).attr("href").substring(0, 10)!="javascript" && $(this).attr("kml")==undefined){
			bindaddmarkers($(this));
			return false;
		}else if($(this).attr("kml")!=undefined){
			bindaddkml($(this));
			return false;
		}
	});

  $("#interactivemap-autocompletecity-form").submit(function(){
    Drupal.settings.interactivemapparameters.city  = $('#edit-city', $(this)).val();

    var path="/carte-interactive?city="+Drupal.settings.interactivemapparameters.city;

    var parameters = path.split('?');

    var path = parameters[0];
    setParameters(parameters);

    path = "/carteint-ajax"+path;

    var datas = { js: true };
    datas['city'] = Drupal.settings.interactivemapparameters.city;

    datas['nid'] = getParameter('nid');
    datas['nids'] = getParameter('nids');
    datas['termand'] = getParameter('termand');
    datas['fluxparentterm'] = getParameter('fluxparentterm');

    _interactivemap_callajax(path, datas);

    return false;
  });
	
});

function _interactivemap_callajax(path, datas){
  $.ajax({
      type: 'GET',
      url: path,
      data: datas,
      dataType: 'json',
      success: function (data) {
        Drupal.settings.markers = new Array();
        if(data.markerstoadd) {

          var alreadyloaded = [];

           for(var i=0; i<data.markerstoadd.length; i++){
            var value = data.markerstoadd[i];

            if($.inArray(value.nid, alreadyloaded)<0){
              Drupal.settings.markers.push(value);
            }
          };

        }
        reloadMarkers();
      },
      error: function (xmlhttp) {}
  });
}

function bindaddmarkers(elt){
  setLoading('.gmap-interactivemap-gmap');
	var path = $(elt).attr("href");
	
	// Get arguments : nid, kml and terms to load
	var parameters = path.split('?');
	
	var path = parameters[0];
	setParameters(parameters);
		
	path = "/carteint-ajax"+path;
	
	$(elt).toggleClass('active');
	
	var datas = { js: true };

  datas['city'] = Drupal.settings.interactivemapparameters.city;
  
	var $fluxparentterm = getParameter('fluxparentterm');
	if($fluxparentterm != ""){
		datas['fluxparentterm'] = $fluxparentterm;
	}
	var $nid = getParameter('nid');
	if($nid != ""){
		datas['nid'] = $nid;
	}
	var $nids = getParameter('nids');
	if($nids != ""){
		datas['nids'] = $nids;
	}
	var $termand = getParameter('termand');
	if($termand != ""){
		datas['termand'] = $termand;
	}
	
  _interactivemap_callajax(path, datas);
	
	$(elt).addClass("mapdisplayed");
	
	return false;
}

function bindaddkml(elt){
  setLoading('.gmap-interactivemap-gmap');
	var path = $(elt).attr("kml");
	
  if(path.indexOf('http://', 0) != 0){
    path = 'http://' + document.domain + path;
  }
	
	
  if($.inArray(path, Drupal.settings.kml)<0){
    Drupal.settings.kml.push(path);
    $(elt).addClass('active');
  }else{
    var newKmlArray = [];
    for(var i=0; i<Drupal.settings.kml.length; i++){
      if(Drupal.settings.kml[i] != path){
        newKmlArray.push(Drupal.settings.kml[i]);
      }
    }
    Drupal.settings.kml = newKmlArray;
    
    $(elt).removeClass('active');
  }
	
	reloadMarkers();
	
	$(elt).addClass("mapdisplayed");
	
	return false;
}

/*
 * Fonction permettant d'initialiser les contrôles et différentes manipulations
 * sur la map.
 * Cette fonction est NECESSAIRE car la map n'est pas forcément toujours chargée,
 * et ce malgré le $(document).ready.
 */
function initialize() {
  //if (GBrowserIsCompatible()) {
    var m = Drupal.gmap.getMap('interactivemap');
    if (m.map) {
      initMap(m);
    }
    else {
      m.bind('ready', function(data) {
        initMap(m);
      });
    }
  //}
}

/*
 * Récupération de la map,
 * Ajout des contrôles et appel de la fonction
 * de loading des éléments
 */
function initMap(partMap) { 

	map = partMap.map;
	//partMap.map.addControl(new GLargeMapControl());
	var path = document.location.toString();

	// Get arguments : nid, kml and terms to load
	var parameters = path.split('?');

	var path = parameters[0];
	setParameters(parameters);

	loadElements();
}

function loadElements() {
	/* On charge l'icône qui représentera les markers... */
	var blueIcon = new GIcon();
	blueIcon.image = Drupal.settings.basePath+'sites/all/modules/gnova/interactivemap/markerfix2.png';
	blueIcon.shadow = Drupal.settings.basePath+'sites/all/modules/gnova/interactivemap/shadowfix2.png';
	blueIcon.iconAnchor = new GPoint(10, 33);
	blueIcon.infoWindowAnchor = new GPoint(5, 1); 
	
	/* Définition des différentes options pour les markers que l'on créera... */
	var markerOptionsDefault = {
		icon: blueIcon
	};

  if(Drupal.settings.markers.length == 0 && Drupal.settings.interactivemapparameters.city != ""){
    var geocoder = new GClientGeocoder();
    geocoder.setBaseCountryCode('fr'); // Only search in France
    geocoder.getLatLng(
      Drupal.settings.interactivemapparameters.city,
      function(point) {
        if (point) {
          map.setCenter(point, 13);
        }
      }
    );

  }else if(Drupal.settings.markers.length > 0){
    // Centering map, based on markers on it
      var latlng = [];
      var i = 0;
      for (var marki in Drupal.settings.markers) {
        var mark = Drupal.settings.markers[marki];
        if (mark.latitude && mark.longitude) {
          latlng[i] = new GLatLng(mark['latitude'], mark['longitude']);
          i++;
        }
      }
			var latlngbounds = new GLatLngBounds( );
			for ( var i = 0; i < latlng.length; i++ )
			{
			//	console.log(latlng[i]);
			  latlngbounds.extend( latlng[ i ] );
			}

      var zoom = map.getBoundsZoomLevel( latlngbounds );
      if(zoom > 15){
        zoom = 15;
      }

			map.setCenter( latlngbounds.getCenter( ), zoom );
  }

	/* 
	 * On crée ces markers à partir de Drupal.settings. (cf structure plus haut)
	 */
	for (i=0; i < Drupal.settings.markers.length; i++) {
		var tMarker = Drupal.settings.markers[i];
		if (tMarker.latitude && tMarker.longitude) {

	    var markerOptions = markerOptionsDefault;
      /* On charge l'icône qui représentera les markers... */
      if(tMarker.image != '' && tMarker.image != undefined){
        var blueIcon = new GIcon();
        blueIcon.image = tMarker.image;
        blueIcon.iconAnchor = new GPoint(10, 33);
        blueIcon.infoWindowAnchor = new GPoint(5, 1);
        /* Définition des différentes options pour les markers que l'on créera... */
        var markerOptions = {
          icon: blueIcon
        };
      }


			map.addOverlay(createMarker(tMarker.latitude, tMarker.longitude, tMarker.html, markerOptions));
		}
	}
	
	/* loading des KMLs... */
	if(Drupal.settings.kml==undefined){
	
	}else{
		for (i=0; i < Drupal.settings.kml.length; i++) {
			var tKml = Drupal.settings.kml[i];
			var nyKml = new GGeoXml(tKml);
			map.addOverlay(nyKml);
		}
	}
	
}

/*
 * Fonction permettant de créer et retourner un marker
 * à partir de latitude, longitude, d'html à intégrer dans l'infobulle
 * et d'options.
 * markerOptions: objet permettant notamment de définir l'icône, l'ombre etc du marker.
 * Différentes options visibles ici:
 * http://code.google.com/intl/fr-FR/apis/maps/documentation/javascript/v2/reference.html#GMarkerOptions
 */
function createMarker(latitude, longitude, html, markerOptions) {
	
		var point = new GLatLng(latitude, longitude);
        var marker = new GMarker(point, markerOptions);
        GEvent.addListener(marker, "click", function() {
          marker.openInfoWindowHtml(html);
        });
        GEvent.addListener(marker, "infowindowopen", function(){
        	Drupal.attachBehaviors();
        });
        return marker;
}

/*
 * Fonction de mise en page de la "bubble" d'info
 * au clic sur un marqueur.
 * Ajouter ici le code que l'on veut qui entourera le html du marqueur.
 */
function modText(html) {
	return html;
}

/* 
 * Fonction de reloading des éléments de
 * la Map
 */
function reloadMarkers() {
	map.clearOverlays();
	loadElements();
  unsetLoading('.gmap-interactivemap-gmap-loading');
}


function getParameterByName( name )
{
  name = name.replace(/[\[]/,"\\\[").replace(/[\]]/,"\\\]");
  var regexS = "[\\?&]"+name+"=([^&#]*)";
  var regex = new RegExp( regexS );
  var results = regex.exec( window.location.href );
  if( results == null )
    return "";
  else
    return decodeURIComponent(results[1].replace(/\+/g, " "));
}


/**
 * function setParameters
 * Drupal.settings.interactivemapparameters structure :
 * array(
 *   'fluxparentterm' => array(
 *     termid1=>termid1,
 *     termid2=>termid2,
 *     termid3=>termid3,
 *   ),
 *   'nid' => array(
 *     nid1=>nid1,
 *   )
 * )
 **/
function setParameters(urlparameters){
	if(urlparameters.length > 1){
		urlparameters = urlparameters[1].split('&');

		for(var i=0;i<urlparameters.length;i++){
			var param = urlparameters[i];
			
			if(param.length > 0){
				var myparams = param.split('=');
				if(myparams.length == 2){
					var multipleparams = myparams[1].split('-');
					for(var j=0;j<multipleparams.length;j++){
						if(Drupal.settings.interactivemapparameters[myparams[0]][multipleparams[j]] == undefined){
							Drupal.settings.interactivemapparameters[myparams[0]][multipleparams[j]] = multipleparams[j];
						}else{
							delete Drupal.settings.interactivemapparameters[myparams[0]][multipleparams[j]];
						}
					}
				}
			}
		}
	}
}

function getParameter(parameter){
	var parameters = Drupal.settings.interactivemapparameters[parameter];
	var datas = "";

	for(var param in parameters){
		if(datas != ""){
			datas += "-";
		}
		datas += param;
	}
	return datas;
}

function setLoading(selector){
  $(selector + ':not('+ selector +'-loading)').addClass(selector.substring(1) + '-loading').append('<img src="' + Drupal.settings.basePath+'sites/all/modules/gnova/interactivemap/loading.gif' + '" alt="loading" class="loading" />');
}

function unsetLoading(selector){
  $(selector + ' .loading').remove();
  $(selector).removeClass(selector.substring(1));
}