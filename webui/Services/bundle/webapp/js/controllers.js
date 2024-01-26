'use strict';

var servicesControllers = angular.module('servicesControllers', []);

servicesControllers.controller('ServicesCtrl', ['$scope', '$http', 
  function ($scope, $http) {
    $scope.services = [];
    $scope.search = "";

    $scope.countProperties = function(service)
    {
      return service.properties.length + 1;
    }
    
    $http.get('/macchina/services/services.jss').then(function(response) {
      $scope.services = response.data;
    });
  }]);

servicesControllers.controller('SessionCtrl', ['$scope', '$http',
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
