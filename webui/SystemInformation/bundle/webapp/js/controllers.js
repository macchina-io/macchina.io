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
    $http.get('/macchina/sysinfo/sysinfo.jss').then(
      function(response) {
        $scope.sysinfo = response.data;
      }
    );
  }]);

sysinfoControllers.controller('ProcessesCtrl', ['$scope', '$http',
  function ($scope, $http) {
    $scope.processes = {};
    $http.get('/macchina/sysinfo/processes.jss').then(
      function(response) {
        $scope.processes = response.data;
      }
    );
  }]);

sysinfoControllers.controller('MemoryCtrl', ['$scope', '$http',
  function ($scope, $http) {
    $scope.processes = {};
    $http.get('/macchina/sysinfo/memory.jss').then(
      function(response) {
        $scope.memory = response.data;
      }
    );
  }]);

sysinfoControllers.controller('SessionCtrl', ['$scope', '$http',
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
