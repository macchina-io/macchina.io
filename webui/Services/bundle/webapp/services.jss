if (!session || !session.authenticated)
{
	logger.error("No session or session not authenticated.");
	response.setStatus(401);
	response.send();
	return;
}

var services = [];

var serviceRefs = serviceRegistry.find('type != ""');
for (let serviceRef of serviceRefs)
{
	let props = [];
	let hasJSBridge = false;
	for (var p in serviceRef.toJSON())
	{
		if (p !== 'dtype' && p !== 'type' && p != 'name')
		{
			props.push({
				name: p,
				value: serviceRef[p]
			});
			if (p === "jsbridge") hasJSBridge = true;
		}
	}

	services.push({
		name: serviceRef.name,
		dtype: serviceRef.dtype,
		jsbridge: hasJSBridge,
		properties: props
	});
}

response.contentType = 'application/json';
response.write(JSON.stringify(services));
response.send();
