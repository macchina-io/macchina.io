//
// WebEventNotifier/WebSocket Sample
//

var sensors = require('sensors');

function watchSensor(id, sensor)
{
	sensor.on('valueChanged', function(evt) {
		logger.debug('Sensor "%s" value changed: %o', id, evt.data);
		webEventNotifier.notify('sensorlog.' + id, '' + evt.data);
	});
}

var webEventNotifier;
var webEventNotifierRef = serviceRegistry.findByName('io.macchina.services.webeventnotifier');
if (webEventNotifierRef)
{
    logger.debug('WebEventNotifier found.');
    webEventNotifier = webEventNotifierRef.instance();

	for (var id in sensors)
	{
		watchSensor(id, sensors[id].sensor);
	}	
}
