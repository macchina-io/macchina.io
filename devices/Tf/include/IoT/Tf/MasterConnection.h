//
// MasterConnection.h
//
// $Id: //iot/Main/Tf/include/IoT/Tf/MasterConnection.h#2 $
//
// Copyright (c) 2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_Tf_MasterConnection_INCLUDED
#define IoT_Tf_MasterConnection_INCLUDED


#include "IoT/Tf/Tf.h"
#include "Poco/BasicEvent.h"
#include "Poco/RefCountedObject.h"
#include "Poco/AutoPtr.h"


namespace IoT {
namespace Tf {


class IoTTf_API MasterConnection: public Poco::RefCountedObject
{
public:
	typedef Poco::AutoPtr<MasterConnection> Ptr;

	enum DeviceState
	{
		DEVICE_AVAILABLE,
		DEVICE_CONNECTED,
		DEVICE_DISCONNECTED
	};
	
	struct Version
	{
		Poco::UInt8 major;
		Poco::UInt8 minor;
		Poco::UInt8 revision;
	};
	
	struct DeviceEvent
	{
		DeviceState  state;
		Version      hardwareVersion;
		Version      firmwareVersion;
		std::string  uid;
		std::string  masterUID;
		char         position;
		Poco::UInt16 type;
	};
	
	Poco::BasicEvent<const DeviceEvent> deviceStateChanged;

	~MasterConnection();
		/// Destroys the MasterConnection.
		
	virtual void connect(const std::string& host = "localhost", Poco::UInt16 port = 4223) = 0;
		/// Connects to the server/brick daemon at the given
		/// host and port. 
		
	virtual void disconnect() = 0;
		/// Disconnects from the server.
		
	virtual bool connected() const = 0;
		/// Returns true if the MasterConnection is connected
		/// to a server.
		
	static Ptr create();
		/// Creates a MasterConnection instance.

protected:
	MasterConnection();
		/// Creates an unconnected MasterConnection.
};


} } // namespace IoT::Tf


#endif // IoT_Tf_MasterConnection_INCLUDED
