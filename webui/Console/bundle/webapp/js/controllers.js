'use strict';

var webeventControllers = angular.module('consoleControllers', []);

webeventControllers.controller('ConsoleCtrl', ['$scope', 
  function($scope) {
  
  	$scope.clear = function() {
      var messagesElem = $('#messages');
      messagesElem.empty();
  	};
  	
  	$scope.follow = function() {
      $(window).scrollTop($(document).height() - $(window).height());
  	}
  	
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
      var needScroll = $(window).scrollTop() + $(window).height() > $(document).height() - 60;
      
      var messagesElem = $('#messages');
      var paraElem = $(document.createElement("p"));
      paraElem.addClass(clazz);
      var textNode = $(document.createTextNode(text));
      paraElem.append(textNode);
      messagesElem.append(paraElem); 
        
      if (needScroll) 
      {
        $(window).scrollTop($(document).height() - $(window).height());
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
        var text = date.format("YYYY-MM-DD HH:mm:ss.S") + " [" + $scope.priorities[json.priority] + "] " + json.text;

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
