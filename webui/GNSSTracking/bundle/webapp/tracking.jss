if (!session || !session.authenticated)
{
	logger.error("No session or session not authenticated.");
	response.setStatus(401);
	response.send();
	return;
}

var trackingData = {
	available: false,
	valid: false
};

var gnssSensor = null;
var gnssSensorRefs = serviceRegistry.find('io.macchina.deviceType == "io.macchina.gnss"');
if (gnssSensorRefs.length > 0)
{
	trackingData.available = true;
    gnssSensor = gnssSensorRefs[0].instance();
    if (gnssSensor.positionAvailable())
    {
    	trackingData.position = gnssSensor.position();
    	trackingData.course = gnssSensor.course();
    	trackingData.speed = gnssSensor.speed();
    	trackingData.altitude = gnssSensor.altitude();
    	trackingData.hdop = gnssSensor.hdop();
    	trackingData.valid = true;
    	trackingData.source = gnssSensor.getPropertyString("name");
    	trackingData.refresh = 1000*application.config.getInt("webui.gnsstracking.refresh", 10);
    }
}

response.contentType = 'application/json';
response.write(JSON.stringify(trackingData));
response.send();
