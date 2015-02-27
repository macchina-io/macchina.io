'use strict';

var mqttControllers = angular.module('mqttControllers', []);

mqttControllers.controller('ClientsCtrl', ['$scope', '$http', '$interval',
  function ($scope, $http, $interval) {
    $scope.clients = [];
    $http.get('/macchina/mqtt/clients.jss').success(function(data) {
      $scope.clients = data;
    });
    $interval(function() {
      $http.get('/macchina/mqtt/clients.jss').success(function(data) {
        $scope.clients = data;
      })
    }, 10000);
  }]);

mqttControllers.controller('SessionCtrl', ['$scope', '$http',
  function($scope, $http) {
    $http.get('/macchina/session.json').success(function(data) {
      $scope.session = data;
      if (!data.authenticated)
      {
        window.location = "/";
      }
    });
  }]);
