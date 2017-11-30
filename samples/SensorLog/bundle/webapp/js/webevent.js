//
// webevent.js
//
// $Id$
//
// Copyright (c) 2013-2017, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// This is unpublished proprietary source code of Applied Informatics.
// The contents of this file may not be disclosed to third parties, 
// copied or duplicated in any form, in whole or in part.
//


var WebEvent = 
{
	webSocket: null,
	
	available: function()
		{
			return 'WebSocket' in window;
		},
		
	connect: function()
		{
			if (!WebEvent.available()) return false;

			var wss = window.location.protocol == 'https:' ? 'wss://' : 'ws://';
			WebEvent.webSocket = new WebSocket(wss + window.location.host + '/webevent');    
			
			WebEvent.webSocket.onopen = function()      
			{
				if (WebEvent.onConnect) WebEvent.onConnect();
			}; 
			
			WebEvent.webSocket.onmessage = function(evt)      
			{
				var msg = evt.data;
				var parsedEvent = WebEvent.parseEvent(msg);
				if (parsedEvent.method == 'NOTIFY')
				{
					WebEvent.onNotify(parsedEvent);
				}
			};
			
			WebEvent.webSocket.onclose = function()
			{
				if (WebEvent.onDisconnect) WebEvent.onDisconnect();
				WebEvent.webSocket = null;
			};
			
			WebEvent.webSocket.onerror = function()
			{
				if (WebEvent.onError) WebEvent.onError();
			};
			
			return true;
		},
		
	disconnect: function()
		{
			if (WebEvent.webSocket) 
			{
				WebEvent.webSocket.close();
				WebEvent.webSocket = null;
			}
			
		},

	subscribe: function (subject)
		{
			if (WebEvent.webSocket)
			{
				var msg = 'SUBSCRIBE ' + subject + ' WebEvent/1.0';
				WebEvent.webSocket.send(msg);
			}
		},
      
	unsubscribe: function (subject)
		{
			if (WebEvent.webSocket)
			{
				var msg = 'UNSUBSCRIBE ' + subject + ' WebEvent/1.0';
				WebEvent.webSocket.send(msg);
			}
		},
		
	notify: function (subject, data)
		{
			if (WebEvent.webSocket)
			{
				var msg = 'NOTIFY ' + subject + ' WebEvent/1.0\r\n' + data;
				WebEvent.webSocket.send(msg);
			}
		},

	onConnect: function() {},

	onDisconnect: function() {},
	
	onError: function() {},
	
	onNotify: function(evt) {},
	
	parseEvent: function(msg)
		{
			var event = {};
			var i = 0;
			var methodStart = i;
			while (i < msg.length && msg[i] != ' ' && msg[i] != '\r' && msg[i] != '\n') i++;
			event.method = msg.substring(methodStart, i);
			while (i < msg.length && msg[i] == ' ') i++;
			var subjectStart = i;
			while (i < msg.length && msg[i] != ' ' && msg[i] != '\r' && msg[i] != '\n') i++;
			event.subject = msg.substring(subjectStart, i);
			while (i < msg.length && msg[i] == ' ') i++;
			var versionStart = i;
			while (i < msg.length && msg[i] != ' ' && msg[i] != '\r' && msg[i] != '\n') i++;
			event.version = msg.substring(versionStart, i);
			while (i < msg.length && (msg[i] == '\r' || msg[i] == '\n')) i++;
			event.data = msg.substring(i);		
			return event;
		}
};
