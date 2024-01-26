if (!session || !session.authenticated)
{
	logger.error("No session or session not authenticated.");
	response.setStatus(401);
	response.send();
	return;
}

var values = [];

var deviceRefs = serviceRegistry.find('io.macchina.device != "" && io.macchina.device != "io.macchina.composite"');
for (const deviceRef of deviceRefs)
{
	var device = deviceRef.instance();
	if (device)
	{
		var keyValue = {};
		keyValue.key = deviceRef.name;
		if (device.hasProperty("displayValue"))
		{
			keyValue.value = device.getPropertyString("displayValue");
		}
		else if (device.hasProperty("displayState"))
		{
			keyValue.value = device.getPropertyString("displayState");
		}
		else
		{
			keyValue.value = "";
		}
		values.push(keyValue);
	}
}

response.contentType = 'application/json';
response.write(JSON.stringify(values));
response.send();
