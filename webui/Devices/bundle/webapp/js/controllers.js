'use strict';

var devicesControllers = angular.module('devicesControllers', []);

devicesControllers.controller('DevicesCtrl', ['$scope', '$http', '$interval',
  function ($scope, $http, $interval) {
    $scope.devices = [];
    $http.get('/macchina/devices/devices.jss').success(function(data) {
      $scope.devices = data;
    });
    $interval(function() {
      $http.get('/macchina/devices/devices.jss').success(function(data) {
        $scope.devices = data;
      })
    }, 5000);
  }]);

devicesControllers.controller('SessionCtrl', ['$scope', '$http',
  function($scope, $http) {
    $http.get('/macchina/session.json').success(function(data) {
      $scope.session = data;
      if (!data.authenticated)
      {
        window.location = "/";
      }
    });
  }]);
