//
// SensorLog Logger
//

var sensors = require('sensors');
var db = require('database');

db.session.execute('PRAGMA journal_mode=WAL');
db.session.execute('CREATE TABLE IF NOT EXISTS sensorlog ( \
	timestamp LONG, \
	sensor VARCHAR, \
	value FLOAT \
	)');

setInterval(
	function()
	{
		var ts = Math.floor(DateTime().timestamp/1000);
		for (var id in sensors)
		{
			var sensor = sensors[id].sensor;

			db.session.execute('INSERT INTO sensorlog VALUES (?, ?, ?)',
				ts,
				id,
				sensor.value());
		}
	},
	db.interval);

setInterval(
	function()
	{
		var cutoffTime = DateTime().timestamp/1000 - 1000*db.retain;
		db.session.execute('DELETE FROM sensorlog WHERE timestamp < ?', cutoffTime);
	},
	db.retain*1000);
