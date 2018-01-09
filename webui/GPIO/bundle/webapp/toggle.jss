if (!session || !session.authenticated)
{
	logger.error("No session or session not authenticated.");
	response.setStatus(401);
	response.send();
	return;
}

var gpio = form.gpio;
var result = false;

var deviceRefs = serviceRegistry.find('io.macchina.deviceType == "io.macchina.gpio" && name == "' + gpio + '"');
for (var i = 0; i < deviceRefs.length; i++)
{
	var device = deviceRefs[i].instance();

	if (device.getPropertyString("direction") != "out") continue;

	device.toggle();
	result = true;
}

response.contentType = 'application/json';
response.write(JSON.stringify(result));
response.send();
