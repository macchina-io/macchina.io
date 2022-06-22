//
// IUnitsOfMeasureService.cpp
//
// Library: IoT/UnitsOfMeasure
// Package: Generated
// Module:  IUnitsOfMeasureService
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2018-2022, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: GPL-3.0-only
//


#include "IoT/UnitsOfMeasure/IUnitsOfMeasureService.h"


namespace IoT {
namespace UnitsOfMeasure {


IUnitsOfMeasureService::IUnitsOfMeasureService():
	Poco::OSP::Service()

{
}


IUnitsOfMeasureService::~IUnitsOfMeasureService()
{
}


bool IUnitsOfMeasureService::isA(const std::type_info& otherType) const
{
	std::string name(type().name());
	return name == otherType.name();
}


const Poco::RemotingNG::Identifiable::TypeId& IUnitsOfMeasureService::remoting__typeId()
{
	static const std::string REMOTING__TYPE_ID("IoT.UnitsOfMeasure.UnitsOfMeasureService");
	return REMOTING__TYPE_ID;
}


const std::type_info& IUnitsOfMeasureService::type() const
{
	return typeid(IUnitsOfMeasureService);
}


} // namespace UnitsOfMeasure
} // namespace IoT

