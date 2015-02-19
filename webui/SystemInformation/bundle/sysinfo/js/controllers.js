'use strict';

var sysinfoControllers = angular.module('sysinfoControllers', []);

sysinfoControllers.controller('TabCtrl', ['$scope', '$http',
  function ($scope, $http) {
    $scope.selectedTab = "sysinfo";
    $scope.switchTab = function(tab) {
      $scope.selectedTab = tab;
    }
    $scope.isTab = function(tab) {
      return $scope.selectedTab == tab;
    }
  }]);

sysinfoControllers.controller('SysInfoCtrl', ['$scope', '$http',
  function ($scope, $http) {
    $scope.sysinfo = {};
    $http.get('/macchina/sysinfo/sysinfo.jss').success(function(data) {
      $scope.sysinfo = data;
    });
  }]);

sysinfoControllers.controller('ProcessesCtrl', ['$scope', '$http',
  function ($scope, $http) {
    $scope.processes = {};
    $http.get('/macchina/sysinfo/processes.jss').success(function(data) {
      $scope.processes = data;
    });
  }]);

sysinfoControllers.controller('MemoryCtrl', ['$scope', '$http',
  function ($scope, $http) {
    $scope.processes = {};
    $http.get('/macchina/sysinfo/memory.jss').success(function(data) {
      $scope.memory = data;
    });
  }]);

sysinfoControllers.controller('SessionCtrl', ['$scope', '$http',
  function($scope, $http) {
    $http.get('/macchina/session.json').success(function(data) {
      $scope.session = data;
      if (!data.authenticated)
      {
        window.location = "/";
      }
    });
  }]);
