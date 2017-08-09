//
// meta.jss
//
// Return a JSON document with sensor meta data.
//

var sensors = require('sensors');

var colors = [
	'rgba(237,70,47,1.0)',
	'rgba(60,129,6,1.0)',
	'rgba(34,74,251,1.0)'
];

var data = {};
var index = 0;
for (var id in sensors)
{
	var sensor = sensors[id].sensor;
	var physicalQuantity = sensor.getPropertyString('physicalQuantity');
	var physicalUnit = sensor.getPropertyString('physicalUnit');
	var title = sensors[id].title;
	if (!title) title = physicalQuantity;
	var color = sensors[id].color;
	if (!color) color = colors[index % colors.length];
	
	data[id] = {
	    id: id,
	    index: index++,
		physicalQuantity: physicalQuantity,
		physicalUnit: physicalUnit,
		title: title,
		color: color
	};
}

response.contentType = 'application/json';
response.write(JSON.stringify(data));
response.send();
