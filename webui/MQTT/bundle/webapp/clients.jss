if (!session || !session.authenticated)
{
	logger.error("No session or session not authenticated.");
	response.setStatus(401);
	response.send();
	return;
}

function versionString(version)
{
	switch (version)
	{
	case 0:
		return '3.1/3.1.1';
	case 3:
		return '3.1';
	case 4:
		return '3.1.1';
	case 5:
		return '5';
	default:
		return 'unknown';
	}
}

function clientVersion(client)
{
	if (client.connected())
	{
		return versionString(client.connectionInfo().mqttVersion);
	}
	else
	{
		return versionString(client.mqttVersion());
	}
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
			version: clientVersion(client),
			subscribedTopics: client.subscribedTopics(),
			statistics: client.statistics()
		};
		clients.push(clientInfo);
	}
}

response.contentType = 'application/json';
response.write(JSON.stringify(clients));
response.send();
