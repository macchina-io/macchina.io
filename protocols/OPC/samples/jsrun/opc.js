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

// read and log some values by name
var nsIdx = 1;
var name = "the.int.answer";
log(name + ': [' + opc.read(nsIdx, name) + ']');
// switch namespace
nsIdx = 2;
name = "the.double.answer";
log(name + ': [' + opc.read(nsIdx, name) + ']');

// read and log some values by index
var idx = 3;
log(idx.toString() + ': [' + opc.read(nsIdx, idx) + ']');
idx = 4;
log(idx.toString() + ': [' + opc.read(nsIdx, idx) + ']');
idx = 5;
log(idx.toString() + ': [' + opc.read(nsIdx, idx) + ']');