// TODO: authentication

var memory = {
    stats: system.exec(system.osName == "Darwin" ? "memory_pressure" : "free")
};

response.contentType = 'application/json';
response.write(JSON.stringify(memory));
response.send();
