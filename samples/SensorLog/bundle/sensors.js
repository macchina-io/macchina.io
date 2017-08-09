//
// sensors.js
//
// Find sensor objects, based on sensorlog.sensors configuration.
//

var sensors = {};

var baseKey = 'sensorlog.sensors';
var keys = application.config.keys(baseKey);

for (var i = 0; i < keys.length; i++)
{
	var key = keys[i];
    var fullKey = baseKey + '.' + key;
    var idKey = fullKey + '.id';
    var queryKey = fullKey + '.query';
    var colorKey = fullKey + '.color';
    var titleKey = fullKey + '.title';
    
    var sensorRef = null;
    var color = null;
    var title = null;

    if (application.config.has(idKey))
    {
        var id = application.config.getString(idKey);
        sensorRef = serviceRegistry.findByName(id);
    }
    else if (application.config.has(queryKey))
    {
        var query = application.config.getString(queryKey);
        var sensorRefs = serviceRegistry.find(query);
        if (sensorRefs.length > 0)
            sensorRef = sensorRefs[0];
    }
    if (application.config.has(colorKey))
    {
    	color = application.config.getString(colorKey);
    }
    if (application.config.has(titleKey))
    {
    	title = application.config.getString(titleKey);
    }
    
    if (sensorRef)
    {
        logger.debug('Found Sensor: %O', sensorRef);
        sensors[sensorRef.name] = {
        	id: sensorRef.name,
        	sensor: sensorRef.instance(),
        	color: color,
        	title: title
        };
    }
}

module.exports = sensors;
