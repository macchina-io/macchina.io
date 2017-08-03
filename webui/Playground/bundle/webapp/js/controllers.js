'use strict';

var playgroundControllers = angular.module('playgroundControllers', []);

playgroundControllers.controller('PlaygroundCtrl', ['$scope', '$http', 'SandboxService',
  function ($scope, $http, SandboxService) {
    $scope.state = "";
    $scope.error = "";
    $scope.editor = null;
    $scope.bundle = {
      name: "",
      symbolicName: "",
      version: "",
      vendor: "",
      copyright: ""
    };

    $scope.resizeEditor = function() {
        var newSize = $(window).height() - 140;
        if (newSize < 200) newSize = 200;
        $("#editor").height(newSize);
        if ($scope.editor) $scope.editor.resize();
    }

    $scope.resizeEditor();

    $scope.editor = ace.edit("editor");
    $scope.editor.setTheme("ace/theme/chrome");
    $scope.editor.getSession().setMode("ace/mode/javascript");
    
    $(window).resize(function() {
      $scope.resizeEditor();
    });

    $scope.clearError = function() {
      $scope.error = "";
    };
    
    $scope.saveIfModified = function(success, error) {
      if ($scope.editor.getSession().getUndoManager().isClean())
      {
      	success($scope.state);
      }
      else
      {
        SandboxService.save($scope.editor.getValue(), 
          function(state) {
             $scope.editor.getSession().getUndoManager().markClean();
             success(state);	
          }, 
          error);
      }
    };
  
    $scope.save = function() {
      $scope.clearError();
      SandboxService.save($scope.editor.getValue(),
        function(state) {
          $scope.state = state;
          $scope.editor.getSession().getUndoManager().markClean();
        },
        function(error) {
          $scope.error = error;
        }
      );
    };
    
    $scope.run = function() {
      $scope.clearError();
      $scope.saveIfModified(
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
      $scope.saveIfModified(
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
 
     $scope.export = function() {
      $scope.clearError();
      $scope.hideExport();
      $scope.saveIfModified(
        function(state) {
          $scope.state = state;
          setTimeout(function() { 
              $('#exportForm').submit(); 
            }, 100);
        },
        function(error) {
          $scope.error = error;
        }
      );
    };
   
    $scope.showExport = function() {
      $('#modalBackground').css("display", "block");
      $('#exportPopup').css("display", "block");
      $('#exportForm input[name=name]').focus();
      $(document).on('keyup.exportPopup',
        function(e) {
          if (e.keyCode == 27) 
          {
            $scope.hideExport(); 
          }
          else if (e.keyCode == 13 && $scope.exportForm.$valid)
          {
            $scope.export();
          }
        }
      );     
    };
    
    $scope.hideExport = function() {
    	$('#modalBackground').css("display", "none");
    	$('#exportPopup').css("display", "none");
    	$(document).unbind('keyup.exportPopup');
    };
    
    SandboxService.info(
      function(state, bundleInfo) {
        $scope.state = state;
        $scope.bundle = bundleInfo;
      },
      function(error) {
        $scope.error = error;
      }
    );

    SandboxService.load(
      function(script) {
        $scope.editor.setValue(script, -1);
        $scope.editor.focus();
        $scope.editor.getSession().getUndoManager().reset();
        $scope.editor.getSession().getUndoManager().markClean();
      },
      function(error) {
        $scope.error = error;
      }
    );
  }
]);

playgroundControllers.controller('SessionCtrl', ['$scope', '$http',
  function($scope, $http) {
    $http.get('/macchina/session.json').success(function(data) {
      $scope.session = data;
      if (!data.authenticated)
      {
        window.location = "/";
      }
    });
  }
]);
