//
// params.jss
//
// Return a JSON document with global parameters.
//

var params = {
	refresh: application.config.getInt('sensorlog.refresh', 5000)
};

response.contentType = 'application/json';
response.write(JSON.stringify(params));
response.send();
