//
// PeripheralBrowserEventDispatcher.h
//
// Library: IoT/BtLE
// Package: Generated
// Module:  PeripheralBrowserEventDispatcher
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2017, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_BtLE_PeripheralBrowserEventDispatcher_INCLUDED
#define IoT_BtLE_PeripheralBrowserEventDispatcher_INCLUDED


#include "IoT/BtLE/PeripheralBrowserRemoteObject.h"
#include "Poco/RemotingNG/EventDispatcher.h"


namespace IoT {
namespace BtLE {


class PeripheralBrowserEventDispatcher: public Poco::RemotingNG::EventDispatcher
	/// This class provides browsing for available Bluetooth LE devices.
{
public:
	PeripheralBrowserEventDispatcher(PeripheralBrowserRemoteObject* pRemoteObject, const std::string& protocol);
		/// Creates a PeripheralBrowserEventDispatcher.

	virtual ~PeripheralBrowserEventDispatcher();
		/// Destroys the PeripheralBrowserEventDispatcher.

	void event__browseComplete(const void* pSender);

	void event__peripheralFound(const void* pSender, const IoT::BtLE::PeripheralInfo& data);

	virtual const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId() const;

private:
	void event__browseCompleteImpl(const std::string& subscriberURI);

	void event__peripheralFoundImpl(const std::string& subscriberURI, const IoT::BtLE::PeripheralInfo& data);

	static const std::string DEFAULT_NS;
	PeripheralBrowserRemoteObject* _pRemoteObject;
};


inline const Poco::RemotingNG::Identifiable::TypeId& PeripheralBrowserEventDispatcher::remoting__typeId() const
{
	return IPeripheralBrowser::remoting__typeId();
}


} // namespace BtLE
} // namespace IoT


#endif // IoT_BtLE_PeripheralBrowserEventDispatcher_INCLUDED

