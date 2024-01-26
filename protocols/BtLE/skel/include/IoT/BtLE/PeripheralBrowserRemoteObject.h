//
// PeripheralBrowserRemoteObject.h
//
// Library: IoT/BtLE
// Package: Generated
// Module:  PeripheralBrowserRemoteObject
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2017-2023, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef IoT_BtLE_PeripheralBrowserRemoteObject_INCLUDED
#define IoT_BtLE_PeripheralBrowserRemoteObject_INCLUDED


#include "IoT/BtLE/IPeripheralBrowser.h"
#include "Poco/RemotingNG/Identifiable.h"
#include "Poco/RemotingNG/RemoteObject.h"
#include "Poco/SharedPtr.h"


namespace IoT {
namespace BtLE {


class PeripheralBrowserRemoteObject: public IoT::BtLE::IPeripheralBrowser, public Poco::RemotingNG::RemoteObject
	/// This class provides browsing (scanning) for available Bt LE devices.
{
public:
	using Ptr = Poco::AutoPtr<PeripheralBrowserRemoteObject>;

	PeripheralBrowserRemoteObject(const Poco::RemotingNG::Identifiable::ObjectId& oid, Poco::SharedPtr<IoT::BtLE::PeripheralBrowser> pServiceObject);
		/// Creates a PeripheralBrowserRemoteObject.

	virtual ~PeripheralBrowserRemoteObject();
		/// Destroys the PeripheralBrowserRemoteObject.

	virtual void browse(bool activeScan = bool(false));
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

	virtual bool browseInProgress();
		/// Returns true if a browse (scan) is currently in progress, otherwise false.

	virtual void cancelBrowse();
		/// Cancels an ongoing browse operation.

	virtual std::string remoting__enableEvents(Poco::RemotingNG::Listener::Ptr pListener, bool enable = bool(true));

	virtual void remoting__enableRemoteEvents(const std::string& protocol);

	virtual bool remoting__hasEvents() const;

	virtual const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId() const;

protected:
	void event__browseComplete();

	void event__browseError(const std::string& data);

	void event__browseStarted();

	void event__peripheralFound(const IoT::BtLE::PeripheralInfo& data);

private:
	Poco::SharedPtr<IoT::BtLE::PeripheralBrowser> _pServiceObject;
};


inline void PeripheralBrowserRemoteObject::browse(bool activeScan)
{
	_pServiceObject->browse(activeScan);
}


inline bool PeripheralBrowserRemoteObject::browseInProgress()
{
	return _pServiceObject->browseInProgress();
}


inline void PeripheralBrowserRemoteObject::cancelBrowse()
{
	_pServiceObject->cancelBrowse();
}


inline const Poco::RemotingNG::Identifiable::TypeId& PeripheralBrowserRemoteObject::remoting__typeId() const
{
	return IPeripheralBrowser::remoting__typeId();
}


} // namespace BtLE
} // namespace IoT


#endif // IoT_BtLE_PeripheralBrowserRemoteObject_INCLUDED

