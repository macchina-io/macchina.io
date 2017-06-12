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
#include "Poco/Logger.h"
#include "Poco/Message.h"
#include "Poco/ConsoleChannel.h"
#include "Poco/AutoPtr.h"
#include "Poco/Any.h"


namespace Poco {
namespace Dynamic {

	class Var;

} } // namespace Poco::Dynamic


struct UA_Server;
struct UA_ServerNetworkLayer;


namespace IoT {
namespace OPC {


class OPC_API Server : public Poco::Runnable
	/// This class represents an OPC Server.
{
public:
	Server(int port, Poco::Message::Priority prio = Poco::Message::PRIO_INFORMATION);
		/// Creates the Server.
	
	Server(Poco::Logger& logger = Poco::Logger::create("IoT_OPC_Server",
			Poco::AutoPtr<Poco::ConsoleChannel>(new Poco::ConsoleChannel)),
		int port = OPC_STANDARD_PORT);
		/// Creates the Server.

	~Server();
		/// Destroys the Server.

	void run();
		/// Runs the Server.

	void stop();
		/// Stops the Server.

	void setLogLevel(Poco::Message::Priority prio)
	{
		_logger.setLevel(prio);
	}

	int addNamespace(const std::string& id);

	void addVariableNode(int nsIndex,
		const Poco::Dynamic::Var& id,
		const Poco::Any& value,
		int type,
		bool array,
		const std::string& qualifiedName,
		const std::string& displayName,
		const std::string& description,
		int parentID = UA_NS0ID_OBJECTSFOLDER,
		int parentRefID = UA_NS0ID_ORGANIZES,
		const std::string& loc = "en_US");

private:
	void init();
	static UA_ServerNetworkLayer* makeServerNetworkLayer(int port);

	const void* convertPOD(const Poco::Any& value, int type);
	const void* convertPODArray(const Poco::Any& value, int type, std::size_t& sz);
	const void* convertString(const Poco::Any& value, UA_String& str);
	const void* convertStringArray(const Poco::Any& value, std::vector<UA_String>& str);

	UA_Server*             _pServer;
	Poco::Logger&          _logger;
	UA_ServerNetworkLayer* _pNetworkLayer;
	bool                   _running;
	bool                   _done;
	std::string            _error;
};


//
// inlines
//

UA_ServerNetworkLayer* Server::makeServerNetworkLayer(int port)
{
	return new UA_ServerNetworkLayer(UA_ServerNetworkLayerTCP(UA_ConnectionConfig_standard, static_cast<UA_UInt16>(port)));
}


} } // namespace IoT::OPC


#endif // IoT_OPC_Server_INCLUDED
