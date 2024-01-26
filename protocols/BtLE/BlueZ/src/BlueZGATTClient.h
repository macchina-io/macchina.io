//
// BlueZGATTClient.h
//
// Library: IoT/BtLE
// Package: BtLE
// Module:  BlueZGATTClient
//
// Definition of the BlueZGATTClient class.
//
// Copyright (c) 2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef IoT_BtLE_BlueZGATTClient_INCLUDED
#define IoT_BtLE_BlueZGATTClient_INCLUDED


#include "HelperClient.h"
#include "IoT/BtLE/GATTClient.h"
#include "Poco/RefCountedObject.h"
#include "Poco/AutoPtr.h"
#include "Poco/Mutex.h"
#include "Poco/Logger.h"
#include <map>


namespace IoT {
namespace BtLE {
namespace BlueZ {


class BlueZGATTClient: public GATTClient, protected HelperClient
	/// An implementation of the GATTClient interface using the BlueZ Linux
	/// Bt stack via an external helper executable.
{
public:
	explicit BlueZGATTClient(const std::string helperPath);
		/// Creates the BlueZGATTClient using the given helper path.

	~BlueZGATTClient();
		/// Destroys the BlueZGATTClient.

	// GATTClient
	void connect(const std::string& address, ConnectMode mode);
	void disconnect();
	State state() const;
	std::string address() const;
	std::vector<Service> services();
	std::vector<Service> includedServices(const std::string& serviceUUID);
	std::vector<Characteristic> characteristics(const std::string& serviceUUID);
	std::vector<Descriptor> descriptors(const std::string& serviceUUID);
	std::string read(Poco::UInt16 handle);
	void write(Poco::UInt16 handle, const std::string& value, bool withResponse);
	void setSecurityLevel(SecurityLevel level);
	SecurityLevel getSecurityLevel() const;
	void setMTU(Poco::UInt8 mtu);
	Poco::UInt8 getMTU() const;
	void setTimeout(long timeout);
	long getTimeout() const;

protected:
	void changeState(State newState);
	void processResponse(const std::string& response);

	struct ServiceDesc: public Poco::RefCountedObject
	{
		using Ptr = Poco::AutoPtr<ServiceDesc>;

		Service service;
		std::vector<Characteristic> characteristics;
		std::vector<Descriptor> descriptors;
	};
	using ServiceMap = std::map<std::string, ServiceDesc::Ptr>;

private:
	std::string _address;
	State _state;
	ConnectMode _connectMode;
	SecurityLevel _securityLevel;
	Poco::UInt8 _mtu;
	long _timeout;
	ServiceMap _services;
	mutable Poco::FastMutex _mutex;
	mutable Poco::FastMutex _stateMutex;
	Poco::Logger& _logger;
};


} } } // namespace IoT::BtLE::BlueZ


#endif // IoT_BtLE_BlueZGATTClient_INCLUDED
