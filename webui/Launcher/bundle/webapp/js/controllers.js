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
    $http.get('/macchina/launcher/apps.json').then(function(response) {
      $scope.apps = response.data;
      $scope.loading = false;
    });
  }]);

launcherControllers.controller('SessionCtrl', ['$scope', '$http',
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
