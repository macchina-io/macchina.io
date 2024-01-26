'use strict';

var devicesControllers = angular.module('devicesControllers', []);

devicesControllers.controller('DevicesCtrl', ['$scope', '$http', '$interval',
  function ($scope, $http, $interval) {
    $scope.devices = [];
    $scope.search = "";
    $scope.orderBy = "name";
    $scope.setOrderBy = function(col) {
      $scope.orderBy = col;
    }
    $scope.iconClass = function(dev) {
      if (dev.type.startsWith('io.macchina.datapoint'))
      {
        return 'fa fa-tachometer';
      }
      else switch (dev.type)
      {
        case 'io.macchina.sensor':
          return 'fa fa-thermometer';
        case 'io.macchina.gnss':
          return 'fa fa-location-arrow';
        case 'io.macchina.composite':
          return 'fa fa-sitemap';
        case 'io.macchina.led':
          return 'fa fa-lightbulb-o';
        case 'io.macchina.accelerometer':
        case 'io.macchina.gyroscope':
        case 'io.macchina.magnetometer':
          return 'fa fa-microchip';
        case 'io.macchina.barcode':
          return 'fa fa-barcode';
        default:
          return 'fa fa-gear';
      }
    }
    $http.get('/macchina/devices/devices.jss').then(function(response) {
      $scope.devices = response.data;
    });
    $interval(function() {
      $http.get('/macchina/devices/devices.jss').then(function(response) {
        $scope.devices = response.data;
      })
    }, 1000);
  }]);

devicesControllers.controller('SessionCtrl', ['$scope', '$http',
  function($scope, $http) {
    $http.get('/macchina/session.json').then(
      function(response) {
        $scope.session = response.data;
        if (!response.data.authenticated)
        {
          window.location = "/";
        }
      }
    );
  }]);
