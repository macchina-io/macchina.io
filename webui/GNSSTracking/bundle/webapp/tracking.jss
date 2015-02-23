// TODO: authentication

var trackingData = {
	available: false,
	valid: false
};

var gnssSensor = null;
var gnssSensorRefs = serviceRegistry.find('io.macchina.device =~ /.*(gnss|gps)/');
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
    }
}

response.contentType = 'application/json';
response.write(JSON.stringify(trackingData));
response.send();
