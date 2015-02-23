'use strict';

var trackingControllers = angular.module('trackingControllers', []);

trackingControllers.controller('TrackingCtrl', ['$scope', '$http', '$interval',
  function ($scope, $http, $interval) {
    $scope.trackingData = {
    	available: false,
    	valid: false
    };
    
    $scope.map = null;

	$scope.resizeMap = function() {
      var newSize = $(window).height() - 240;
      if (newSize < 200) newSize = 200;
      $("#mapview").height(newSize);
      if ($scope.map)
      {
        $scope.map.updateSize();
      }
	}
	
	$scope.resizeMap();

    $scope.map = new OpenLayers.Map('mapview');
    $scope.baseLayer = new OpenLayers.Layer.OSM();
    $scope.map.addLayer($scope.baseLayer);
    $scope.markers = new OpenLayers.Layer.Markers("Markers");
    $scope.map.addLayer($scope.markers);
    $scope.marker = null;
    var initialPosition = new OpenLayers.LonLat(0, 0);
    $scope.map.setCenter(initialPosition, 1);

    $(window).resize(function() {
      $scope.resizeMap();
    });

    $scope.setPosition = function(position) {
        var olPosition = new OpenLayers.LonLat(position.longitude, position.latitude);
        var wgs84Proj = new OpenLayers.Projection("EPSG:4326"); // WGS 1984
        var mercatorProj = new OpenLayers.Projection("EPSG:900913"); // Spherical Mercator Projection
        olPosition = olPosition.transform(wgs84Proj, mercatorProj);
        var zoomIn = false;
        if (!$scope.marker) zoomIn = true; // zoom in first time marker is set
        if ($scope.marker)
        {
        	$scope.markers.removeMarker($scope.marker);
        	$scope.marker = null;
        }
        if (zoomIn)
			$scope.map.setCenter(olPosition, 10);
		else
			$scope.map.setCenter(olPosition);
		$scope.marker = new OpenLayers.Marker(olPosition);
		$scope.markers.addMarker($scope.marker);	
    };
    
    $http.get('/macchina/gnss/tracking.jss').success(function(data) {
      $scope.trackingData = data;
      if (data.valid)
      {
        $scope.setPosition(data.position);
      }
    });
    $interval(function() {
      $http.get('/macchina/gnss/tracking.jss').success(function(data) {
        $scope.trackingData = data;
        if (data.valid)
        {
          $scope.setPosition(data.position);
        }
      })
    }, 10000);
  }]);

trackingControllers.controller('SessionCtrl', ['$scope', '$http',
  function($scope, $http) {
    $http.get('/macchina/session.json').success(function(data) {
      $scope.session = data;
      if (!data.authenticated)
      {
        window.location = "/";
      }
    });
  }]);
