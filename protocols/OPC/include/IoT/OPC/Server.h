//
// Server.h
//
// $Id$
//
// Library: OPC
// Package: OPC
// Module:  Server
//
// Definition of the Server class.
//
// Copyright (c) 2010-2015, Günter Obiltschnig.
//
// SPDX-License-Identifier:	BSL-1.0
//


#ifndef IoT_OPC_Server_INCLUDED
#define IoT_OPC_Server_INCLUDED


#include "IoT/OPC/OPC.h"
#include "IoT/OPC/Types.h"
#include "Poco/Runnable.h"
#include "Poco/Any.h"

namespace Poco {
namespace Dynamic {

	class Var;

} } // namespace Poco::Dynamic

namespace IoT {
namespace OPC {
namespace open62541 {

struct UA_Server;
struct UA_ServerNetworkLayer;

}

using namespace open62541;

class OPC_API Server : public Poco::Runnable
	/// This class represents an OPC Server.
{
public:
	
	Server(int port = OPC_STANDARD_PORT);
		/// Creates the Server.

	~Server();
		/// Destroys the Server.

	void run();
		/// Runs the Server.

	void stop();
		/// Stops the Server.

	int addNamespace(const std::string& id);

	void addVariableNode(int nsIndex,
		const Poco::Dynamic::Var& id,
		const Poco::Any& value,
		int type,
		const std::string& qualifiedName,
		const std::string& displayName,
		const std::string& description,
		int parentID = UA_NS0ID_OBJECTSFOLDER,
		int parentRefID = UA_NS0ID_ORGANIZES,
		const std::string& loc = "en_US");

private:
	const void* convertPOD(const Poco::Any& value, int type);
	const void* convertString(const Poco::Any& value, UA_String& str);

	open62541::UA_Server*             _pServer;
	open62541::UA_ServerNetworkLayer* _pNetworkLayer;
	bool                              _running;
	bool                              _done;
	std::string                       _error;
};


//
// inlines
//

} } // namespace IoT::OPC


#endif // IoT_OPC_Server_INCLUDED
