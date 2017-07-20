'use strict';

var dataflowControllers = angular.module('dataflowControllers', []);

dataflowControllers.controller('DataflowCtrl', ['$scope', '$http',
  function($scope, $http) {

    $scope.resizeEditor = function() {
        var newSize = $(window).height() - 140;
        if (newSize < 200) newSize = 200;
        $("#editor").height(newSize);
        if ($scope.editor) $scope.editor.resize();
    }

    $scope.resizeEditor();
    
    $(window).resize(function() {
      $scope.resizeEditor();
    });

  }]);


dataflowControllers.controller('SessionCtrl', ['$scope', '$http',
  function($scope, $http) {
    $http.get('/macchina/session.json').success(function(data) {
      $scope.session = data;
      if (!data.authenticated)
      {
        window.location = "/";
      }
    });
  }]);
