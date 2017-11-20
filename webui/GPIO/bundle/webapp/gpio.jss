if (!session || !session.authenticated)
{
	logger.error("No session or session not authenticated.");
	response.setStatus(401);
	response.send();
	return;
}

var devices = [];

var deviceRefs = serviceRegistry.find('io.macchina.deviceType == "io.macchina.gpio"');
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
		if (device.hasProperty("direction")) {
			deviceInfo.direction = device.getPropertyString("direction");
		} else {
			deviceInfo.direction = "";
		}
		if (device.hasProperty("state")) {
			deviceInfo.state = device.getPropertyBool("state");
		} else {
			deviceInfo.state = false;
		}
		if (device.hasProperty("displayValue")) {
			deviceInfo.displayValue = device.getPropertyString("displayValue");
		} else if (device.hasProperty("displayState")) {
			deviceInfo.displayValue = device.getPropertyString("displayState");
		} else {
			deviceInfo.displayValue = "";
		}
		devices.push(deviceInfo);
	}
}

response.contentType = 'application/json';
response.write(JSON.stringify(devices));
response.send();
