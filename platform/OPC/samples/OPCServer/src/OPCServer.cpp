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


#include "Poco/OPC/Server.h"

using namespace Poco::OPC;

int main(int argc, char** argv)
{
	Server srv;
	srv.addVariableNode(1, "the.int.answer", 42, UA_TYPES_INT32);
	srv.addVariableNode(1, "the.double.answer", 4.2, UA_TYPES_DOUBLE);
	srv.run();
	return 0;
}
