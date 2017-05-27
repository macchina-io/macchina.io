//
// OPCClient.cpp
//
// $Id$
//
// This sample demonstrates an OPC client.
//
// Copyright (c) 2010-2015, Günter Obiltschnig.
//
// SPDX-License-Identifier:	BSL-1.0
//


#include "Poco/OPC/Client.h"
#include "Poco/Types.h"
#include "Poco/OPC/Types.h"
#include <iostream>


using namespace Poco;
using namespace Poco::OPC;


int main(int argc, char** argv)
{
	try
	{
		Client cli("localhost");
		cli.printEndpointURLs(std::cout);
		cli.connect();
		std::cout << "Server DateTime is: [" << cli.readServerDateTimeStr() << ']' << std::endl << std::endl;
		std::cout << "Server objects:" << std::endl;
		cli.printServerObjects(std::cout);

		std::cout << std::endl  << "Object values:" << std::endl;
		int nsIndex = 1;
		std::cout<< "Node [" << nsIndex << ", \"the.int.answer\"]: " << cli.readInt32ByName(nsIndex,
				"the.int.answer") << std::endl;

		nsIndex = 2;
		std::cout << "Node [" << nsIndex << ", \"the.double.answer\"]: " << cli.readDoubleByName(nsIndex,
				"the.double.answer") << std::endl;

		int id = 3;
		std::cout << "Node [" << nsIndex << ", " << id << "]: " << cli.readDoubleByID(nsIndex, 3) << std::endl;

		id = 4;
		std::cout << "Node [" << nsIndex << ", " << id << "]: " << cli.readStringByID(nsIndex, 4) << std::endl;

		id = 5;
		std::cout << "Node [" << nsIndex << ", " << id << "]: " << cli.readStrDateTimeByID(nsIndex, 5) << std::endl;
	}
	catch(Poco::Exception& ex)
	{
		std::cout << ex.displayText() << std::endl;
		return -1;
	}
	return 0;
}
