'use strict';

var peripheralsControllers = angular.module('peripheralsControllers', []);

peripheralsControllers.controller('PeripheralsCtrl', ['$scope', '$http', '$interval',
  function ($scope, $http, $interval) {
    $scope.peripherals = [];
    $scope.search = '';
    $scope.orderBy = 'name';
    $scope.status = '';
    $scope.statusTimer = null;

    $scope.setOrderBy = function(col) {
      $scope.orderBy = col;
    }
  
  $scope.addressType = function(type) {
    switch (type)
    {
    case 0: return 'BR/EDR';
    case 1: return 'public';
    case 2: return 'random';
    default: return 'unknown';
    }
  }

  $scope.refresh = function() {
    WebEvent.notify('btle.scan.command', 'start');
  }

  $scope.resetSeenState = function() {
    for (let p of $scope.peripherals)
    {
      p.seen = false;
    }
  }

  $scope.removePeripheral = function(index)
  {
    const n = $scope.peripherals.length - index - 1;
    for (let i = 0; i < n; i++)
    {
      $scope.peripherals[index + i] = $scope.peripherals[index + i + 1];
    }
    $scope.peripherals.pop();
  }

  $scope.removeUnseen = function()
  {
    let length = $scope.peripherals.length;
    for (let i = 0; i < length; i++)
    {
      if (!$scope.peripherals[i].seen)
      {
        $scope.removePeripheral(i);
        length--;
      }
    }
  }
  
  $scope.addOrUpdatePeripheral = function(peripheral) {
    peripheral.seen = true;
    for (let i = 0; i < $scope.peripherals.length; i++)
    {
      if ($scope.peripherals[i].address === peripheral.address)
      {
        $scope.peripherals[i] = peripheral;
        return;
      }
    }
    $scope.peripherals.push(peripheral);
    $scope.$apply();
  }

  $scope.updateScanningStatus = function() {
    switch ($scope.status)
    {
      case 'Scanning.':
        $scope.status = 'Scanning..';
        break;
      case 'Scanning..':
        $scope.status = 'Scanning...';
        break;
      case 'Scanning...':
        $scope.status = 'Scanning.';
        break;
    }
    $scope.$apply();
  }

  $scope.startStatusTimer = function() {
    if ($scope.statusTimer != null)
    {
      clearInterval($scope.statusTimer);
    }
    $scope.statusTimer = setInterval($scope.updateScanningStatus, 1000);
  }

  $scope.stopStatusTimer = function() {
    if ($scope.statusTimer != null)
    {
      clearInterval($scope.statusTimer);
    }
  }
    
  if (WebEvent.available)
  {
    WebEvent.onConnect = function() {
      WebEvent.subscribe('btle.scan');
      WebEvent.notify('btle.scan.command', 'start');
    };

    WebEvent.onNotify = function(evt) {
      if (evt.subject === 'btle.scan.peripheralFound')
      {
        $scope.addOrUpdatePeripheral(JSON.parse(evt.data));
      }
      else if (evt.subject === 'btle.scan.started')
      {
        $scope.status = 'Scanning...';
        $scope.resetSeenState();
        $scope.startStatusTimer();
        $scope.$apply();
      }
      else if (evt.subject === 'btle.scan.completed')
      {
        $scope.status = '';
        $scope.removeUnseen();
        $scope.stopStatusTimer();
        $scope.$apply();
      }
      else if (evt.subject === 'btle.scan.error')
      {
        $scope.status = 'Error: ' + evt.data;
        $scope.stopStatusTimer();
        $scope.$apply();
      }
    };

    WebEvent.connect();
  }

}]);

peripheralsControllers.controller('SessionCtrl', ['$scope', '$http',
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
