//
// GATTPeripheral.cpp
//
// Library: IoT/BtLE
// Package: BtLE
// Module:  GATTPeripheral
//
// Copyright (c) 2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#include "IoT/BtLE/GATTPeripheral.h"
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


GATTPeripheral::GATTPeripheral(const std::string& address, GATTClient::Ptr pGATTClient):
	_address(address),
	_pGATTClient(pGATTClient),
	_logger(Poco::Logger::get("IoT.GATTPeripheral"))
{
	_pGATTClient->connected += Poco::delegate(this, &GATTPeripheral::onConnected);
	_pGATTClient->disconnected += Poco::delegate(this, &GATTPeripheral::onDisconnected);
	_pGATTClient->error += Poco::delegate(this, &GATTPeripheral::onError);
	_pGATTClient->indicationReceived += Poco::delegate(this, &GATTPeripheral::onIndication);
	_pGATTClient->notificationReceived += Poco::delegate(this, &GATTPeripheral::onNotification);
}


GATTPeripheral::~GATTPeripheral()
{
	_pGATTClient->connected -= Poco::delegate(this, &GATTPeripheral::onConnected);
	_pGATTClient->disconnected -= Poco::delegate(this, &GATTPeripheral::onDisconnected);
	_pGATTClient->error -= Poco::delegate(this, &GATTPeripheral::onError);
	_pGATTClient->indicationReceived -= Poco::delegate(this, &GATTPeripheral::onIndication);
	_pGATTClient->notificationReceived -= Poco::delegate(this, &GATTPeripheral::onNotification);
}


void GATTPeripheral::connect()
{
	if (_pGATTClient->state() == GATTClient::GATT_STATE_DISCONNECTED)
	{
		_pGATTClient->connect(_address, GATTClient::GATT_CONNECT_WAIT);
	}
}


void GATTPeripheral::connectAsync()
{
	if (_pGATTClient->state() == GATTClient::GATT_STATE_DISCONNECTED)
	{
		_pGATTClient->connect(_address, GATTClient::GATT_CONNECT_NOWAIT);
	}
}


void GATTPeripheral::disconnect()
{
	_pGATTClient->disconnect();
}


bool GATTPeripheral::isConnected() const
{
	return _pGATTClient->state() == GATTClient::GATT_STATE_CONNECTED;
}


std::string GATTPeripheral::address() const
{
	return _address;
}


std::vector<std::string> GATTPeripheral::services()
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


std::string GATTPeripheral::serviceUUIDForAssignedNumber(Poco::UInt32 assignedNumber)
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


std::vector<std::string> GATTPeripheral::characteristics(const std::string& serviceUUID)
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


Characteristic GATTPeripheral::characteristic(const std::string& serviceUUID, const std::string& characteristicUUID)
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


Characteristic GATTPeripheral::characteristicForAssignedNumber(const std::string& serviceUUID, Poco::UInt32 assignedNumber)
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


Poco::UInt16 GATTPeripheral::handleForDescriptor(const std::string& serviceUUID, const std::string& descriptorUUID)
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


Poco::UInt8 GATTPeripheral::readUInt8(Poco::UInt16 valueHandle)
{
	Poco::Mutex::ScopedLock lock(_mutex);

	if (!isConnected()) throw Poco::IllegalStateException("disconnected", _address);

	std::string value = _pGATTClient->read(valueHandle);
	if (value.size() == 1)
		return static_cast<Poco::UInt8>(value[0]);
	else
		throw Poco::DataFormatException();
}


Poco::Int8 GATTPeripheral::readInt8(Poco::UInt16 valueHandle)
{
	Poco::Mutex::ScopedLock lock(_mutex);

	if (!isConnected()) throw Poco::IllegalStateException("disconnected", _address);

	std::string value = _pGATTClient->read(valueHandle);
	if (value.size() == 1)
		return static_cast<Poco::Int8>(value[0]);
	else
		throw Poco::DataFormatException();	
}


Poco::UInt16 GATTPeripheral::readUInt16(Poco::UInt16 valueHandle)
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


Poco::Int16 GATTPeripheral::readInt16(Poco::UInt16 valueHandle)
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


Poco::UInt32 GATTPeripheral::readUInt32(Poco::UInt16 valueHandle)
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


Poco::Int32 GATTPeripheral::readInt32(Poco::UInt16 valueHandle)
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


std::string GATTPeripheral::readString(Poco::UInt16 valueHandle)
{
	Poco::Mutex::ScopedLock lock(_mutex);

	if (!isConnected()) throw Poco::IllegalStateException("disconnected", _address);

	return _pGATTClient->read(valueHandle);
}


std::vector<char> GATTPeripheral::readBytes(Poco::UInt16 valueHandle)
{
	Poco::Mutex::ScopedLock lock(_mutex);

	if (!isConnected()) throw Poco::IllegalStateException("disconnected", _address);

	std::string str = _pGATTClient->read(valueHandle);
	return std::vector<char>(str.begin(), str.end());
}


void GATTPeripheral::writeUInt8(Poco::UInt16 valueHandle, Poco::UInt8 value, bool withResponse)
{
	Poco::Mutex::ScopedLock lock(_mutex);

	if (!isConnected()) throw Poco::IllegalStateException("disconnected", _address);

	std::string d(1, static_cast<char>(value));
	_pGATTClient->write(valueHandle, d, withResponse);
}


