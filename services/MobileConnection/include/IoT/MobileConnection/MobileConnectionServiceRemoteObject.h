//
// MobileConnectionServiceRemoteObject.h
//
// Library: IoT/MobileConnection
// Package: Generated
// Module:  MobileConnectionServiceRemoteObject
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2017, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_MobileConnection_MobileConnectionServiceRemoteObject_INCLUDED
#define IoT_MobileConnection_MobileConnectionServiceRemoteObject_INCLUDED


#include "IoT/MobileConnection/IMobileConnectionService.h"
#include "Poco/RemotingNG/Identifiable.h"
#include "Poco/RemotingNG/RemoteObject.h"
#include "Poco/SharedPtr.h"


namespace IoT {
namespace MobileConnection {


class MobileConnectionServiceRemoteObject: public IoT::MobileConnection::IMobileConnectionService, public Poco::RemotingNG::RemoteObject
	/// The MobileConnectionService interface is used to configure
	/// and establish a mobile data connection.
{
public:
	using Ptr = Poco::AutoPtr<MobileConnectionServiceRemoteObject>;

	MobileConnectionServiceRemoteObject(const Poco::RemotingNG::Identifiable::ObjectId& oid, Poco::SharedPtr<IoT::MobileConnection::MobileConnectionService> pServiceObject);
		/// Creates a MobileConnectionServiceRemoteObject.

	virtual ~MobileConnectionServiceRemoteObject();
		/// Destroys the MobileConnectionServiceRemoteObject.

	virtual void authenticate(IoT::MobileConnection::AuthMethod method, const std::string& username, const std::string& password);
		/// Provide the credentials for the mobile data connection.

	virtual void connectData();
		/// Establishes the data connection.

	virtual std::string deviceName() const;
		/// Returns the modem device name.

	virtual void disconnectData();
		/// Closes the data connection.

	virtual void enableRadio(bool enable);
		/// Enables or disables the radio.

	virtual void enterPIN(const std::string& pin);
		/// Provides the given PIN to the SIM.

	virtual std::string getAPN() const;
		/// Returns the configured Access Point Name (APN) for the mobile data connection.

	IoT::MobileConnection::PDPType getPDPType() const;
		/// Returns the PDP Type for the mobile data connection.

	virtual std::string iccid() const;
		/// Returns the SIMs ICCID (Integrated Circuit Card Identifier).

	virtual std::string imei() const;
		/// Returns the IMEI (International Mobile Equipment Identity).

	virtual std::string imsi() const;
		/// Returns the SIM's IMSI (International Mobile Subscriber Identity).

	virtual bool isDataConnected();
		/// Returns true if the data connection is available.

	virtual bool isRadioEnabled() const;
		/// Returns true if the radio is enabled, otherwise false.

	virtual void lockSIM(const std::string& pin);
		/// Locks the SIM, using the given PIN.

	virtual std::string networkOperator() const;
		/// Returns the name of the network operator, if available, or
		/// an empty string otherwise.

	virtual std::string phoneNumber() const;
		/// Returns the phone number associated with the SIM.

	IoT::MobileConnection::RadioAccessTechnology radioAccessTechnology() const;
		/// Returns the radio access technology (RAT) used to connect
		/// to the mobile network.

	IoT::MobileConnection::RegistrationStatus registrationStatus() const;
		/// Returns the network registration status.

	virtual std::string remoting__enableEvents(Poco::RemotingNG::Listener::Ptr pListener, bool enable = bool(true));

	virtual void remoting__enableRemoteEvents(const std::string& protocol);

	virtual bool remoting__hasEvents() const;

	virtual const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId() const;

	virtual void setAPN(const std::string& apn);
		/// Sets the Access Point Name (APN) for the mobile data connection.

	virtual void setPDPType(IoT::MobileConnection::PDPType type);
		/// Sets the PDP Type for the mobile data connection.

	virtual int signalStrength() const;
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

	IoT::MobileConnection::SIMState simState() const;
		/// Returns the current state of the SIM.

	virtual void unlockSIM(const std::string& pin);
		/// Unlocks the SIM, using the given PIN.

protected:
	void event__dataConnected();

	void event__dataDisconnected();

private:
	Poco::SharedPtr<IoT::MobileConnection::MobileConnectionService> _pServiceObject;
};


inline void MobileConnectionServiceRemoteObject::authenticate(IoT::MobileConnection::AuthMethod method, const std::string& username, const std::string& password)
{
	_pServiceObject->authenticate(method, username, password);
}


inline void MobileConnectionServiceRemoteObject::connectData()
{
	_pServiceObject->connectData();
}


inline std::string MobileConnectionServiceRemoteObject::deviceName() const
{
	return _pServiceObject->deviceName();
}


inline void MobileConnectionServiceRemoteObject::disconnectData()
{
	_pServiceObject->disconnectData();
}


inline void MobileConnectionServiceRemoteObject::enableRadio(bool enable)
{
	_pServiceObject->enableRadio(enable);
}


inline void MobileConnectionServiceRemoteObject::enterPIN(const std::string& pin)
{
	_pServiceObject->enterPIN(pin);
}


inline std::string MobileConnectionServiceRemoteObject::getAPN() const
{
	return _pServiceObject->getAPN();
}


inline IoT::MobileConnection::PDPType MobileConnectionServiceRemoteObject::getPDPType() const
{
	return _pServiceObject->getPDPType();
}


inline std::string MobileConnectionServiceRemoteObject::iccid() const
{
	return _pServiceObject->iccid();
}


inline std::string MobileConnectionServiceRemoteObject::imei() const
{
	return _pServiceObject->imei();
}


inline std::string MobileConnectionServiceRemoteObject::imsi() const
{
	return _pServiceObject->imsi();
}


inline bool MobileConnectionServiceRemoteObject::isDataConnected()
{
	return _pServiceObject->isDataConnected();
}


inline bool MobileConnectionServiceRemoteObject::isRadioEnabled() const
{
	return _pServiceObject->isRadioEnabled();
}


inline void MobileConnectionServiceRemoteObject::lockSIM(const std::string& pin)
{
	_pServiceObject->lockSIM(pin);
}


inline std::string MobileConnectionServiceRemoteObject::networkOperator() const
{
	return _pServiceObject->networkOperator();
}


inline std::string MobileConnectionServiceRemoteObject::phoneNumber() const
{
	return _pServiceObject->phoneNumber();
}


inline IoT::MobileConnection::RadioAccessTechnology MobileConnectionServiceRemoteObject::radioAccessTechnology() const
{
	return _pServiceObject->radioAccessTechnology();
}


inline IoT::MobileConnection::RegistrationStatus MobileConnectionServiceRemoteObject::registrationStatus() const
{
	return _pServiceObject->registrationStatus();
}


inline const Poco::RemotingNG::Identifiable::TypeId& MobileConnectionServiceRemoteObject::remoting__typeId() const
{
	return IMobileConnectionService::remoting__typeId();
}


inline void MobileConnectionServiceRemoteObject::setAPN(const std::string& apn)
{
	_pServiceObject->setAPN(apn);
}


inline void MobileConnectionServiceRemoteObject::setPDPType(IoT::MobileConnection::PDPType type)
{
	_pServiceObject->setPDPType(type);
}


inline int MobileConnectionServiceRemoteObject::signalStrength() const
{
	return _pServiceObject->signalStrength();
}


inline IoT::MobileConnection::SIMState MobileConnectionServiceRemoteObject::simState() const
{
	return _pServiceObject->simState();
}


inline void MobileConnectionServiceRemoteObject::unlockSIM(const std::string& pin)
{
	_pServiceObject->unlockSIM(pin);
}


} // namespace MobileConnection
} // namespace IoT


#endif // IoT_MobileConnection_MobileConnectionServiceRemoteObject_INCLUDED

