//
// params.jss
//
// Return a JSON document with global parameters.
//

var params = {
	refresh: application.config.getInt('sensorlog.chart.refresh', 5000),
	points: application.config.getInt('sensorlog.chart.points', 20)
};

response.contentType = 'application/json';
response.write(JSON.stringify(params));
response.send();
