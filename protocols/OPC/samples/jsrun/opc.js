//
// OPC example
//
// for this script to execute succesfully, the protocols/OPC/samples/OPCServer
// application must be running on localhost
//

var log = function(msg) { application.logger.information(msg); }

// connect
var addr = "localhost";
log('Connecting to [' + addr + '] ...');
var opc = new OPCClient(addr);
log('Connected.');

// retrieve and log server date/time
log('Server DateTime: [' + opc.serverDateTime() + ']');

// read/write and log some values by name
var nsIdx = 1;
var name = "the.int.answer";
var i = opc.read(nsIdx, name);
log(name + ': [' + i + ']');
log("Write " + ++i);
opc.write(nsIdx, name, i);
i = 0;
i = opc.read(nsIdx, name);
log(name + ': [' + i + ']');

// switch namespace
nsIdx = 2;
name = "the.double.answer";
log(name + ': [' + opc.read(nsIdx, name) + ']');

// read/write and log some values by index
var idx = 3;
log(idx.toString() + ': [' + opc.read(nsIdx, idx) + ']');

idx = 4;
var str = opc.read(nsIdx, idx);
log(idx.toString() + ': [' + str + ']');
str = str.split("").reverse().join("");
log("Write reversed value: " + str);
opc.write(nsIdx, idx, str);
str = opc.read(nsIdx, idx);
log(idx.toString() + ': [' + str + ']');

idx = 5;
log(idx.toString() + ': [' + opc.read(nsIdx, idx) + ']');

var date = new Date;
log("Write current DateTime: " + date);
opc.write(nsIdx, idx, date);
log(idx.toString() + ': [' + opc.read(nsIdx, idx) + ']');

date = Date.now();
log("Write current timestamp: " + date);
opc.write(nsIdx, idx, date);
date = opc.read(nsIdx, idx);
log("Read " + Object.prototype.toString.call(date));
log(idx.toString() + ': [' + date.valueOf() + "] => " + date);
