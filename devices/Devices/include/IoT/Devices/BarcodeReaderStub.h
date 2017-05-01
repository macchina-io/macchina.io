//
// BarcodeReaderStub.h
//
// Library: IoT/Devices
// Package: Generated
// Module:  BarcodeReaderStub
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_Devices_BarcodeReaderStub_INCLUDED
#define IoT_Devices_BarcodeReaderStub_INCLUDED


#include "IoT/Devices/BarcodeReaderRemoteObject.h"
#include "Poco/SharedPtr.h"


namespace IoT {
namespace Devices {


class BarcodeReaderStub: public IoT::Devices::BarcodeReaderRemoteObject
	/// The base class for barcode reader devices.
	///
	/// Only a single event, barcodeRead, is supported.
	/// Any device-specific configuration should be
	/// done via device features and properties.
{
public:
	typedef Poco::AutoPtr<BarcodeReaderStub> Ptr;

	BarcodeReaderStub(const Poco::RemotingNG::Identifiable::ObjectId& oid, Poco::SharedPtr<IoT::Devices::BarcodeReader> pServiceObject);
		/// Creates a BarcodeReaderStub.

	virtual ~BarcodeReaderStub();
		/// Destroys the BarcodeReaderStub.

	virtual bool getFeature(const std::string& name) const;
		/// Returns true if the feature with the given name
		/// is enabled, or false otherwise.

	virtual bool getPropertyBool(const std::string& name) const;
		/// Returns the value of the device property with
		/// the given name.
		///
		/// Throws a Poco::NotFoundException if the property
		/// with the given name is unknown.

	virtual double getPropertyDouble(const std::string& name) const;
		/// Returns the value of the device property with
		/// the given name.
		///
		/// Throws a Poco::NotFoundException if the property
		/// with the given name is unknown.

	virtual int getPropertyInt(const std::string& name) const;
		/// Returns the value of the device property with
		/// the given name.
		///
		/// Throws a Poco::NotFoundException if the property
		/// with the given name is unknown.

	virtual std::string getPropertyString(const std::string& name) const;
		/// Returns the value of the device property with
		/// the given name.
		///
		/// Throws a Poco::NotFoundException if the property
		/// with the given name is unknown.

	virtual bool hasFeature(const std::string& name) const;
		/// Returns true if the feature with the given name
		/// is known, or false otherwise.

	virtual bool hasProperty(const std::string& name) const;
		/// Returns true if the property with the given name
		/// exists, or false otherwise.

	virtual std::string remoting__enableEvents(Poco::RemotingNG::Listener::Ptr pListener, bool enable = bool(true));

	virtual void remoting__enableRemoteEvents(const std::string& protocol);

	virtual bool remoting__hasEvents() const;

	virtual const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId() const;

	virtual void setFeature(const std::string& name, bool enable);
		/// Enables or disables the feature with the given name.
		///
		/// Which features are supported is defined by the
		/// actual device implementation.

	virtual void setPropertyBool(const std::string& name, bool value);
		/// Sets a device property.
		///
		/// Which properties are supported is defined by the
		/// actual device implementation.

	virtual void setPropertyDouble(const std::string& name, double value);
		/// Sets a device property.
		///
		/// Which properties are supported is defined by the
		/// actual device implementation.

	virtual void setPropertyInt(const std::string& name, int value);
		/// Sets a device property.
		///
		/// Which properties are supported is defined by the
		/// actual device implementation.

	virtual void setPropertyString(const std::string& name, const std::string& value);
		/// Sets a device property.
		///
		/// Which properties are supported is defined by the
		/// actual device implementation.

protected:
	void event__barcodeRead(const IoT::Devices::BarcodeReadEvent& data);

private:
	Poco::SharedPtr<IoT::Devices::BarcodeReader> _pServiceObject;
};


inline bool BarcodeReaderStub::getFeature(const std::string& name) const
{
	return _pServiceObject->getFeature(name);
}


inline bool BarcodeReaderStub::getPropertyBool(const std::string& name) const
{
	return _pServiceObject->getPropertyBool(name);
}


inline double BarcodeReaderStub::getPropertyDouble(const std::string& name) const
{
	return _pServiceObject->getPropertyDouble(name);
}


inline int BarcodeReaderStub::getPropertyInt(const std::string& name) const
{
	return _pServiceObject->getPropertyInt(name);
}


inline std::string BarcodeReaderStub::getPropertyString(const std::string& name) const
{
	return _pServiceObject->getPropertyString(name);
}


inline bool BarcodeReaderStub::hasFeature(const std::string& name) const
{
	return _pServiceObject->hasFeature(name);
}


inline bool BarcodeReaderStub::hasProperty(const std::string& name) const
{
	return _pServiceObject->hasProperty(name);
}


inline const Poco::RemotingNG::Identifiable::TypeId& BarcodeReaderStub::remoting__typeId() const
{
	return IBarcodeReader::remoting__typeId();
}


inline void BarcodeReaderStub::setFeature(const std::string& name, bool enable)
{
	_pServiceObject->setFeature(name, enable);
}


inline void BarcodeReaderStub::setPropertyBool(const std::string& name, bool value)
{
	_pServiceObject->setPropertyBool(name, value);
}


inline void BarcodeReaderStub::setPropertyDouble(const std::string& name, double value)
{
	_pServiceObject->setPropertyDouble(name, value);
}


inline void BarcodeReaderStub::setPropertyInt(const std::string& name, int value)
{
	_pServiceObject->setPropertyInt(name, value);
}


inline void BarcodeReaderStub::setPropertyString(const std::string& name, const std::string& value)
{
	_pServiceObject->setPropertyString(name, value);
}


} // namespace Devices
} // namespace IoT


#endif // IoT_Devices_BarcodeReaderStub_INCLUDED

