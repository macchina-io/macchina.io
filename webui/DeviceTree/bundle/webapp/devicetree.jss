if (!session || !session.authenticated)
{
	logger.error("No session or session not authenticated.");
	response.setStatus(401);
	response.send();
	return;
}

var deviceTreeRef = serviceRegistry.findByName('io.macchina.deviceTree');
var deviceTree;
if (deviceTreeRef)
{
	deviceTree = deviceTreeRef.instance();
}

var devices = [];

function createDeviceInfo(deviceRef)
{
	var deviceInfo = {};
	var device = deviceRef.instance();
	deviceInfo.id = deviceRef.name;
	deviceInfo.name = device.getPropertyString("name");
	deviceInfo.type = device.getPropertyString("type");
	deviceInfo.symbolicName = device.getPropertyString("symbolicName");
	if (device.hasProperty("physicalQuantity"))
	{
		deviceInfo.physicalQuantity = device.getPropertyString("physicalQuantity");
	}
	else
	{
		deviceInfo.physicalQuantity = "";
	}
	if (device.hasProperty("physicalUnit"))
	{
		deviceInfo.physicalUnit = device.getPropertyString("physicalUnit");
		var uomRef = serviceRegistry.findByName('io.macchina.services.unitsofmeasure');
		if (uomRef)
		{
			deviceInfo.displayUnit = uomRef.instance().format(deviceInfo.physicalUnit);
		}
		else
		{
			deviceInfo.displayUnit = deviceInfo.physicalUnit;
		}
	}
	else
	{
		deviceInfo.physicalUnit = "";
		deviceInfo.displayUnit = "";
	}
	if (device.hasProperty("displayValue"))
	{
		deviceInfo.displayValue = device.getPropertyString("displayValue");
	}
	else if (device.hasProperty("displayState"))
	{
		deviceInfo.displayValue = device.getPropertyString("displayState");
	}
	else
	{
		deviceInfo.displayValue = "";
	}
	return deviceInfo;
}

function traverseDeviceTree(deviceTree, id)
{
	const deviceRef = serviceRegistry.findByName(id);
    const deviceNode = deviceTree.deviceById(id);
	const deviceInfo = createDeviceInfo(deviceRef);
    if (deviceNode.fragments)
    {
        deviceInfo.fragments = [];
        for (const f of deviceNode.fragments)
        {
            const subNode = deviceTree.deviceById(f);
            var subDeviceInfo = traverseDeviceTree(deviceTree, subNode.id);
            deviceInfo.fragments.push(subDeviceInfo);
        }
    }
    return deviceInfo;
}

const rootInfo = traverseDeviceTree(deviceTree, 'io.macchina.composite.root');

devices.push(rootInfo);

var deviceRefs = serviceRegistry.find('io.macchina.device != "" && io.macchina.nodeName == ""');
for (const ref of deviceRefs)
{
	devices.push(createDeviceInfo(ref));
}

response.contentType = 'application/json';
response.write(JSON.stringify(devices));
response.send();
