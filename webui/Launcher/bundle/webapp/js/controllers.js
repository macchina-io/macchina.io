'use strict';

var launcherControllers = angular.module('launcherControllers', []);

launcherControllers.controller('AppGridCtrl', ['$scope', '$http',
  function ($scope, $http) {
    $scope.apps = [];
    $scope.loading = true;
    $scope.appsLoading = function() {
    	return $scope.loading;
    };
    $scope.appsAvailable = function() {
      return $scope.apps.length > 0;
    };
    $http.get('/macchina/launcher/apps.json').success(function(data) {
      $scope.apps = data;
      $scope.loading = false;
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
