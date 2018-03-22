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
	var physicalQuantity;
	if (sensor.hasProperty('physicalQuantity'))
		physicalQuantity = sensor.getPropertyString('physicalQuantity');
	else
		physicalQuantity = '';
	var physicalUnit;
	var displayUnit;
	if (sensor.hasProperty('physicalUnit'))
	{
		physicalUnit = sensor.getPropertyString('physicalUnit');
		var uomRef = serviceRegistry.findByName('io.macchina.services.unitsofmeasure');
		if (uomRef)
			displayUnit = uomRef.instance().format(physicalUnit);
		else
			displayUnit = physicalUnit;
	}
	else
	{
		physicalUnit = '';
		displayUnit = '';
	}
	var title = sensors[id].title;
	if (!title) title = physicalQuantity;
	var color = sensors[id].color;
	if (!color) color = colors[index % colors.length];

	data[id] = {
	    id: id,
	    index: index++,
		physicalQuantity: physicalQuantity,
		physicalUnit: physicalUnit,
		displayUnit: displayUnit,
		title: title,
		color: color
	};
}

response.contentType = 'application/json';
response.write(JSON.stringify(data));
response.send();
