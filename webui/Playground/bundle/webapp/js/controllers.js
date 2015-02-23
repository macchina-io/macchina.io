'use strict';

var playgroundControllers = angular.module('playgroundControllers', []);

playgroundControllers.controller('PlaygroundCtrl', ['$scope', '$http', 'SandboxService',
  function ($scope, $http, SandboxService) {
    $scope.state = "";
    $scope.error = "";

    $("#editor").height($(window).height() - 140);
    $scope.editor = ace.edit("editor");
    $scope.editor.setTheme("ace/theme/chrome");
    $scope.editor.getSession().setMode("ace/mode/javascript");
    
    $(window).resize(function() {
      $("#editor").height($(window).height() - 140);
      $scope.editor.resize();
    });

    $scope.clearError = function() {
      $scope.error = "";
    };
  
    $scope.save = function() {
      $scope.clearError();
      SandboxService.save($scope.editor.getValue(),
        function(state) {
          $scope.state = state;
        },
        function(error) {
          $scope.error = error;
        }
      );
    };
    
    $scope.run = function() {
      $scope.clearError();
      SandboxService.save($scope.editor.getValue(),
        function(state) {
          $scope.state = state;
          SandboxService.run(
            function(state) {
              $scope.state = state;
            },
            function(error) {
              $scope.error = error;
            }
          );
        },
        function(error) {
          $scope.error = error;
        }
      );
    };

    $scope.restart = function() {
      $scope.clearError();
      SandboxService.save($scope.editor.getValue(),
        function(state) {
          $scope.state = state;
          SandboxService.restart(
            function(state) {
              $scope.state = state;
            },
            function(error) {
              $scope.error = error;
            }
          );
        },
        function(error) {
          $scope.error = error;
        }
      );
    };
    
    $scope.stop = function() {
      $scope.clearError();
      SandboxService.stop(
        function(state) {
          $scope.state = state;
        },
        function(error) {
          $scope.error = error;
        }
      );
    };
    
    SandboxService.state(
      function(state) {
        $scope.state = state;
      },
      function(error) {
        $scope.error = error;
      }
    );

    SandboxService.load(
      function(script) {
        $scope.editor.setValue(script, -1);
        $scope.editor.focus();
      },
      function(error) {
        $scope.error = error;
      }
    );
  }]);

playgroundControllers.controller('SessionCtrl', ['$scope', '$http',
  function($scope, $http) {
    $http.get('/macchina/session.json').success(function(data) {
      $scope.session = data;
      if (!data.authenticated)
      {
        window.location = "/";
      }
    });
  }]);
