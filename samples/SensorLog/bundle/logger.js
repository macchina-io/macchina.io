//
// SensorLog Logger
//

var sensors = require('sensors');
var db = require('database');

db.session.execute('PRAGMA journal_mode=WAL');
db.session.execute('CREATE TABLE IF NOT EXISTS sensorlog ( \
	timestamp INTEGER, \
	sensor VARCHAR, \
	value FLOAT \
	)');

setInterval(
	function()
	{
		for (var id in sensors)
		{
			var sensor = sensors[id].sensor;

			db.session.execute('INSERT INTO sensorlog VALUES (?, ?, ?)',
				DateTime().epoch,
				id,
				sensor.value());
		}
	},
	db.logIntervalSeconds*1000);

setInterval(
	function()
	{
		var cutoffTime = DateTime().epoch - db.keepDataSeconds;
		db.session.execute('DELETE FROM datalog WHERE timestamp < ?', cutoffTime);
	},
	db.keepDataSeconds*1000);
