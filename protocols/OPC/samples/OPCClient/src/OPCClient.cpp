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


#include "IoT/OPC/Client.h"
#include "Poco/Types.h"
#include "IoT/OPC/Types.h"
#include <iostream>


using namespace Poco;
using namespace IoT::OPC;


int main(int argc, char** argv)
{
	try
	{
		int port = OPC_STANDARD_PORT;
		if(argc > 1) port = Poco::NumberParser::parse(argv[1]);
		Client cli("localhost", port, Message::PRIO_TRACE);
		cli.printEndpointURLs(std::cout);
		cli.connect();

		std::cout << "Server DateTime is: [" << cli.readServerDateTimeStr() << ']' << std::endl << std::endl;
		std::cout << "Server objects:" << std::endl;
		cli.printServerObjects(std::cout);
#if 0
		std::cout << std::endl  << "Object values:" << std::endl;

		int nsIndex = 1;
		std::string name = "the.int.answer";
		int val = cli.readInt32ByName(nsIndex, name);
		std::cout<< "Node [" << nsIndex << ", \"" << name << "\"]: " << val << std::endl;

		val += 1;
		std::cout<< "Writing value " << val << " to Node [" << nsIndex << ", \"" << name << "\"]" << std::endl;
		cli.write(nsIndex, name, val);
		val = cli.readInt32ByName(nsIndex, name);
		std::cout<< "Node [" << nsIndex << ", \"" << name << "\"]: " << val << std::endl;

		nsIndex = 2;
		name = "the.double.answer";
		std::cout << "Node [" << nsIndex << ", \"" << name << "\"]: " << cli.readDoubleByName(nsIndex, name) << std::endl;

		int id = 3;
		std::cout << "Node [" << nsIndex << ", " << id << "]: " << cli.readDoubleByID(nsIndex, 3) << std::endl;

		id = 4;
		std::string str = cli.readStringByID(nsIndex, id);
		std::cout << "Node [" << nsIndex << ", " << id << "]: " << str << std::endl;
		std::cout << "Reversing " << str << " => ";
		std::reverse(str.begin(), str.end());
		std::cout << str << std::endl;
		cli.write(nsIndex, id, str);
		str = cli.readStringByID(nsIndex, id);
		std::cout << "Node [" << nsIndex << ", " << id << "]: " << str << std::endl;

		id = 5;
		std::cout << "Node [" << nsIndex << ", " << id << "]: " << cli.readStrDateTimeByID(nsIndex, 5) << std::endl;
#endif
	}
	catch(Poco::Exception& ex)
	{
		std::cout << ex.displayText() << std::endl;
		return -1;
	}
	return 0;
}
