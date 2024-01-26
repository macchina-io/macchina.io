'use strict';

var gpioControllers = angular.module('gpioControllers', []);

gpioControllers.controller('GpioCtrl', ['$scope', '$http', '$interval',
  function($scope, $http, $interval) {
    $scope.devices = [];
    $scope.orderBy = "name";

    $scope.setOrderBy = function(col) {
      $scope.orderBy = col;
    }

    $scope.toggleState = function(id) {
      var jsonData = $.ajax({
        url: '/macchina/gpio/toggle.jss?gpio=' + encodeURIComponent(id),
        dataType: 'json',
      });
    }

    $http.get('/macchina/gpio/gpio.jss').then(function(response) {
      $scope.devices = response.data;
    });

    $interval(function() {
        $http.get('/macchina/gpio/gpio.jss').then(function(response) {
          $scope.devices = response.data;
        })
      }, 1000);
  }
]);

gpioControllers.controller('SessionCtrl', ['$scope', '$http',
  function($scope, $http) {
    $http.get('/macchina/session.json').then(
      function(response) {
        $scope.session = response.data;
        if (!response.data.authenticated) {
          window.location = "/";
        }
      }
    );
  }
]);
