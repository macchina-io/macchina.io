//
// Playground Sample Script
//
// This script will look for a temperature sensor and, if found,
// output the current temperature.
//
// Feel free to modify this script as you like to try out
// macchina.io features.
//

// Search for temperature sensors in the Service Registry
var temperatureRefs = serviceRegistry.find('io.macchina.physicalQuantity == "temperature"');
if (temperatureRefs.length > 0)
{
    // Found at least one temperature sensor entry in the registry.
    // Resolve the first one.
	var temperatureSensor = temperatureRefs[0].instance();
	// Get current temperature.
	var temperature = temperatureSensor.value();
	logger.information('Current temperature: ' + temperature);
}
else
{
    logger.error('No temperature sensor found.');
}
