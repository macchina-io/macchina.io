if (!session || !session.authenticated)
{
	logger.error("No session or session not authenticated.");
	response.setStatus(401);
	response.send();
	return;
}

var clients = [];

var clientRefs = serviceRegistry.find('io.macchina.mqtt.id != ""');
for (var i = 0; i < clientRefs.length; i++)
{
	var clientRef = clientRefs[i];
	var client = clientRef.instance();
	if (client)
	{
		var clientInfo = {
			id: clientRef["io.macchina.mqtt.id"],
			clientId: client.id(),
			name: clientRef.name,
			serverURI: client.serverURI(),
			connected: client.connected(),
			subscribedTopics: client.subscribedTopics(),
			statistics: client.statistics()
		};
		clients.push(clientInfo);
	}
}

response.contentType = 'application/json';
response.write(JSON.stringify(clients));
response.send();
