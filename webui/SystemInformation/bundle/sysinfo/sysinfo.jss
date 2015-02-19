// TODO: authentication

var dateTime = new LocalDateTime();
var sysInfo = {
    nodeName: system.nodeName,
    nodeId: system.nodeId,
    osName: system.osName,
    osVersion: system.osVersion,
    osArch: system.osArchitecture,
    processorCount: system.processorCount,
    dateTime: dateTime.format("sortable")
};

response.contentType = 'application/json';
response.write(JSON.stringify(sysInfo));
response.send();
