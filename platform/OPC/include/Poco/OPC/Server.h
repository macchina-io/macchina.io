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


#ifndef OPC_Server_INCLUDED
#define OPC_Server_INCLUDED


#include "Poco/OPC/OPC.h"
#include "Poco/OPC/Types.h"
#include "Poco/Runnable.h"
#include "Poco/Any.h"

namespace Poco {

/*
template <typename ValueType>
void* VoidPtrAnyCast(const Any* operand)
{
	return (void*) static_cast<Any::Holder<ValueType>*>(operand->content())->_held;
}
*/
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
	
	Server(int port = 16664);
		/// Creates the Server.

	~Server();
		/// Destroys the Server.

	void run();
		/// Runs the Server.

	void stop();
		/// Stops the Server.

	void addVariableNode(int nsIndex, const std::string& id, const Any& value, int type);

private:
	const void* convert(const Any& value, int type);

	open62541::UA_Server*             _pServer;
	open62541::UA_ServerNetworkLayer* _pNetworkLayer;
	bool                              _running;
	bool                              _done;
};


//
// inlines
//

} } // namespace Poco::OPC


#endif // OPC_Server_INCLUDED
