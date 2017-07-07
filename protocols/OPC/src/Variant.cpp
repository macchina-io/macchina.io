//
// Variant.cpp
//
// $Id$
//
// Library: OPC
// Package: OPC
// Module:  Variant
//
// Copyright (c) 2010-2015, Günter Obiltschnig.
//
// SPDX-License-Identifier:	BSL-1.0
//


#include "IoT/OPC/Variant.h"
//#include "Poco/ByteOrder.h"
//#include "Poco/Exception.h"
//#include "open62541.h"
//#include <iostream>

using namespace Poco;


namespace IoT {
namespace OPC {


Variant::Variant(): _pVariant(UA_Variant_new())
{
	poco_check_ptr(_pVariant);
}


Variant::~Variant()
{
	UA_Variant_delete(_pVariant);
}


Variant::operator UA_Variant*()
{
	return _pVariant;
}


Variant::operator const UA_Variant*() const
{
	return _pVariant;
}


Variant::operator UA_Variant&()
{
	poco_check_ptr(_pVariant);
	return *_pVariant;
}


bool Variant::hasData() const
{
	return _pVariant && _pVariant->data;
}


bool Variant::hasType() const
{
	return _pVariant && _pVariant->type;
}


const UA_DataType& Variant::type() const
{
	poco_check_ptr(_pVariant);
	poco_check_ptr(_pVariant->type);
	return *_pVariant->type;
}


bool Variant::isArray() const
{
	poco_check_ptr(_pVariant);
	return _pVariant->arrayLength > 0;
}


} } // namespace IoT::OPC
