'use strict';

var consoleControllers = angular.module('consoleControllers', []);

consoleControllers.controller('ConsoleCtrl', ['$scope', 'LogLevelService',
  function($scope, LogLevelService) {
  	$scope.messages = $("#messages");
  	$scope.messageCount = 0;
  	$scope.messageLimit = 10000;
  
  	$scope.clear = function() {
      $scope.messages.empty();
      $scope.messageCount = 0;
  	};
  	
  	$scope.follow = function() {
      $scope.messages.scrollTop($scope.messages.prop("scrollHeight"));
  	}

    $scope.selectText = function(id) {
      var node = document.getElementById(id);
  
      if (document.body.createTextRange)
      {
        var range = document.body.createTextRange();
        range.moveToElementText(node);
        range.select();
        return true;
      }
      else if (window.getSelection)
      {
        var selection = window.getSelection();
        var range = document.createRange();
        range.selectNodeContents(node);
        selection.removeAllRanges();
        selection.addRange(range);
        return true;
      }
      return false;
    }

    $scope.clearSelection = function() {
      if (window.getSelection)
      {
        var selection = window.getSelection();
        selection.removeAllRanges();
      }
    }
  
    $scope.copyToClipboard = function(id) {
      var success = false;
      if ($scope.selectText(id))
      {
        success = document.execCommand('copy');
        $scope.clearSelection();
      }
      if (!success)
      {
        alert('Could not copy log to clipboard.');
      }
    }
  
   	$scope.resizeMessages = function() {
      var newSize = $(window).height() - 140;
      if (newSize < 200) newSize = 200;
      var newWidth = $("#messagesContainer").width() - 8;
      $scope.messages.height(newSize);
      $scope.messages.width(newWidth);
	  }

    $scope.showLogLevelsPopup = function() {
      $scope.loadLogLevels();
      $('#modalBackground').css('display', 'block');
      $('#logLevelsPopup').css('display', 'block');
      $('#logLevelsForm input[name=filter]').focus();
      $(document).on('keyup.logLevelsPopup',
        function(e) {
          if (e.keyCode == 27) 
          {
            $scope.hideLogLevelsPopup(); 
          }
          else if (e.keyCode == 13)
          {
            $scope.updateLogLevels();
          }
        }
      );   
    }

    $scope.hideLogLevelsPopup = function() {
      $('#modalBackground').css('display', 'none');
      $('#logLevelsPopup').css('display', 'none');
      $(document).unbind('keyup.logLevelsPopup');
    }

    $scope.updateLogLevels = function() {
      $scope.saveLogLevels(function() {
        $scope.hideLogLevelsPopup();
      });
    }

    $scope.loadLogLevels = function() {
      LogLevelService.load(
        function(loggers) {
          $scope.loggers = [];
          for (var l in loggers)
          {
            $scope.loggers.push({
              name: l,
              level: loggers[l],
              loadedLevel: loggers[l]
            });
          }
        },
        function() {
          $scope.error = "Failed to load log levels.";
        }
      );
    }

    $scope.saveLogLevels = function(fn) {
      var loggers = {};
      var mustSave = false;
      for (var i = 0; i < $scope.loggers.length; i++)
      {
        var l = $scope.loggers[i];
        if (l.level != l.loadedLevel)
        {
          loggers[l.name] = l.level;
          mustSave = true;
        }
      }
      if (mustSave)
      {
        LogLevelService.update(loggers, 
          function() 
          {
            fn();
          }, 
          function() 
          {
            $scope.error = "Failed to set log levels.";
          }
        );
      }
      else
      {
        fn();
      }
    }

    $(window).resize(function() {
      $scope.resizeMessages();
    });
    
    $scope.resizeMessages();

    $scope.error = "";

    $scope.priorityFilter = 7; // Debug

    $scope.loggers = [];
 	
    $scope.logLevelOptions = [
      {id: "none", name: "None"},
      {id: "fatal", name: "Fatal"},
      {id: "critical", name: "Critical"},
      {id: "error", name: "Error"},
      {id: "warning", name: "Warning"},
      {id: "notice", name: "Notice"},
      {id: "information", name: "Information"},
      {id: "debug", name: "Debug"},
      {id: "trace", name: "Trace"}
    ];

    $scope.priorityFilterOptions = [
      {id: 1, name: "Fatal"},
      {id: 2, name: "Critical"},
      {id: 3, name: "Error"},
      {id: 4, name: "Warning"},
      {id: 5, name: "Notice"},
      {id: 6, name: "Information"},
      {id: 7, name: "Debug"},
      {id: 8, name: "Trace"}
    ];

  	$scope.priorities = [
    	"",
  		"Fatal",
  		"Critical",
  		"Error",
  		"Warning",
	  	"Notice",
  		"Information",
  		"Debug",
  		"Trace"
	  ];
	
    $scope.priorityClasses = [
      "",
      "prio-fatal",
      "prio-critical",
      "prio-error",
      "prio-warning",
      "prio-notice",
      "prio-information",
      "prio-debug",
      "prio-trace"
    ];
	
    $scope.appendMessage = function(text, clazz) {
        var needScroll = $scope.messages.scrollTop() > $scope.messages.prop("scrollHeight") - $scope.messages.height() - 60;
        
        var messagesElem = $('#messages');
        var paraElem = $(document.createElement("p"));
        paraElem.addClass(clazz);
        var textNode = $(document.createTextNode(text));
        paraElem.append(textNode);
        messagesElem.append(paraElem); 
        
        if ($scope.messageCount >= $scope.messageLimit)
        {
          messagesElem.find('p:first').remove();
        }
        else
        {
          $scope.messageCount++;
        }
          
        if (needScroll) 
        {
          $scope.messages.scrollTop($scope.messages.prop("scrollHeight"))
        }
    }
    
    if ("WebSocket" in window)  
    {
      var wss = window.location.protocol == "https:" ? "wss://" : "ws://";
      var webSocket = new WebSocket(wss + window.location.host + "/macchina/console/messages");    

      webSocket.onopen = function()
	  {
      }
      
      webSocket.onmessage = function(evt)
      {
        var json = JSON.parse(evt.data);
        var date = moment(json.time);
        var text = date.format("YYYY-MM-DD HH:mm:ss.S") + " [" + $scope.priorities[json.priority] + "] " + json.source + ": " + json.text;

        if (json.priority <= $scope.priorityFilter)
        {
          $scope.appendMessage(text, $scope.priorityClasses[json.priority]);
        }
      }
      
      webSocket.onerror = function()
      {
      	$scope.appendMessage("Connection to server failed.", "prio-error");
      }
      
      webSocket.onclose = function()
      {
      	$scope.appendMessage("Connection to server closed.", "prio-notice");
      }
	  }
  }]);

consoleControllers.controller('SessionCtrl', ['$scope', '$http',
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
