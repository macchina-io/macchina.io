if (!session || !session.authenticated)
{
	logger.error("No session or session not authenticated.");
	response.setStatus(401);
	response.send();
	return;
}

var devices = [];

var deviceRefs = serviceRegistry.find('io.macchina.device != ""');
for (var i = 0; i < deviceRefs.length; i++)
{
	var deviceRef = deviceRefs[i];
	var device = deviceRef.instance();
	if (device)
	{
		var deviceInfo = {};
		deviceInfo.id = deviceRef.name;
		deviceInfo.name = device.getPropertyString("name");
		deviceInfo.type = device.getPropertyString("type");
		deviceInfo.symbolicName = device.getPropertyString("symbolicName");
		if (device.hasProperty("physicalQuantity"))
		{
			deviceInfo.physicalQuantity = device.getPropertyString("physicalQuantity");
		}
		else
		{
			deviceInfo.physicalQuantity = "";
		}
		if (device.hasProperty("physicalUnit"))
		{
			deviceInfo.physicalUnit = device.getPropertyString("physicalUnit");
			var uomRef = serviceRegistry.findByName('io.macchina.services.unitsofmeasure');
			if (uomRef)
			{
				deviceInfo.displayUnit = uomRef.instance().format(deviceInfo.physicalUnit);
			}
			else
			{
				deviceInfo.displayUnit = deviceInfo.physicalUnit;
			}
		}
		else
		{
			deviceInfo.physicalUnit = "";
			deviceInfo.displayUnit = "";
		}
		if (device.hasProperty("displayValue"))
		{
			deviceInfo.displayValue = device.getPropertyString("displayValue") + " " + deviceInfo.displayUnit;
		}
		else if (device.hasProperty("displayState"))
		{
			deviceInfo.displayValue = device.getPropertyString("displayState");
		}
		else
		{
			deviceInfo.displayValue = "";
		}
		devices.push(deviceInfo);
	}
}

response.contentType = 'application/json';
response.write(JSON.stringify(devices));
response.send();
