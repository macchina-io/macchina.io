// TODO: authentication

var processes = {
    list: system.exec(system.osName == "Darwin" ? "top -l 1" : "top -b -n1")
};

response.contentType = 'application/json';
response.write(JSON.stringify(processes));
response.send();
