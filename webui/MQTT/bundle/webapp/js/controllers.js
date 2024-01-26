'use strict';

var mqttControllers = angular.module('mqttControllers', []);

mqttControllers.controller('ClientsCtrl', ['$scope', '$http', '$interval',
  function ($scope, $http, $interval) {
    $scope.clients = [];
    $http.get('/macchina/mqtt/clients.jss').then(function(response) {
      $scope.clients = response.data;
    });
    $interval(function() {
      $http.get('/macchina/mqtt/clients.jss').then(function(response) {
        $scope.clients = response.data;
      })
    }, 10000);
  }]);

mqttControllers.controller('SessionCtrl', ['$scope', '$http',
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
