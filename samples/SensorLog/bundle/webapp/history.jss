//
// history.jss
//
// Return a JSON document with sensor samples.
//

var db = require('database');

var data = [];

db.session.pageSize = form.maxItems ? parseInt(form.maxItems) : 20;
var sensor = form.sensor;
var since = form.since ? parseInt(form.since) : 0;

var recordSet = db.session.execute('SELECT timestamp, value FROM sensorlog WHERE timestamp > ? AND sensor == ? ORDER BY timestamp DESC', since, sensor);
for (var row = 0; row < recordSet.rowCount; row++)
{
	var timestamp = recordSet.getValue('timestamp');
	var value = recordSet.getValue('value');
	data[recordSet.rowCount - row - 1] = 
		{
			timestamp: timestamp,
			value: value
		};
	recordSet.moveNext();
}
recordSet.close();

response.contentType = 'application/json';
response.write(JSON.stringify(data));
response.send();
