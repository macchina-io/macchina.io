//
// BlueZGATTClient.h
//
// $Id$
//
// Library: IoT/BtLE
// Package: BtLE
// Module:  BlueZGATTClient
//
// Definition of the GATTClient class.
//
// Copyright (c) 2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_BtLE_BlueZGATTClient_INCLUDED
#define IoT_BtLE_BlueZGATTClient_INCLUDED


#include "IoT/BtLE/GATTClient.h"
#include "Poco/RefCountedObject.h"
#include "Poco/AutoPtr.h"
#include "Poco/Runnable.h"
#include "Poco/Thread.h"
#include "Poco/Mutex.h"
#include "Poco/Process.h"
#include "Poco/PipeStream.h"
#include "Poco/Notification.h"
#include "Poco/NotificationQueue.h"
#include "Poco/Logger.h"
#include <map>


namespace IoT {
namespace BtLE {


class IoTBtLE_API BlueZGATTClient: public GATTClient, public Poco::Runnable
	/// An implementation of the GATTClient interface using the BlueZ Linux
	/// Bluetooth stack via an external helper executable.
	///
	/// Using an external helper executable is necessary due to GPL licensing
	/// of relevant parts of the BlueZ library used in the client part.
	/// A future implementation of this class may use the D-Bus API of BlueZ.
{
public:
	BlueZGATTClient(const std::string helperPath);
		/// Creates the BlueZGATTClient using the given helper path.
	
	~BlueZGATTClient();
		/// Destroys the BlueZGATTClient.
	
	static std::string decodeValue(const std::string& value);
	static Poco::UInt16 decodeWord(const std::string& value);
	
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
	typedef std::pair<std::string, std::string> KeyValuePair;
	class ParsedResponse: public Poco::Notification
	{
	public:
		typedef Poco::AutoPtr<ParsedResponse> Ptr;
		typedef std::vector<KeyValuePair> KeyValueVec;
		typedef KeyValueVec::const_iterator const_iterator;

		std::string type() const
		{
			return decodeValue(get("rsp"));
		}
		
		const std::string& get(const std::string& key) const
		{
			const_iterator it = find(key);
			if (it != end())
				return it->second;
			else
				throw Poco::NotFoundException(key);
		}
		
		void add(const KeyValuePair& param)
		{
			_params.push_back(param);
		}
		
		const_iterator begin() const
		{
			return _params.begin();
		}
		
		const_iterator end() const
		{
			return _params.end();
		}
		
		const_iterator find(const std::string& key) const
		{
			for (std::vector<KeyValuePair>::const_iterator it = _params.begin(); it != _params.end(); ++it)
			{
				if (it->first == key)
					return it;
			}
			return _params.end();
		}
		
	private:
		std::vector<KeyValuePair> _params;
	};

	void changeState(State newState);
	void startHelper();
	void stopHelper();
	bool helperRunning();
	void run();
	void sendCommand(const std::string& command);
	void processResponse(const std::string& response);
	void parseResponse(const std::string& response, ParsedResponse& parsedResponse);
	ParsedResponse::Ptr waitResponse(long timeout);
	ParsedResponse::Ptr expectResponse(const std::string& type, long timeout);

	struct ServiceDesc: public Poco::RefCountedObject
	{
		typedef Poco::AutoPtr<ServiceDesc> Ptr;

		Service service;
		std::vector<Characteristic> characteristics;
		std::vector<Descriptor> descriptors;
	};
	typedef std::map<std::string, ServiceDesc::Ptr> ServiceMap;
	
	struct HelperInfo: public Poco::RefCountedObject
	{
		typedef Poco::AutoPtr<HelperInfo> Ptr;
	
		HelperInfo(const Poco::ProcessHandle& ph, const Poco::Pipe& inputPipe, const Poco::Pipe& outputPipe):
			processHandle(ph),
			inputStream(outputPipe),
			outputStream(inputPipe)
		{
		}
		
		Poco::ProcessHandle    processHandle;
		Poco::PipeInputStream  inputStream;
		Poco::PipeOutputStream outputStream;
	};
	
	enum
	{
		DEFAULT_TIMEOUT = 30000,
		DISCONNECT_TIMEOUT = 2000
	};
	
private:
	std::string _helperPath;
	std::string _address;
	State _state;
	ConnectMode _connectMode;
	SecurityLevel _securityLevel;
	Poco::UInt8 _mtu;
	long _timeout;
	ServiceMap _services;
	Poco::Thread _helperThread;
	HelperInfo::Ptr _pHelperInfo;
	Poco::NotificationQueue _responseQueue;
	Poco::Logger& _logger;
	mutable Poco::FastMutex _mutex;
	mutable Poco::FastMutex _responseMutex;
	mutable Poco::FastMutex _stateMutex;
};


} } // namespace IoT::BtLE


#endif // IoT_BtLE_BlueZGATTClient_INCLUDED
