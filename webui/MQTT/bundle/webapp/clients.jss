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
		var clientInfo = {};
		clientInfo.id = client.id();
		clientInfo.name = clientRef.name;
		clientInfo.serverURI = client.serverURI();
		clientInfo.connected = client.connected();
		clientInfo.subscribedTopics = client.subscribedTopics();
		clientInfo.statistics = client.statistics();

		clients.push(clientInfo);
	}
}

response.contentType = 'application/json';
response.write(JSON.stringify(clients));
response.send();
