'use strict';

var launcherControllers = angular.module('launcherControllers', []);

launcherControllers.controller('AppGridCtrl', ['$scope', '$http',
  function ($scope, $http) {
    $scope.apps = [];
    $scope.appsAvailable = function() {
      return $scope.apps.length > 0;
    };
    $http.get('/macchina/launcher/apps.json').success(function(data) {
      $scope.apps = data;
    });
  }]);

launcherControllers.controller('SessionCtrl', ['$scope', '$http',
  function($scope, $http) {
    $http.get('/macchina/session.json').success(function(data) {
      $scope.session = data;
      if (!data.authenticated)
      {
        window.location = "/";
      }
    });
  }]);
