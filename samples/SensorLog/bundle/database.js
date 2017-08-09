//
// database.js
//

var data = require('data');

var path = bundle.persistentDirectory + 'sensorlog.sqlite';
module.exports = {
	path: path,
	session: new data.Session('SQLite', path),
	interval: application.config.getInt('sensorlog.interval', 5000),
	retain: application.config.getInt('sensorlog.retain', 3600)
};
