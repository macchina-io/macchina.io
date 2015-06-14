'use strict';

var webeventControllers = angular.module('consoleControllers', []);

webeventControllers.controller('ConsoleCtrl', ['$scope', 
  function($scope) {
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
 
 	$scope.resizeMessages = function() {
      var newSize = $(window).height() - 140;
      if (newSize < 200) newSize = 200;
      var newWidth = $("#messagesContainer").width() - 8;
      $scope.messages.height(newSize);
      $scope.messages.width(newWidth);
	}

    $(window).resize(function() {
      $scope.resizeMessages();
    });
    
    $scope.resizeMessages();
 	
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

        $scope.appendMessage(text, $scope.priorityClasses[json.priority]);
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

webeventControllers.controller('SessionCtrl', ['$scope', '$http',
  function($scope, $http) {
    $http.get('/macchina/session.json').success(function(data) {
      $scope.session = data;
      if (!data.authenticated)
      {
        window.location = "/";
      }
    });
  }]);
