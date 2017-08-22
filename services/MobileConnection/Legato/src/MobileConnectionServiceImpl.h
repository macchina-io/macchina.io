//
// MobileConnectionServiceImpl.h
//
// $Id$
//
// Definition of the MobileConnectionServiceImpl class.
//
// Copyright (c) 2017, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_MobileConnection_Legato_MobileConnectionServiceImpl_INCLUDED
#define IoT_MobileConnection_Legato_MobileConnectionServiceImpl_INCLUDED


#include "IoT/MobileConnection/MobileConnectionService.h"
#include "Poco/ExpireCache.h"
#include "Poco/Mutex.h"
#include <vector>


namespace IoT {
namespace MobileConnection {
namespace Legato {


class MobileConnectionServiceImpl: public MobileConnectionService
	/// The MobileConnectionService implementation for Legato.
	///
	/// Note: this implementation is quite trivial and based on
	/// the Legato "cm" command-line utility. A proper implementation
	/// should use the respective Legato C APIs.
{
public:
	typedef Poco::SharedPtr<MobileConnectionServiceImpl> Ptr;

	MobileConnectionServiceImpl(const std::string& cmPath = DEFAULT_CM_PATH);
		/// Creates the MobileConnectionService.

	~MobileConnectionServiceImpl();
		/// Destroys the MobileConnectionService.

	// MobileConnectionService
	std::string imei() const;
	std::string deviceName() const;
	SIMState simState() const;
	void unlockSIM(const std::string& pin);
	void lockSIM(const std::string& pin);
	void enterPIN(const std::string& pin);
	std::string imsi() const;
	std::string phoneNumber() const;
	std::string iccid() const;
	void setAPN(const std::string& apn);
	std::string getAPN() const;
	void setPDPType(PDPType type);
	PDPType getPDPType() const;
	void authenticate(AuthMethod method, const std::string& username, const std::string& password);
	void enableRadio(bool enable);
	bool isRadioEnabled() const;
	std::string networkOperator() const;
	RegistrationStatus registrationStatus() const;
	RadioAccessTechnology radioAccessTechnology() const;
	int signalStrength() const;
	bool isDataConnected();
	void connectData();
	void disconnectData();

	static const std::string DEFAULT_CM_PATH;

protected:
	std::string cmCached(const std::string& module, const std::string& command) const;
	std::string cm(const std::string& module, const std::string& command) const;
	std::string cm(const std::string& module, const std::string& command, const std::string& arg) const;
	std::string cm(const std::vector<std::string>& args) const;
	static std::string extractValue(const std::string& output, const std::string& key);

private:
	typedef Poco::ExpireCache<std::string, std::string> CMCache;
	std::string _cmPath;
	mutable CMCache _cmCache;
	mutable Poco::FastMutex _mutex;
};


} } } // namespace IoT::MobileConnection::Legato


#endif // IoT_MobileConnection_Legato_MobileConnectionServiceImpl_INCLUDED
