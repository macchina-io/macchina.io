if (!session || !session.authenticated) {
    logger.error("No session or session not authenticated.");
    response.setStatus(401);
    response.send();
    return;
}

var gpio = decodeURIComponent(form.gpio);
result = false;

var deviceRefs = serviceRegistry.find('io.macchina.device != ""');
for (var i = 0; i < deviceRefs.length; i++) {
    var deviceRef = deviceRefs[i];

    if (deviceRef.name != gpio) {
        continue;
    }

    var device = deviceRef.instance();

    if (device) {
        if (device.getPropertyString("symbolicName") != "io.macchina.linux.gpio") {
            continue;
        }

        if (device.getPropertyString("direction") != "out") {
            continue;
        }

        state = device.getPropertyBool("state");
        device.setPropertyBool("state", !state);
        result = true;
    }
}

response.contentType = 'application/json';
response.write(JSON.stringify(result));
response.send();
