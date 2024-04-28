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
// SPDX-License-Identifier: GPL-3.0-only
//


#include "IoT/BtLE/GATTPeripheral.h"
#include "Poco/MemoryStream.h"
#include "Poco/BinaryReader.h"
#include "Poco/BinaryWriter.h"
#include "Poco/ByteOrder.h"
#include "Poco/Exception.h"
#include "Poco/Delegate.h"
#include "Poco/NumberFormatter.h"
#include "Poco/Format.h"
#include "Poco/String.h"
#include "Poco/ByteOrder.h"
#include <cstring>


using namespace std::string_literals;


namespace IoT {
namespace BtLE {


GATTPeripheral::GATTPeripheral(const std::string& address, GATTClient::Ptr pGATTClient):
	_address(Poco::toUpper(address)),
	_pGATTClient(pGATTClient),
	_logger(Poco::Logger::get("IoT.GATTPeripheral"s))
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


std::vector<Poco::UUID> GATTPeripheral::services()
{
	Poco::Mutex::ScopedLock lock(_mutex);

	if (!isConnected()) throw Poco::IllegalStateException("disconnected"s, _address);

	std::vector<Poco::UUID> result;
	std::vector<GATTClient::Service> services = _pGATTClient->services();
	for (std::vector<GATTClient::Service>::const_iterator it = services.begin(); it != services.end(); ++it)
	{
		result.push_back(it->uuid);
	}

	return result;
}


Poco::UUID GATTPeripheral::serviceUUIDForAssignedNumber(Poco::UInt32 assignedNumber)
{
	Poco::Mutex::ScopedLock lock(_mutex);

	if (!isConnected()) throw Poco::IllegalStateException("disconnected"s, _address);

	Poco::UUID uuid = expandUUID(assignedNumber);
	std::vector<GATTClient::Service> services = _pGATTClient->services();
	for (std::vector<GATTClient::Service>::const_iterator it = services.begin(); it != services.end(); ++it)
	{
		if (it->uuid == uuid)
		{
			break;
		}
	}

	return Poco::UUID::null();
}


std::vector<Poco::UUID> GATTPeripheral::characteristics(const Poco::UUID& serviceUUID)
{
	Poco::Mutex::ScopedLock lock(_mutex);

	if (!isConnected()) throw Poco::IllegalStateException("disconnected"s, _address);

	std::vector<Poco::UUID> result;
	std::vector<GATTClient::Characteristic> chars = _pGATTClient->characteristics(serviceUUID);
	for (std::vector<GATTClient::Characteristic>::const_iterator it = chars.begin(); it != chars.end(); ++it)
	{
		result.push_back(it->uuid);
	}

	return result;
}


Characteristic GATTPeripheral::characteristic(const Poco::UUID& serviceUUID, const Poco::UUID& characteristicUUID)
{
	Poco::Mutex::ScopedLock lock(_mutex);

	if (!isConnected()) throw Poco::IllegalStateException("disconnected"s, _address);

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
	throw Poco::NotFoundException("characteristic"s, characteristicUUID.toString());
}


Characteristic GATTPeripheral::characteristicForAssignedNumber(const Poco::UUID& serviceUUID, Poco::UInt32 assignedNumber)
{
	Poco::Mutex::ScopedLock lock(_mutex);

	if (!isConnected()) throw Poco::IllegalStateException("disconnected"s, _address);

	Poco::UUID charUUID = expandUUID(assignedNumber);
	std::vector<GATTClient::Characteristic> chars = _pGATTClient->characteristics(serviceUUID);
	for (std::vector<GATTClient::Characteristic>::const_iterator it = chars.begin(); it != chars.end(); ++it)
	{
		if (it->uuid == charUUID)
		{
			Characteristic chara;
			chara.properties = it->properties;
			chara.valueHandle = it->valueHandle;
			return chara;
		}
	}
	throw Poco::NotFoundException("characteristic"s, charUUID.toString());
}


Handle GATTPeripheral::handleForDescriptor(const Poco::UUID& serviceUUID, const Poco::UUID& characteristicUUID, const Poco::UUID& descriptorUUID)
{
	Poco::Mutex::ScopedLock lock(_mutex);

	if (!isConnected()) throw Poco::IllegalStateException("disconnected"s, _address);

	std::vector<GATTClient::Descriptor> descs = _pGATTClient->descriptors(serviceUUID);
	std::vector<GATTClient::Characteristic> chars = _pGATTClient->characteristics(serviceUUID);
	for (std::vector<GATTClient::Characteristic>::const_iterator itc = chars.begin(); itc != chars.end(); ++itc)
	{
		if (itc->uuid == characteristicUUID)
		{
			for (std::vector<GATTClient::Descriptor>::const_iterator itd = descs.begin(); itd != descs.end(); ++itd)
			{
				if (itd->handle >= itc->handle && itd->handle <= itc->lastHandle && itd->uuid == descriptorUUID)
				{
					return itd->handle;
				}
			}
		}
	}
	throw Poco::NotFoundException("handle with descriptor"s, descriptorUUID.toString());
}


Poco::UInt8 GATTPeripheral::readUInt8(Handle valueHandle)
{
	Poco::Mutex::ScopedLock lock(_mutex);

	if (!isConnected()) throw Poco::IllegalStateException("disconnected"s, _address);

	std::string value = _pGATTClient->read(valueHandle);
	if (value.size() == 1)
		return static_cast<Poco::UInt8>(value[0]);
	else
		throw Poco::DataFormatException();
}


Poco::Int8 GATTPeripheral::readInt8(Handle valueHandle)
{
	Poco::Mutex::ScopedLock lock(_mutex);

	if (!isConnected()) throw Poco::IllegalStateException("disconnected"s, _address);

	std::string value = _pGATTClient->read(valueHandle);
	if (value.size() == 1)
		return static_cast<Poco::Int8>(value[0]);
	else
		throw Poco::DataFormatException();
}


Poco::UInt16 GATTPeripheral::readUInt16(Handle valueHandle)
{
	return readValue<Poco::UInt16>(valueHandle);
}


Poco::Int16 GATTPeripheral::readInt16(Handle valueHandle)
{
	return readValue<Poco::Int16>(valueHandle);
}


Poco::UInt32 GATTPeripheral::readUInt32(Handle valueHandle)
{
	return readValue<Poco::UInt32>(valueHandle);
}


Poco::Int32 GATTPeripheral::readInt32(Handle valueHandle)
{
	return readValue<Poco::Int32>(valueHandle);
}


Poco::UInt64 GATTPeripheral::readUInt64(Handle valueHandle)
{
	return readValue<Poco::UInt64>(valueHandle);
}


Poco::Int64 GATTPeripheral::readInt64(Handle valueHandle)
{
	return readValue<Poco::Int64>(valueHandle);
}


float GATTPeripheral::readFloat(Handle valueHandle)
{
	return readValue<float>(valueHandle);
}


double GATTPeripheral::readDouble(Handle valueHandle)
{
	return readValue<double>(valueHandle);
}


std::string GATTPeripheral::readString(Handle valueHandle)
{
	Poco::Mutex::ScopedLock lock(_mutex);

	if (!isConnected()) throw Poco::IllegalStateException("disconnected"s, _address);

	return _pGATTClient->read(valueHandle);
}


std::string GATTPeripheral::readString0(Handle valueHandle)
{
	std::string value = readString(valueHandle);
	value.resize(std::strlen(value.c_str()));
	return value;
}


std::vector<char> GATTPeripheral::readBytes(Handle valueHandle)
{
	Poco::Mutex::ScopedLock lock(_mutex);

	if (!isConnected()) throw Poco::IllegalStateException("disconnected"s, _address);

	std::string str = _pGATTClient->read(valueHandle);
	return std::vector<char>(str.begin(), str.end());
}


void GATTPeripheral::writeUInt8(Handle valueHandle, Poco::UInt8 value, bool withResponse)
{
	writeValue(valueHandle, value, withResponse);
}


void GATTPeripheral::writeInt8(Handle valueHandle, Poco::Int8 value, bool withResponse)
{
	writeValue(valueHandle, value, withResponse);
}


void GATTPeripheral::writeUInt16(Handle valueHandle, Poco::UInt16 value, bool withResponse)
{
	writeValue(valueHandle, value, withResponse);
}


void GATTPeripheral::writeInt16(Handle valueHandle, Poco::Int16 value, bool withResponse)
{
	writeValue(valueHandle, value, withResponse);
}


void GATTPeripheral::writeUInt32(Handle valueHandle, Poco::UInt32 value, bool withResponse)
{
	writeValue(valueHandle, value, withResponse);
}


void GATTPeripheral::writeInt32(Handle valueHandle, Poco::Int32 value, bool withResponse)
{
	writeValue(valueHandle, value, withResponse);
}


void GATTPeripheral::writeUInt64(Handle valueHandle, Poco::UInt64 value, bool withResponse)
{
	writeValue(valueHandle, value, withResponse);
}


void GATTPeripheral::writeInt64(Handle valueHandle, Poco::Int64 value, bool withResponse)
{
	writeValue(valueHandle, value, withResponse);
}


void GATTPeripheral::writeFloat(Handle valueHandle, float value, bool withResponse)
{
	writeValue(valueHandle, value, withResponse);
}


void GATTPeripheral::writeDouble(Handle valueHandle, double value, bool withResponse)
{
	writeValue(valueHandle, value, withResponse);
}


void GATTPeripheral::writeString(Handle valueHandle, const std::string& value, bool withResponse)
{
	Poco::Mutex::ScopedLock lock(_mutex);

	if (!isConnected()) throw Poco::IllegalStateException("disconnected"s, _address);

	_pGATTClient->write(valueHandle, value, withResponse);
}


void GATTPeripheral::writeBytes(Handle valueHandle, const std::vector<char>& value, bool withResponse)
{
	Poco::Mutex::ScopedLock lock(_mutex);

	if (!isConnected()) throw Poco::IllegalStateException("disconnected"s, _address);
	if (value.empty()) throw Poco::InvalidArgumentException("empty value"s);

	std::string data(value.begin(), value.end());
	_pGATTClient->write(valueHandle, data, withResponse);
}


std::string GATTPeripheral::deviceName()
{
	Poco::Mutex::ScopedLock lock(_mutex);

	if (_deviceName.empty())
	{
		Poco::UUID serviceUUID = serviceUUIDForAssignedNumber(0x1800);
		std::string result;
		if (!serviceUUID.isNull())
		{
			Characteristic chara = characteristicForAssignedNumber(serviceUUID, 0x2A00);
			_deviceName = readString0(chara.valueHandle);
		}
	}
	return _deviceName;
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


Poco::UUID GATTPeripheral::expandUUID(Poco::UInt32 uuid)
{
	unsigned char buffer[16] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x80, 0x00, 0x00, 0x80, 0x5f, 0x9b, 0x34, 0xfb};
	Poco::UInt32 uuidBE = Poco::ByteOrder::toBigEndian(uuid);
	std::memcpy(buffer, &uuidBE, 4);
	Poco::UUID result;
	result.copyFrom(reinterpret_cast<char*>(buffer));
	return result;
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
	Poco::UUID serviceUUID = serviceUUIDForAssignedNumber(0x180a);
	std::string result;
	if (!serviceUUID.isNull())
	{
		Characteristic chara = characteristicForAssignedNumber(serviceUUID, assignedNumber);
		result = readString0(chara.valueHandle);
	}
	return result;
}


template <typename T>
T GATTPeripheral::readValue(Handle valueHandle)
{
	Poco::Mutex::ScopedLock lock(_mutex);

	if (!isConnected()) throw Poco::IllegalStateException("disconnected", _address);

	std::string value = _pGATTClient->read(valueHandle);
	if (value.size() != sizeof(T)) throw Poco::DataFormatException(Poco::format("Characteristic value size mismatch: %z bytes required, %z bytes received"s, sizeof(T), value.size()));

	Poco::MemoryInputStream istr(value.data(), value.size());
	Poco::BinaryReader reader(istr, Poco::BinaryReader::LITTLE_ENDIAN_BYTE_ORDER);
	T result;
	reader >> result;
	return result;
}


template <typename T>
void GATTPeripheral::writeValue(Handle valueHandle, T value, bool withResponse)
{
	Poco::Mutex::ScopedLock lock(_mutex);

	if (!isConnected()) throw Poco::IllegalStateException("disconnected"s, _address);

	char buffer[sizeof(T)];
	Poco::MemoryOutputStream ostr(buffer, sizeof(T));
	Poco::BinaryWriter writer(ostr, Poco::BinaryWriter::LITTLE_ENDIAN_BYTE_ORDER);
	writer << value;
	_pGATTClient->write(valueHandle, buffer, sizeof(T), withResponse);
}


} } // namespace IoT::BtLE
