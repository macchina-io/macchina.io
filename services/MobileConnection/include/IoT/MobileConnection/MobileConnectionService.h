//
// MobileConnectionService.h
//
// $Id$
//
// Library: IoT/MobileConnection
// Package: MobileConnection
// Module:  MobileConnectionService
//
// Definition of the MobileConnectionService interface.
//
// Copyright (c) 2017, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_MobileConnection_MobileConnectionService_INCLUDED
#define IoT_MobileConnection_MobileConnectionService_INCLUDED


#include "IoT/MobileConnection/MobileConnection.h"
#include "Poco/BasicEvent.h"
#include "Poco/SharedPtr.h"


namespace IoT {
namespace MobileConnection {


enum SIMState
	/// State of SIM card.
{
	MC_SIM_INSERTED,   /// SIM is present, but no PIN has been provided yet.
	MC_SIM_ABSENT,     /// SIM is not present.
	MC_SIM_READY,      /// SIM is ready.
	MC_SIM_BLOCKED,    /// SIM is blocked.
	MC_SIM_BUSY,       /// SIM is busy.
	MC_SIM_UNKNOWN     /// SIM state is unknown due to an error.
};


enum RadioAccessTechnology
	/// Radio technology used to connect to mobile network.
{
	MC_RAT_CDMA,       /// CDMA
	MC_RAT_GSM,        /// GSM
	MC_RAT_UMTS,       /// UMTS
	MC_RAT_LTE,        /// LTE
	MC_RAT_TDSCDMA,    /// CDMA 3G
	MC_RAT_UNKNOWN     /// Technology unknown due to error.
};


enum RegistrationStatus
	/// Network registration status.
{
	MC_REG_NONE,       /// Not registered.
	MC_REG_HOME,       /// Registered with home network.
	MC_REG_SEARCHING,  /// Searching for network.
	MC_REG_DENIED,     /// Registration was denied.
	MC_REG_ROAMING,    /// Registered with roaming network.
	MC_REG_UNKNOWN     /// Registration state unknown due to an error.
};


enum AuthMethod
	/// Authentication method for data connection.
{
	MC_AUTH_NONE,      /// No authentication
	MC_AUTH_PAP,       /// PAP authentication
	MC_AUTH_CHAP       /// CHAP authentication
};


enum PDPType
	/// Packet Data Protocol (PDP) type.
{
	MC_PDP_IPV4,       /// IPv4 protocol
	MC_PDP_IPV6,       /// IPv6 protocol
	MC_PDP_IPV4V6,     /// Both IPv4 and IPv6 protocols
	MC_PDP_UNKNOWN     /// PDP type unknown due to an error.
};


//@ remote
class IoTMobileConnection_API MobileConnectionService
	/// The MobileConnectionService interface is used to configure
	/// and establish a mobile data connection.
{
public:
	typedef Poco::SharedPtr<MobileConnectionService> Ptr;

	Poco::BasicEvent<void> dataConnected;
		/// The data connection has become available.

	Poco::BasicEvent<void> dataDisconnected;
		/// The data connection no longer is available.

	MobileConnectionService();
		/// Creates the MobileConnectionService.

	virtual ~MobileConnectionService();
		/// Destroys the MobileConnectionService.

	virtual std::string deviceName() const = 0;
		/// Returns the modem device name.

	virtual std::string imei() const = 0;
		/// Returns the IMEI (International Mobile Equipment Identity).

	virtual SIMState simState() const = 0;
		/// Returns the current state of the SIM.

	virtual void unlockSIM(const std::string& pin) = 0;
		/// Unlocks the SIM, using the given PIN.

	virtual void lockSIM(const std::string& pin) = 0;
		/// Locks the SIM, using the given PIN.

	virtual void enterPIN(const std::string& pin) = 0;
		/// Provides the given PIN to the SIM.

	virtual std::string imsi() const = 0;
		/// Returns the SIM's IMSI (International Mobile Subscriber Identity).

	virtual std::string phoneNumber() const = 0;
		/// Returns the phone number associated with the SIM.

	virtual std::string iccid() const = 0;
		/// Returns the SIMs ICCID (Integrated Circuit Card Identifier).

	virtual void setAPN(const std::string& apn) = 0;
		/// Sets the Access Point Name (APN) for the mobile data connection.

	virtual std::string getAPN() const = 0;
		/// Returns the configured Access Point Name (APN) for the mobile data connection.

	virtual void setPDPType(PDPType type) = 0;
		/// Sets the PDP Type for the mobile data connection.

	virtual PDPType getPDPType() const = 0;
		/// Returns the PDP Type for the mobile data connection.

	virtual void authenticate(AuthMethod method, const std::string& username, const std::string& password) = 0;
		/// Provide the credentials for the mobile data connection.

	virtual void enableRadio(bool enable) = 0;
		/// Enables or disables the radio.

	virtual bool isRadioEnabled() const = 0;
		/// Returns true if the radio is enabled, otherwise false.

	virtual std::string networkOperator() const = 0;
		/// Returns the name of the network operator, if available, or
		/// an empty string otherwise.

	virtual RegistrationStatus registrationStatus() const = 0;
		/// Returns the network registration status.

	virtual RadioAccessTechnology radioAccessTechnology() const = 0;
		/// Returns the radio access technology (RAT) used to connect
		/// to the mobile network.

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

	virtual bool isDataConnected() = 0;
		/// Returns true if the data connection is available.

	virtual void connectData() = 0;
		/// Establishes the data connection.

	virtual void disconnectData() = 0;
		/// Closes the data connection.
};


} } // namespace IoT::MobileConnection


#endif // IoT_MobileConnection_MobileConnectionService_INCLUDED
