'use strict';

var deviceTreeControllers = angular.module('deviceTreeControllers', []);

deviceTreeControllers.controller('DeviceTreeCtrl', ['$scope', '$interval', '$http', 'DeviceTreeService', 
  function($scope, $interval, $http, DeviceTreeService) {
    $scope.data = [];
    $scope.dataById = {};
    $scope.error = "";
    $scope.idDOMOffset = 1e9;
    $scope.nextId = 0;
    $scope.expanded = false;

    $scope.clearError = function() {
      $scope.error = "";
    };
    
    $scope.getNextId = function() {
      if ($scope.nextId == 0)
      {
        $scope.nextId = 1000;
      }
      else
      {
        $scope.nextId += 1;
      }
      return $scope.nextId;
    }
  
    $scope.toggleNode = function(item) {
      item.toggle();
    };

    $scope.collapseAll = function() {
      $scope.$broadcast('angular-ui-tree:collapse-all');
      $scope.expanded = false;
    };

    $scope.expandAll = function() {
      $scope.$broadcast('angular-ui-tree:expand-all');
      $scope.expanded = true;
    };

    $scope.reload = function() {
      DeviceTreeService.load(
        function(props) {
          $scope.dataById = {};
          $scope.data = $scope.createDataArray(props);
          if ($scope.expanded)
            setTimeout(function() {$scope.expandAll();}, 0);
          else
            setTimeout(function() {$scope.collapseAll();}, 0);
        },
        function(error) {
          $scope.error = error;
        }
      );
    };

    $scope.update = function(data) {
      for (const v of data)
      {
        if ($scope.dataById.hasOwnProperty(v.key))
        {
          $scope.dataById[v.key].displayValue = v.value;
        }
      }
    };

    $scope.nodePath = function(parent, name)
    {
      if (parent.endsWith('/'))
        return parent + name;
      else if (name != '/' && parent != '')
        return parent + '/' + name;
      else
        return name;
    };

    $scope.createNode = function(parent, obj)
    {
      var node = {
        id: $scope.getNextId(),
        key: obj.id,
        name: obj.name,
        path: $scope.nodePath(parent, obj.name),
        type: obj.type,
        symbolicName: obj.symbolicName,
        physicalQuantity: obj.physicalQuantity,
        physicalUnit: obj.physicalUnit,
        displayValue: obj.displayValue,
        displayUnit: obj.displayUnit,
        fragments: []
      };
      if (obj.fragments && obj.fragments.length > 0)
      {
        node.displayValue = obj.fragments.length.toString();
        node.displayUnit = obj.fragments.length == 1 ? 'item' : 'items';
        for (const frag of obj.fragments)
        {
          node.fragments.push($scope.createNode(node.path, frag));
        }
      }
      $scope.dataById[node.key] = node;
      return node;
    };
  
    $scope.createDataArray = function(array)
    {
      var nodes = [];
      for (const obj of array)
      {
        nodes.push($scope.createNode('', obj));
      }
      return nodes;
    };

    $scope.reload();
  
    $interval(function() {
      $http.get('/macchina/devicetree/values.jss').then(function(response) {
        $scope.update(response.data);
      })
    }, 1000);
  }
]);

deviceTreeControllers.controller('SessionCtrl', ['$scope', '$http',
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
  }
]);
