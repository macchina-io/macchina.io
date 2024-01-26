//
// IBarcodeReader.cpp
//
// Library: IoT/Devices
// Package: Generated
// Module:  IBarcodeReader
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2022, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: GPL-3.0-only
//


#include "IoT/Devices/IBarcodeReader.h"


namespace IoT {
namespace Devices {


IBarcodeReader::IBarcodeReader():
	IoT::Devices::IDevice(),
	barcodeRead()
{
}


IBarcodeReader::~IBarcodeReader()
{
}


bool IBarcodeReader::isA(const std::type_info& otherType) const
{
	static const std::string name(typeid(IoT::Devices::IBarcodeReader).name());
	return name == otherType.name() || IoT::Devices::IDevice::isA(otherType);
}


const Poco::RemotingNG::Identifiable::TypeId& IBarcodeReader::remoting__typeId()
{
	static const std::string REMOTING__TYPE_ID("IoT.Devices.BarcodeReader");
	return REMOTING__TYPE_ID;
}


const std::type_info& IBarcodeReader::type() const
{
	return typeid(IBarcodeReader);
}


} // namespace Devices
} // namespace IoT

