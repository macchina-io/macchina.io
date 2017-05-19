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
		std::cout << "Server DateTime is: [" << cli.readServerDateTime() << ']' << std::endl;
		int nsIndex = 1;
		std::cout << "Node [" << nsIndex << ":\"the.int.answer\"]: " << cli.readInt32(nsIndex,
				"the.int.answer") << std::endl;
		std::cout << "Node [" << nsIndex << ":\"the.double.answer\"]: " << cli.readDouble(nsIndex,
				"the.double.answer") << std::endl;
	}
	catch(Poco::Exception& ex)
	{
		std::cout << ex.displayText() << std::endl;
		return -1;
	}
	return 0;
}
