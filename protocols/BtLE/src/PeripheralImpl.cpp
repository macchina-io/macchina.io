//
// PeripheralImpl.cpp
//
// $Id$
//
// Library: IoT/BtLE
// Package: BtLE
// Module:  PeripheralImpl
//
// Copyright (c) 2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#include "IoT/BtLE/PeripheralImpl.h"
#include "Poco/MemoryStream.h"
#include "Poco/BinaryReader.h"
#include "Poco/BinaryWriter.h"
#include "Poco/ByteOrder.h"
#include "Poco/Exception.h"
#include "Poco/Delegate.h"
#include "Poco/NumberFormatter.h"
#include "Poco/String.h"


namespace IoT {
namespace BtLE {


PeripheralImpl::PeripheralImpl(const std::string& address, GATTClient::Ptr pGATTClient):
	_address(address),
	_pGATTClient(pGATTClient),
	_logger(Poco::Logger::get("IoT.PeripheralImpl"))
{
	_pGATTClient->connected += Poco::delegate(this, &PeripheralImpl::onConnected);
	_pGATTClient->disconnected += Poco::delegate(this, &PeripheralImpl::onDisconnected);
	_pGATTClient->error += Poco::delegate(this, &PeripheralImpl::onError);
	_pGATTClient->indicationReceived += Poco::delegate(this, &PeripheralImpl::onIndication);
	_pGATTClient->notificationReceived += Poco::delegate(this, &PeripheralImpl::onNotification);
}


PeripheralImpl::~PeripheralImpl()
{
	_pGATTClient->connected -= Poco::delegate(this, &PeripheralImpl::onConnected);
	_pGATTClient->disconnected -= Poco::delegate(this, &PeripheralImpl::onDisconnected);
	_pGATTClient->error -= Poco::delegate(this, &PeripheralImpl::onError);
	_pGATTClient->indicationReceived -= Poco::delegate(this, &PeripheralImpl::onIndication);
	_pGATTClient->notificationReceived -= Poco::delegate(this, &PeripheralImpl::onNotification);
}


void PeripheralImpl::connect(GATTClient::ConnectMode mode)
{
	if (_pGATTClient->state() == GATTClient::GATT_STATE_DISCONNECTED)
	{
		_pGATTClient->connect(_address, mode);
	}
}


void PeripheralImpl::disconnect()
{
	_pGATTClient->disconnect();
}


bool PeripheralImpl::isConnected() const
{
	return _pGATTClient->state() == GATTClient::GATT_STATE_CONNECTED;
}


std::string PeripheralImpl::address() const
{
	return _address;
}


std::vector<std::string> PeripheralImpl::services()
{
	Poco::Mutex::ScopedLock lock(_mutex);
	
	if (!isConnected()) throw Poco::IllegalStateException("disconnected", _address);

	std::vector<std::string> result;
	std::vector<GATTClient::Service> services = _pGATTClient->services();
	for (std::vector<GATTClient::Service>::const_iterator it = services.begin(); it != services.end(); ++it)
	{
		result.push_back(it->uuid);
	}
	
	return result;
}


std::string PeripheralImpl::serviceUUIDForAssignedNumber(Poco::UInt32 assignedNumber)
{
	Poco::Mutex::ScopedLock lock(_mutex);
	
	if (!isConnected()) throw Poco::IllegalStateException("disconnected", _address);

	std::string uuid;
	std::string prefix = Poco::NumberFormatter::formatHex(assignedNumber, 8);
	std::vector<GATTClient::Service> services = _pGATTClient->services();
	for (std::vector<GATTClient::Service>::const_iterator it = services.begin(); it != services.end(); ++it)
	{
		if (Poco::icompare(it->uuid, 8, prefix) == 0)
		{
			uuid = it->uuid;
			break;
		}
	}

	return uuid;
}


std::vector<std::string> PeripheralImpl::characteristics(const std::string& serviceUUID)
{
	Poco::Mutex::ScopedLock lock(_mutex);

	if (!isConnected()) throw Poco::IllegalStateException("disconnected", _address);

	std::vector<std::string> result;
	std::vector<GATTClient::Characteristic> chars = _pGATTClient->characteristics(serviceUUID);
	for (std::vector<GATTClient::Characteristic>::const_iterator it = chars.begin(); it != chars.end(); ++it)
	{
		result.push_back(it->uuid);
	}
	
	return result;
}


Characteristic PeripheralImpl::characteristic(const std::string& serviceUUID, const std::string& characteristicUUID)
{
	Poco::Mutex::ScopedLock lock(_mutex);

	if (!isConnected()) throw Poco::IllegalStateException("disconnected", _address);

	std::vector<GATTClient::Characteristic> chars = _pGATTClient->characteristics(serviceUUID);
	for (std::vector<GATTClient::Characteristic>::const_iterator it = chars.begin(); it != chars.end(); ++it)
	{
		if (it->uuid == characteristicUUID)
		{
			Characteristic chara;
			chara.properties = it->properties;
			chara.valueHandle = it->valueHandle;
			return chara;
		}
	}
	throw Poco::NotFoundException("characteristic", characteristicUUID);
}


Characteristic PeripheralImpl::characteristicForAssignedNumber(const std::string& serviceUUID, Poco::UInt32 assignedNumber)
{
	Poco::Mutex::ScopedLock lock(_mutex);

	if (!isConnected()) throw Poco::IllegalStateException("disconnected", _address);

	std::string prefix = Poco::NumberFormatter::formatHex(assignedNumber, 8);
	std::vector<GATTClient::Characteristic> chars = _pGATTClient->characteristics(serviceUUID);
	for (std::vector<GATTClient::Characteristic>::const_iterator it = chars.begin(); it != chars.end(); ++it)
	{
		if (Poco::icompare(it->uuid, 8, prefix) == 0)
		{
			Characteristic chara;
			chara.properties = it->properties;
			chara.valueHandle = it->valueHandle;
			return chara;
		}
	}
	throw Poco::NotFoundException("characteristic", prefix);
}


Poco::UInt16 PeripheralImpl::handleForDescriptor(const std::string& serviceUUID, const std::string& descriptorUUID)
{
	Poco::Mutex::ScopedLock lock(_mutex);

	if (!isConnected()) throw Poco::IllegalStateException("disconnected", _address);

	std::vector<GATTClient::Descriptor> descs = _pGATTClient->descriptors(serviceUUID);
	for (std::vector<GATTClient::Descriptor>::const_iterator it = descs.begin(); it != descs.end(); ++it)
	{
		if (it->uuid == descriptorUUID)
		{
			return it->handle;
		}
	}
	throw Poco::NotFoundException("handle with descriptor", descriptorUUID);
}


Poco::UInt8 PeripheralImpl::readUInt8(Poco::UInt16 valueHandle)
{
	Poco::Mutex::ScopedLock lock(_mutex);

	if (!isConnected()) throw Poco::IllegalStateException("disconnected", _address);

	std::string value = _pGATTClient->read(valueHandle);
	if (value.size() == 1)
		return static_cast<Poco::UInt8>(value[0]);
	else
		throw Poco::DataFormatException();
}


Poco::Int8 PeripheralImpl::readInt8(Poco::UInt16 valueHandle)
{
	Poco::Mutex::ScopedLock lock(_mutex);

	if (!isConnected()) throw Poco::IllegalStateException("disconnected", _address);

	std::string value = _pGATTClient->read(valueHandle);
	if (value.size() == 1)
		return static_cast<Poco::Int8>(value[0]);
	else
		throw Poco::DataFormatException();	
}


Poco::UInt16 PeripheralImpl::readUInt16(Poco::UInt16 valueHandle)
{
	Poco::Mutex::ScopedLock lock(_mutex);

	if (!isConnected()) throw Poco::IllegalStateException("disconnected", _address);

	std::string value = _pGATTClient->read(valueHandle);
	Poco::MemoryInputStream istr(value.data(), value.size());
	Poco::BinaryReader reader(istr, Poco::BinaryReader::LITTLE_ENDIAN_BYTE_ORDER);
	Poco::UInt16 result;
	reader >> result;
	return result;
}


Poco::Int16 PeripheralImpl::readInt16(Poco::UInt16 valueHandle)
{
	Poco::Mutex::ScopedLock lock(_mutex);

	if (!isConnected()) throw Poco::IllegalStateException("disconnected", _address);

	std::string value = _pGATTClient->read(valueHandle);
	Poco::MemoryInputStream istr(value.data(), value.size());
	Poco::BinaryReader reader(istr, Poco::BinaryReader::LITTLE_ENDIAN_BYTE_ORDER);
	Poco::Int16 result;
	reader >> result;
	return result;
}


Poco::UInt32 PeripheralImpl::readUInt32(Poco::UInt16 valueHandle)
{
	Poco::Mutex::ScopedLock lock(_mutex);

	if (!isConnected()) throw Poco::IllegalStateException("disconnected", _address);

	std::string value = _pGATTClient->read(valueHandle);
	Poco::MemoryInputStream istr(value.data(), value.size());
	Poco::BinaryReader reader(istr, Poco::BinaryReader::LITTLE_ENDIAN_BYTE_ORDER);
	Poco::UInt32 result;
	reader >> result;
	return result;
}


Poco::Int32 PeripheralImpl::readInt32(Poco::UInt16 valueHandle)
{
	Poco::Mutex::ScopedLock lock(_mutex);

	if (!isConnected()) throw Poco::IllegalStateException("disconnected", _address);

	std::string value = _pGATTClient->read(valueHandle);
	Poco::MemoryInputStream istr(value.data(), value.size());
	Poco::BinaryReader reader(istr, Poco::BinaryReader::LITTLE_ENDIAN_BYTE_ORDER);
	Poco::Int32 result;
	reader >> result;
	return result;
}


std::string PeripheralImpl::readString(Poco::UInt16 valueHandle)
{
	Poco::Mutex::ScopedLock lock(_mutex);

	if (!isConnected()) throw Poco::IllegalStateException("disconnected", _address);

	return _pGATTClient->read(valueHandle);
}


std::vector<char> PeripheralImpl::readBytes(Poco::UInt16 valueHandle)
{
	Poco::Mutex::ScopedLock lock(_mutex);

	if (!isConnected()) throw Poco::IllegalStateException("disconnected", _address);

	std::string str = _pGATTClient->read(valueHandle);
	return std::vector<char>(str.begin(), str.end());
}


void PeripheralImpl::writeUInt8(Poco::UInt16 valueHandle, Poco::UInt8 value, bool withResponse)
{
	Poco::Mutex::ScopedLock lock(_mutex);

	if (!isConnected()) throw Poco::IllegalStateException("disconnected", _address);

	std::string d(1, static_cast<char>(value));
	_pGATTClient->write(valueHandle, d, withResponse);
}


void PeripheralImpl::writeInt8(Poco::UInt16 valueHandle, Poco::Int8 value, bool withResponse)
{
	Poco::Mutex::ScopedLock lock(_mutex);

	if (!isConnected()) throw Poco::IllegalStateException("disconnected", _address);

	std::string d(1, static_cast<char>(value));
	_pGATTClient->write(valueHandle, d, withResponse);
}


void PeripheralImpl::writeUInt16(Poco::UInt16 valueHandle, Poco::UInt16 value, bool withResponse)
{
	Poco::Mutex::ScopedLock lock(_mutex);

	if (!isConnected()) throw Poco::IllegalStateException("disconnected", _address);

	Poco::UInt16 lv = Poco::ByteOrder::toLittleEndian(value);
	std::string d(reinterpret_cast<char*>(&lv), sizeof(lv));
	_pGATTClient->write(valueHandle, d, withResponse);
}


void PeripheralImpl::writeInt16(Poco::UInt16 valueHandle, Poco::Int16 value, bool withResponse)
{
	Poco::Mutex::ScopedLock lock(_mutex);

	if (!isConnected()) throw Poco::IllegalStateException("disconnected", _address);

	Poco::UInt16 lv = Poco::ByteOrder::toLittleEndian(value);
	std::string d(reinterpret_cast<char*>(&lv), sizeof(lv));
	_pGATTClient->write(valueHandle, d, withResponse);
}


void PeripheralImpl::writeUInt32(Poco::UInt16 valueHandle, Poco::UInt32 value, bool withResponse)
{
	Poco::Mutex::ScopedLock lock(_mutex);

	if (!isConnected()) throw Poco::IllegalStateException("disconnected", _address);

	Poco::UInt32 lv = Poco::ByteOrder::toLittleEndian(value);
	std::string d(reinterpret_cast<char*>(&lv), sizeof(lv));
	_pGATTClient->write(valueHandle, d, withResponse);
}


void PeripheralImpl::writeInt32(Poco::UInt16 valueHandle, Poco::UInt32 value, bool withResponse)
{
	Poco::Mutex::ScopedLock lock(_mutex);

	if (!isConnected()) throw Poco::IllegalStateException("disconnected", _address);

	Poco::Int32 lv = Poco::ByteOrder::toLittleEndian(value);
	std::string d(reinterpret_cast<char*>(&lv), sizeof(lv));
	_pGATTClient->write(valueHandle, d, withResponse);
}


void PeripheralImpl::writeString(Poco::UInt16 valueHandle, const std::string& value, bool withResponse)
{
	Poco::Mutex::ScopedLock lock(_mutex);

	if (!isConnected()) throw Poco::IllegalStateException("disconnected", _address);

	_pGATTClient->write(valueHandle, value, withResponse);
}


void PeripheralImpl::writeBytes(Poco::UInt16 valueHandle, const std::vector<char>& value, bool withResponse)
{
	Poco::Mutex::ScopedLock lock(_mutex);

	if (!isConnected()) throw Poco::IllegalStateException("disconnected", _address);
	if (value.empty()) throw Poco::InvalidArgumentException("empty value");

	std::string data(value.begin(), value.end());
	_pGATTClient->write(valueHandle, data, withResponse);
}


std::string PeripheralImpl::manufacturerName()
{
	Poco::Mutex::ScopedLock lock(_mutex);

	if (_manufacturerName.empty())
	{
		_manufacturerName = readDeviceInformation(0x2a29);
	}
	return _manufacturerName;
}


std::string PeripheralImpl::modelNumber()
{
	Poco::Mutex::ScopedLock lock(_mutex);

	if (_modelNumber.empty())
	{
		_modelNumber = readDeviceInformation(0x2a24);
	}
	return _modelNumber;
}


std::string PeripheralImpl::serialNumber()
{
	Poco::Mutex::ScopedLock lock(_mutex);

	if (_serialNumber.empty())
	{
		_serialNumber = readDeviceInformation(0x2a25);
	}
	return _serialNumber;
}


std::string PeripheralImpl::hardwareRevision()
{
	Poco::Mutex::ScopedLock lock(_mutex);

	if (_hardwareRevision.empty())
	{
		_hardwareRevision = readDeviceInformation(0x2a27);
	}
	return _hardwareRevision;
}


std::string PeripheralImpl::firmwareRevision()
{
	Poco::Mutex::ScopedLock lock(_mutex);

	if (_firmwareRevision.empty())
	{
		_firmwareRevision = readDeviceInformation(0x2a26);
	}
	return _firmwareRevision;
}


std::string PeripheralImpl::softwareRevision()
{
	Poco::Mutex::ScopedLock lock(_mutex);

	if (_softwareRevision.empty())
	{
		_softwareRevision = readDeviceInformation(0x2a28);
	}
	return _softwareRevision;
}


void PeripheralImpl::onConnected()
{
	connected(this);
}


void PeripheralImpl::onDisconnected()
{
	disconnected(this);
}


void PeripheralImpl::onError(const std::string& err)
{
	error(this, err);
}


void PeripheralImpl::onIndication(const GATTClient::Indication& ind)
{
	indicationReceived(ind);
}


void PeripheralImpl::onNotification(const GATTClient::Notification& nf)
{
	notificationReceived(nf);
}


std::string PeripheralImpl::readDeviceInformation(Poco::UInt32 assignedNumber)
{
	std::string serviceUUID = serviceUUIDForAssignedNumber(0x180a);
	std::string result;	
	if (!serviceUUID.empty())
	{
		Characteristic chara = characteristicForAssignedNumber(serviceUUID, assignedNumber);
		result = readString(chara.valueHandle);
	}
	return result;
}


} } // namespace IoT::BtLE
