//
// OPCServer.cpp
//
// $Id$
//
// This sample demonstrates an OPC server.
//
// Copyright (c) 2010-2015, Günter Obiltschnig.
//
// SPDX-License-Identifier:	BSL-1.0
//


#include "IoT/OPC/Server.h"
#include "IoT/OPC/DateTime.h"
#include "Poco/Dynamic/Var.h"
#include <iostream>

using namespace Poco;
using namespace Poco::Dynamic;
using namespace IoT::OPC;


int main(int argc, char** argv)
{
	try
	{
		Server srv;

		int nsIndex = 1;
		Var id = "the.int.answer";
		std::string name = "the int answer";
		srv.addVariableNode(nsIndex, id, 42, UA_TYPES_INT32, false, name, name, name);

		nsIndex = srv.addNamespace("ns2");
		id = "the.double.answer";
		name = "the double answer";
		srv.addVariableNode(nsIndex, id, 4.2, UA_TYPES_DOUBLE, false, name, name, name);

		id = 3;
		name = "the double answer by ID in ns2";
		srv.addVariableNode(nsIndex, id, 2.4, UA_TYPES_DOUBLE, false, name, name, name);

		id = 4;
		name = "the string answer by ID in ns2";
		srv.addVariableNode(nsIndex, id, std::string("abc123"), UA_TYPES_STRING, false, name, name, name);

		id = 5;
		name = "the DateTime answer by ID in ns2";
		Poco::Int64 ts = IoT::OPC::DateTime::now();
		srv.addVariableNode(nsIndex, id, ts, UA_TYPES_DATETIME, false, name, name, name);

		srv.run();
	}
	catch(Poco::Exception& ex)
	{
		std::cout << ex.displayText() << std::endl;
		return -1;
	}
	return 0;
}