void GATTPeripheral::writeInt8(Poco::UInt16 valueHandle, Poco::Int8 value, bool withResponse)
{
	Poco::Mutex::ScopedLock lock(_mutex);

	if (!isConnected()) throw Poco::IllegalStateException("disconnected", _address);

	std::string d(1, static_cast<char>(value));
	_pGATTClient->write(valueHandle, d, withResponse);
}


void GATTPeripheral::writeUInt16(Poco::UInt16 valueHandle, Poco::UInt16 value, bool withResponse)
{
	Poco::Mutex::ScopedLock lock(_mutex);

	if (!isConnected()) throw Poco::IllegalStateException("disconnected", _address);

	Poco::UInt16 lv = Poco::ByteOrder::toLittleEndian(value);
	std::string d(reinterpret_cast<char*>(&lv), sizeof(lv));
	_pGATTClient->write(valueHandle, d, withResponse);
}


void GATTPeripheral::writeInt16(Poco::UInt16 valueHandle, Poco::Int16 value, bool withResponse)
{
	Poco::Mutex::ScopedLock lock(_mutex);

	if (!isConnected()) throw Poco::IllegalStateException("disconnected", _address);

	Poco::UInt16 lv = Poco::ByteOrder::toLittleEndian(value);
	std::string d(reinterpret_cast<char*>(&lv), sizeof(lv));
	_pGATTClient->write(valueHandle, d, withResponse);
}


void GATTPeripheral::writeUInt32(Poco::UInt16 valueHandle, Poco::UInt32 value, bool withResponse)
{
	Poco::Mutex::ScopedLock lock(_mutex);

	if (!isConnected()) throw Poco::IllegalStateException("disconnected", _address);

	Poco::UInt32 lv = Poco::ByteOrder::toLittleEndian(value);
	std::string d(reinterpret_cast<char*>(&lv), sizeof(lv));
	_pGATTClient->write(valueHandle, d, withResponse);
}


void GATTPeripheral::writeInt32(Poco::UInt16 valueHandle, Poco::UInt32 value, bool withResponse)
{
	Poco::Mutex::ScopedLock lock(_mutex);

	if (!isConnected()) throw Poco::IllegalStateException("disconnected", _address);

	Poco::Int32 lv = Poco::ByteOrder::toLittleEndian(value);
	std::string d(reinterpret_cast<char*>(&lv), sizeof(lv));
	_pGATTClient->write(valueHandle, d, withResponse);
}


void GATTPeripheral::writeString(Poco::UInt16 valueHandle, const std::string& value, bool withResponse)
{
	Poco::Mutex::ScopedLock lock(_mutex);

	if (!isConnected()) throw Poco::IllegalStateException("disconnected", _address);

	_pGATTClient->write(valueHandle, value, withResponse);
}


void GATTPeripheral::writeBytes(Poco::UInt16 valueHandle, const std::vector<char>& value, bool withResponse)
{
	Poco::Mutex::ScopedLock lock(_mutex);

	if (!isConnected()) throw Poco::IllegalStateException("disconnected", _address);
	if (value.empty()) throw Poco::InvalidArgumentException("empty value");

	std::string data(value.begin(), value.end());
	_pGATTClient->write(valueHandle, data, withResponse);
}


std::string GATTPeripheral::manufacturerName()
{
	Poco::Mutex::ScopedLock lock(_mutex);

	if (_manufacturerName.empty())
	{
		_manufacturerName = readDeviceInformation(0x2a29);
	}
	return _manufacturerName;
}


std::string GATTPeripheral::modelNumber()
{
	Poco::Mutex::ScopedLock lock(_mutex);

	if (_modelNumber.empty())
	{
		_modelNumber = readDeviceInformation(0x2a24);
	}
	return _modelNumber;
}


std::string GATTPeripheral::serialNumber()
{
	Poco::Mutex::ScopedLock lock(_mutex);

	if (_serialNumber.empty())
	{
		_serialNumber = readDeviceInformation(0x2a25);
	}
	return _serialNumber;
}


std::string GATTPeripheral::hardwareRevision()
{
	Poco::Mutex::ScopedLock lock(_mutex);

	if (_hardwareRevision.empty())
	{
		_hardwareRevision = readDeviceInformation(0x2a27);
	}
	return _hardwareRevision;
}


std::string GATTPeripheral::firmwareRevision()
{
	Poco::Mutex::ScopedLock lock(_mutex);

	if (_firmwareRevision.empty())
	{
		_firmwareRevision = readDeviceInformation(0x2a26);
	}
	return _firmwareRevision;
}


std::string GATTPeripheral::softwareRevision()
{
	Poco::Mutex::ScopedLock lock(_mutex);

	if (_softwareRevision.empty())
	{
		_softwareRevision = readDeviceInformation(0x2a28);
	}
	return _softwareRevision;
}


void GATTPeripheral::onConnected()
{
	connected(this);
}


void GATTPeripheral::onDisconnected()
{
	disconnected(this);
}


void GATTPeripheral::onError(const std::string& err)
{
	error(this, err);
}


void GATTPeripheral::onIndication(const GATTClient::Indication& gattInd)
{
	Indication ind;
	ind.handle = gattInd.handle;
	ind.data   = gattInd.data;
	indicationReceived(ind);
}


void GATTPeripheral::onNotification(const GATTClient::Notification& gattNf)
{
	Notification nf;
	nf.handle = gattNf.handle;
	nf.data   = gattNf.data;
	notificationReceived(nf);
}


std::string GATTPeripheral::readDeviceInformation(Poco::UInt32 assignedNumber)
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
