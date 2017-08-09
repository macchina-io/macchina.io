//
// current.jss
//
// Return a JSON document with current sensor data.
//

var sensors = require('sensors');

var data = {};
for (var id in sensors)
{
	var sensor = sensors[id].sensor;
	data[id] = sensor.value();
}

response.contentType = 'application/json';
response.write(JSON.stringify(data));
response.send();
