//
// CANEndpointImpl.h
//
// Definition of the CANEndpointImpl class for SocketCAN.
//
// Copyright (c) 2018, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef IoT_SocketCAN_CANEndpointImpl_INCLUDED
#define IoT_SocketCAN_CANEndpointImpl_INCLUDED


#include "IoT/CAN/CANEndpoint.h"
#include "Poco/Thread.h"
#include "Poco/Runnable.h"
#include "Poco/Mutex.h"
#include "Poco/Logger.h"
#include "CANSocket.h"



namespace IoT {
namespace CAN {
namespace SocketCAN {


class IoTCAN_API CANEndpointImpl: public IoT::CAN::CANEndpoint, public Poco::Runnable
	/// CANEndpoint implementation for Linux SocketCAN interface.
{
public:
	using Ptr = Poco::SharedPtr<CANEndpointImpl>;

	CANEndpointImpl(const std::string& interfc);
		/// Creates the CANEndpointImpl for the given interface.

	~CANEndpointImpl();
		/// Destroys the CANEndpointImpl.

	void run();
		/// Receive thread.

	// CANEndpoint
	std::string device() const;
	void setFilter(const std::vector<Filter>& filter);
	std::vector<Filter> getFilter() const;
	bool addFilter(const Filter& filter);
	bool removeFilter(const Filter& filter);
	void setFilterMode(FilterMode mode);
	FilterMode getFilterMode() const;
	void sendCANFrame(const CANFrame& frame);
	void sendCANFDFrame(const CANFDFrame& frame);
	void sendFrame(const CANFDFrame& frame, FrameType type);
	void enableEvents(bool enable);
	bool eventsEnabled() const;
	void enableFD(bool enable);
	bool fdEnabled() const;
	bool fdSupported() const;

protected:
	void applyFilter();

private:
	enum
	{
		CAN_POLL_TIMEOUT = 200000
	};

	std::string _interfc;
	CANSocket _socket;
	Poco::Thread _thread;
	std::vector<Filter> _filter;
	FilterMode _filterMode;
	int _enableEvents;
	int _enableFD;
	mutable Poco::FastMutex _mutex;
	Poco::Logger& _logger;
};


} } } // namespace IoT::CAN::SocketCAN


#endif // IoT_SocketCAN_CANEndpointImpl_INCLUDED
