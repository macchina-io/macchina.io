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

	$scope.map = new ol.Map({
      target: 'mapview',
      layers: [
        new ol.layer.Tile({
          source: new ol.source.OSM()
        })
      ],
      view: new ol.View({
        center: ol.proj.fromLonLat([0.0, 0.0]),
        zoom: 1
      })
    });

    $scope.markers = null;

    $scope.setPosition = function(position) {
      var zoomIn = false;
      if ($scope.markers)
      {
        $scope.map.removeLayer($scope.markers);
        $scope.markers = null;
      }
      else
      {
        zoomIn = true;
      }
      const projPos = ol.proj.fromLonLat([position.longitude, position.latitude]);
      $scope.markers = new ol.layer.Vector({
        source: new ol.source.Vector({
          features: [
            new ol.Feature({
              geometry: new ol.geom.Point(projPos)
            })
          ]
        }),
        style: new ol.style.Style({
          image: new ol.style.Icon({
            anchor: [0.5, 1],
            anchorXUnits: 'fraction',
            anchorYUnits: 'fraction',
            src: '/openlayers/img/marker.png'
          })
        })
      })
      $scope.map.addLayer($scope.markers);
      $scope.map.getView().setCenter(projPos);
      if (zoomIn)
      {
		$scope.map.getView().setZoom(10);
	  }
    };

    $(window).resize(function() {
      $scope.resizeMap();
    });

    $http.get('/macchina/gnss/tracking.jss').success(function(data) {
      $scope.trackingData = data;
      if (data.valid)
      {
        $scope.setPosition(data.position);
      }
      if (data.refresh)
      {
        $interval(function() {
          $http.get('/macchina/gnss/tracking.jss').success(function(data) {
            $scope.trackingData = data;
            if (data.valid)
            {
              $scope.setPosition(data.position);
            }
          })
        }, data.refresh);
      }
    });
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
