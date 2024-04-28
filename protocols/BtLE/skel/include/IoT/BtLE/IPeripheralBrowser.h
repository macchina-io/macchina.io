//
// IPeripheralBrowser.h
//
// Library: IoT/BtLE
// Package: Generated
// Module:  IPeripheralBrowser
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2017-2023, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef IoT_BtLE_IPeripheralBrowser_INCLUDED
#define IoT_BtLE_IPeripheralBrowser_INCLUDED


#include "IoT/BtLE/PeripheralBrowser.h"
#include "Poco/AutoPtr.h"
#include "Poco/OSP/Service.h"
#include "Poco/RemotingNG/Identifiable.h"
#include "Poco/RemotingNG/Listener.h"


namespace IoT {
namespace BtLE {


class IPeripheralBrowser: public Poco::OSP::Service
	/// This class provides browsing (scanning) for available Bt LE devices.
{
public:
	using Ptr = Poco::AutoPtr<IPeripheralBrowser>;

	IPeripheralBrowser();
		/// Creates a IPeripheralBrowser.

	virtual ~IPeripheralBrowser();
		/// Destroys the IPeripheralBrowser.

	virtual void browse(bool activeScan = bool(false)) = 0;
		/// Scan for peripherals.
		///
		/// If activeScan is true, an active scan will be performed, 
		/// otherwise a passive scan. Full advertising data will only
		/// be provided in an active scan. Advertising data for a passive
		/// scan is limited to at most 31 bytes. For extended advertising data
		/// provided by an active scan, the maximum size is 1650 bytes.
		///
		/// Any peripherals found will be reported through the peripheralFound
		/// event. Scanning for peripherals will be done asynchronously, therefore
		/// this method returns immediately.
		///
		/// An active scan will stop automatically after some time, firing the
		/// browseComplete event. A passive scan will go on until canceled by
		/// calling cancelBrowse().
		///
		/// If a browse is already in progress, throws a Poco::IllegalStateException.

	virtual bool browseInProgress() = 0;
		/// Returns true if a browse (scan) is currently in progress, otherwise false.

	virtual void cancelBrowse() = 0;
		/// Cancels an ongoing browse operation.

	bool isA(const std::type_info& otherType) const;
		/// Returns true if the class is a subclass of the class given by otherType.

	virtual std::string remoting__enableEvents(Poco::RemotingNG::Listener::Ptr pListener, bool enable = bool(true)) = 0;
		/// Enable or disable delivery of remote events.
		///
		/// The given Listener instance must implement the Poco::RemotingNG::EventListener
		/// interface, otherwise this method will fail with a RemotingException.
		///
		/// This method is only used with Proxy objects; calling this method on a
		/// RemoteObject will do nothing.

	static const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId();
		/// Returns the TypeId of the class.

	const std::type_info& type() const;
		/// Returns the type information for the object's class.

	Poco::BasicEvent<void> browseComplete;
	Poco::BasicEvent<const std::string> browseError;
	Poco::BasicEvent<void> browseStarted;
	Poco::BasicEvent<const IoT::BtLE::PeripheralInfo> peripheralFound;
};


} // namespace BtLE
} // namespace IoT


#endif // IoT_BtLE_IPeripheralBrowser_INCLUDED

