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
	Poco::FastMutex::ScopedLock lock(_mutex);
	
	if (!isConnected()) throw Poco::IllegalStateException("disconnected", _address);

	std::vector<std::string> result;
	std::vector<GATTClient::Service> services = _pGATTClient->services();
	for (std::vector<GATTClient::Service>::const_iterator it = services.begin(); it != services.end(); ++it)
	{
		result.push_back(it->uuid);
	}
	
	return result;
}


std::vector<std::string> PeripheralImpl::characteristics(const std::string& serviceUUID)
{
	Poco::FastMutex::ScopedLock lock(_mutex);

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
	Poco::FastMutex::ScopedLock lock(_mutex);

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


Poco::UInt16 PeripheralImpl::handleForDescriptor(const std::string& serviceUUID, const std::string& descriptorUUID)
{
	Poco::FastMutex::ScopedLock lock(_mutex);

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
	Poco::FastMutex::ScopedLock lock(_mutex);

	if (!isConnected()) throw Poco::IllegalStateException("disconnected", _address);

	std::string value = _pGATTClient->read(valueHandle);
	if (value.size() == 1)
		return static_cast<Poco::UInt8>(value[0]);
	else
		throw Poco::DataFormatException();
}


Poco::Int8 PeripheralImpl::readInt8(Poco::UInt16 valueHandle)
{
	Poco::FastMutex::ScopedLock lock(_mutex);

	if (!isConnected()) throw Poco::IllegalStateException("disconnected", _address);

	std::string value = _pGATTClient->read(valueHandle);
	if (value.size() == 1)
		return static_cast<Poco::Int8>(value[0]);
	else
		throw Poco::DataFormatException();	
}


Poco::UInt16 PeripheralImpl::readUInt16(Poco::UInt16 valueHandle)
{
	Poco::FastMutex::ScopedLock lock(_mutex);

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
	Poco::FastMutex::ScopedLock lock(_mutex);

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
	Poco::FastMutex::ScopedLock lock(_mutex);

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
	Poco::FastMutex::ScopedLock lock(_mutex);

	if (!isConnected()) throw Poco::IllegalStateException("disconnected", _address);

	std::string value = _pGATTClient->read(valueHandle);
	Poco::MemoryInputStream istr(value.data(), value.size());
	Poco::BinaryReader reader(istr, Poco::BinaryReader::LITTLE_ENDIAN_BYTE_ORDER);
	Poco::Int32 result;
	reader >> result;
	return result;
}


std::string PeripheralImpl::read(Poco::UInt16 valueHandle)
{
	Poco::FastMutex::ScopedLock lock(_mutex);

	if (!isConnected()) throw Poco::IllegalStateException("disconnected", _address);

	return _pGATTClient->read(valueHandle);
}


void PeripheralImpl::writeUInt8(Poco::UInt16 valueHandle, Poco::UInt8 value, bool withResponse)
{
	Poco::FastMutex::ScopedLock lock(_mutex);

	if (!isConnected()) throw Poco::IllegalStateException("disconnected", _address);

	std::string d(1, static_cast<char>(value));
	_pGATTClient->write(valueHandle, d, withResponse);
}


void PeripheralImpl::writeInt8(Poco::UInt16 valueHandle, Poco::Int8 value, bool withResponse)
{
	Poco::FastMutex::ScopedLock lock(_mutex);

	if (!isConnected()) throw Poco::IllegalStateException("disconnected", _address);

	std::string d(1, static_cast<char>(value));
	_pGATTClient->write(valueHandle, d, withResponse);
}


void PeripheralImpl::writeUInt16(Poco::UInt16 valueHandle, Poco::UInt16 value, bool withResponse)
{
	Poco::FastMutex::ScopedLock lock(_mutex);

	if (!isConnected()) throw Poco::IllegalStateException("disconnected", _address);

	Poco::UInt16 lv = Poco::ByteOrder::toLittleEndian(value);
	std::string d(reinterpret_cast<char*>(&lv), sizeof(lv));
	_pGATTClient->write(valueHandle, d, withResponse);
}


void PeripheralImpl::writeInt16(Poco::UInt16 valueHandle, Poco::Int16 value, bool withResponse)
{
	Poco::FastMutex::ScopedLock lock(_mutex);

	if (!isConnected()) throw Poco::IllegalStateException("disconnected", _address);

	Poco::UInt16 lv = Poco::ByteOrder::toLittleEndian(value);
	std::string d(reinterpret_cast<char*>(&lv), sizeof(lv));
	_pGATTClient->write(valueHandle, d, withResponse);
}


void PeripheralImpl::writeUInt32(Poco::UInt16 valueHandle, Poco::UInt32 value, bool withResponse)
{
	Poco::FastMutex::ScopedLock lock(_mutex);

	if (!isConnected()) throw Poco::IllegalStateException("disconnected", _address);

	Poco::UInt32 lv = Poco::ByteOrder::toLittleEndian(value);
	std::string d(reinterpret_cast<char*>(&lv), sizeof(lv));
	_pGATTClient->write(valueHandle, d, withResponse);
}


void PeripheralImpl::writeInt32(Poco::UInt16 valueHandle, Poco::UInt32 value, bool withResponse)
{
	Poco::FastMutex::ScopedLock lock(_mutex);

	if (!isConnected()) throw Poco::IllegalStateException("disconnected", _address);

	Poco::Int32 lv = Poco::ByteOrder::toLittleEndian(value);
	std::string d(reinterpret_cast<char*>(&lv), sizeof(lv));
	_pGATTClient->write(valueHandle, d, withResponse);
}


void PeripheralImpl::write(Poco::UInt16 valueHandle, const std::string& value, bool withResponse)
{
	Poco::FastMutex::ScopedLock lock(_mutex);

	if (!isConnected()) throw Poco::IllegalStateException("disconnected", _address);

	_pGATTClient->write(valueHandle, value, withResponse);
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


} } // namespace IoT::BtLE
