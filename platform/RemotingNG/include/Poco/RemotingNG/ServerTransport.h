//
// ServerTransport.h
//
// $Id: //poco/1.6/RemotingNG/include/Poco/RemotingNG/ServerTransport.h#1 $
//
// Library: RemotingNG
// Package: Transport
// Module:  ServerTransport
//
// Definition of the ServerTransport class.
//
// Copyright (c) 2006-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef RemotingNG_ServerTransport_INCLUDED
#define RemotingNG_ServerTransport_INCLUDED


#include "Poco/RemotingNG/RemotingNG.h"
#include "Poco/RemotingNG/SerializerBase.h"


namespace Poco {
namespace RemotingNG {


class Serializer;
class Deserializer;


class RemotingNG_API ServerTransport
	/// ServerTransport objects are used as mediators between
	/// a Listener, receiving a request, and the ORB, Skeleton and
	/// MethodHandlers, processing the request.
	///
	/// The ServerTransport allows the Skeleton to deserialize the
	/// request message in order to determine the method name,
	/// select an appropriate MethodHandler, based on the method 
	/// name and pass control to the MethodHandler. The 
	/// MethodHandler then uses the ServerTransport to send
	/// back a response message.
{
public:
	ServerTransport();
		/// Creates a ServerTransport.

	virtual ~ServerTransport();
		/// Destroys the ServerTransport.

	virtual Deserializer& beginRequest() = 0;
		/// Prepare a Deserializer for reading the request message.
		///
		/// Returns a Deserializer that can be used to read the
		/// request message.
		
	virtual Serializer& sendReply(SerializerBase::MessageType messageType) = 0;
		/// Prepares the ServerTransport to send a response message back to
		/// the caller.
		///
		/// The given MessageType must be either MESSAGE_REPLY, MESSAGE_EVENT_REPLY
		/// or MESSAGE_FAULT.
		///
		/// Returns a Serializer for writing the reply (or fault reply) message.
	
	virtual void endRequest() = 0;
		/// Signals the ServerTransport that request processing is
		/// finished for this request.

private:
	ServerTransport(const ServerTransport&);
	ServerTransport& operator = (const ServerTransport&);
};


} } // namespace Poco::RemotingNG


#endif // RemotingNG_Transport_INCLUDED
