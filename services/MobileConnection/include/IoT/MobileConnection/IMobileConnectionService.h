//
// IMobileConnectionService.h
//
// Library: IoT/MobileConnection
// Package: Generated
// Module:  IMobileConnectionService
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2017, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_MobileConnection_IMobileConnectionService_INCLUDED
#define IoT_MobileConnection_IMobileConnectionService_INCLUDED


#include "IoT/MobileConnection/MobileConnectionService.h"
#include "Poco/AutoPtr.h"
#include "Poco/OSP/Service.h"
#include "Poco/RemotingNG/Identifiable.h"
#include "Poco/RemotingNG/Listener.h"


namespace IoT {
namespace MobileConnection {


class IMobileConnectionService: public Poco::OSP::Service
	/// The MobileConnectionService interface is used to configure
	/// and establish a mobile data connection.
{
public:
	typedef Poco::AutoPtr<IMobileConnectionService> Ptr;

	IMobileConnectionService();
		/// Creates a IMobileConnectionService.

	virtual ~IMobileConnectionService();
		/// Destroys the IMobileConnectionService.

	virtual void authenticate(IoT::MobileConnection::AuthMethod method, const std::string& username, const std::string& password) = 0;
		/// Provide the credentials for the mobile data connection.

	virtual void connectData() = 0;
		/// Establishes the data connection.

	virtual void disconnectData() = 0;
		/// Closes the data connection.

	virtual void enableRadio(bool enable) = 0;
		/// Enables or disables the radio.

	virtual void enterPIN(const std::string& pin) = 0;
		/// Provides the given PIN to the SIM.

	virtual std::string getAPN() const = 0;
		/// Returns the configured Access Point Name (APN) for the mobile data connection.

	virtual std::string iccid() const = 0;
		/// Returns the SIMs ICCID (Integrated Circuit Card Identifier).

	virtual std::string imsi() const = 0;
		/// Returns the SIM's IMSI (International Mobile Subscriber Identity).

	bool isA(const std::type_info& otherType) const;
		/// Returns true if the class is a subclass of the class given by otherType.

	virtual bool isDataConnected() = 0;
		/// Returns true if the data connection is available.

	virtual bool isRadioEnabled() const = 0;
		/// Returns true if the radio is enabled, otherwise false.

	virtual void lockSIM(const std::string& pin) = 0;
		/// Locks the SIM, using the given PIN.

	virtual std::string networkOperator() const = 0;
		/// Returns the name of the network operator, if available, or
		/// an empty string otherwise.

	virtual std::string phoneNumber() const = 0;
		/// Returns the phone number associated with the SIM.

	virtual IoT::MobileConnection::RadioAccessTechnology radioAccessTechnology() const = 0;
		/// Returns the radio access technology (RAT) used to connect
		/// to the mobile network.

	virtual IoT::MobileConnection::RegistrationStatus registrationStatus() const = 0;
		/// Returns the network registration status.

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

	virtual void setAPN(const std::string& apn) = 0;
		/// Sets the Access Point Name (APN) for the mobile data connection.

	virtual int signalStrength() const = 0;
		/// Returns the signal strength in a range from 0 to 5
		/// (suitable for displaying corresponding "signal strength bars").
		///
		///   - 0: No signal.
		///   - 1: Very weak signal.
		///   - 2: Weak signal strength.
		///   - 3: Good signal strength.
		///   - 4: Strong signal strength.
		///   - 5: Very strong signal strength.
		///
		/// Returns -1 if the signal strength cannot be obtained.

	virtual IoT::MobileConnection::SIMState simState() const = 0;
		/// Returns the current state of the SIM.

	const std::type_info& type() const;
		/// Returns the type information for the object's class.

	virtual void unlockSIM(const std::string& pin) = 0;
		/// Unlocks the SIM, using the given PIN.

	Poco::BasicEvent < void > dataConnected;
	Poco::BasicEvent < void > dataDisconnected;
};


} // namespace MobileConnection
} // namespace IoT


#endif // IoT_MobileConnection_IMobileConnectionService_INCLUDED

