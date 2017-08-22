//
// BrickletImpl.h
//
// $Id: //iot/Main/Tf/src/BrickletImpl.h#2 $
//
// Copyright (c) 2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_Tf_BrickletImpl_INCLUDED
#define IoT_Tf_BrickletImpl_INCLUDED


#include "IoT/Tf/Tf.h"
#include "IoT/Devices/DeviceImpl.h"
#include "Poco/Format.h"


namespace IoT {
namespace Tf {


template <class Super, class Sub>
class BrickletImpl: public IoT::Devices::DeviceImpl<Super, Sub>
{
public:
	typedef BrickletImpl BrickletType;
	typedef Super        SuperType;

	BrickletImpl(const std::string& symbolicName, const std::string& name, const std::string& type, const std::string physicalQuantity = "", const std::string& physicalUnit = ""):
		_symbolicName(symbolicName),
		_name(name),
		_physicalQuantity(physicalQuantity),
		_physicalUnit(physicalUnit)
	{
		this->addProperty("uid", &BrickletImpl::getUID);
		this->addProperty("masterUID", &BrickletImpl::getMasterUID);
		this->addProperty("position", &BrickletImpl::getPosition);
		this->addProperty("hardwareVersion", &BrickletImpl::getHardwareVersion);
		this->addProperty("firmwareVersion", &BrickletImpl::getFirmwareVersion);
		this->addProperty("deviceIdentifier", &BrickletImpl::getDeviceIdentifier);
		this->addProperty("symbolicName", &BrickletImpl::getSymbolicName);
		this->addProperty("name", &BrickletImpl::getName);
		this->addProperty("type", &BrickletImpl::getType);
		this->addProperty("physicalQuantity", &BrickletImpl::getPhysicalQuantity);
		this->addProperty("physicalUnit", &BrickletImpl::getPhysicalUnit);
	}
		
	~BrickletImpl()
	{
	}
	
protected:
	void setIdentity(const char* uid, const char* masterUID, char position, Poco::UInt8 hardwareVersion[3], Poco::UInt8 firmwareVersion[3], Poco::UInt16 deviceIdentifier)
	{
		_uid = std::string(uid);
		_masterUID = std::string(masterUID);
		_position = std::string(&position, 1);
		_hardwareVersion = Poco::format("%u.%u.%u", static_cast<unsigned>(hardwareVersion[0]), static_cast<unsigned>(hardwareVersion[1]), static_cast<unsigned>(hardwareVersion[2]));
		_firmwareVersion = Poco::format("%u.%u.%u", static_cast<unsigned>(firmwareVersion[0]), static_cast<unsigned>(firmwareVersion[1]), static_cast<unsigned>(firmwareVersion[2]));
		_deviceIdentifier = static_cast<int>(deviceIdentifier);
	}
	
	Poco::Any getUID(const std::string&) const
	{
		return _uid;
	}
	
	Poco::Any getMasterUID(const std::string&) const
	{
		return _masterUID;
	}
	
	Poco::Any getPosition(const std::string&) const
	{
		return _position;
	}
	
	Poco::Any getHardwareVersion(const std::string&) const
	{
		return _hardwareVersion;
	}
	
	Poco::Any getFirmwareVersion(const std::string&) const
	{
		return _firmwareVersion;
	}
	
	Poco::Any getDeviceIdentifier(const std::string&) const
	{
		return _deviceIdentifier;
	}

	Poco::Any getName(const std::string&) const
	{
		return _name;
	}

	Poco::Any getType(const std::string&) const
	{
		return _type;
	}

	Poco::Any getSymbolicName(const std::string&) const
	{
		return _symbolicName;
	}
	
	Poco::Any getPhysicalQuantity(const std::string&) const
	{
		return _physicalQuantity;
	}
	
	Poco::Any getPhysicalUnit(const std::string&) const
	{
		return _physicalUnit;
	}
	
private:
	Poco::Any _uid;
	Poco::Any _masterUID;
	Poco::Any _position;
	Poco::Any _hardwareVersion;
	Poco::Any _firmwareVersion;
	Poco::Any _deviceIdentifier;
	Poco::Any _symbolicName;
	Poco::Any _name;
	Poco::Any _type;
	Poco::Any _physicalQuantity;
	Poco::Any _physicalUnit;
};


} } // namespace IoT::Tf


#endif // IoT_Tf_BrickletImpl_INCLUDED
