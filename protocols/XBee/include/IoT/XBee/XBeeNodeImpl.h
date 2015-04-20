//
// XBeeNodeImpl.h
//
// $Id$
//
// Library: IoT/XBee
// Package: XBeeNode
// Module:  XBeeNodeImpl
//
// Definition of the XBeeNodeImpl class.
//
// Copyright (c) 2013-2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_XBee_XBeeNodeImpl_INCLUDED
#define IoT_XBee_XBeeNodeImpl_INCLUDED


#include "IoT/XBee/XBeeNode.h"
#include "IoT/XBee/XBeePort.h"
#include "Poco/Thread.h"
#include "Poco/Runnable.h"
#include "Poco/Mutex.h"
#include "Poco/SharedPtr.h"
#include "Poco/Logger.h"


namespace IoT {
namespace XBee {


class XBeeFrame;


class IoTXBee_API XBeeNodeImpl: public XBeeNode, public Poco::Runnable
	/// Implementation of the XBeeNode interface.
{
public:
	enum Options
	{
		XBEE_OPTION_ESCAPE_FRAMES = 0x01
	};
	
	XBeeNodeImpl(Poco::SharedPtr<XBeePort> pXBeePort, int options = 0);
		/// Creates a XBeeNodeImpl using the given XBeePort instance
		/// and options.
		
	~XBeeNodeImpl();
		/// Destroys the ZBPort.

	// XBeeNode
	void sendFrame(const APIFrame& frame);
	void sendCommand(const ATCommand& command);
	void queueCommand(const ATCommand& command);
	void sendRemoteCommand(const RemoteATCommand& command);
	
protected:
	void run();
	void start();
	void stop();
	void handleFrame(const XBeeFrame& frame);
	void handleCommandResponse(const XBeeFrame& frame);
	void handleRemoteCommandResponse(const XBeeFrame& frame);
	void handleSampleRxIndicator(const XBeeFrame& frame);
	void sendFrame(XBeeFrame& frame);

private:
	Poco::SharedPtr<XBeePort> _pXBeePort;
	int _options;
	Poco::Thread _thread;	
	bool _stopped;
	mutable Poco::FastMutex _mutex;
	Poco::Logger& _logger;
};


} } // namespace IoT::XBee


#endif // IoT_XBee_XBeeNodeImpl_INCLUDED
