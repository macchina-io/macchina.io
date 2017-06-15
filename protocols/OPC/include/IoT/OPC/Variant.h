//
// Variant.h
//
// $Id$
//
// Library: OPC
// Package: OPC
// Module:  Variant
//
// Definitions of the OPC standard types classes as specified in
// in OPC UA Part 3, 8. Standard Data Types.
//
// Copyright (c) 2010-2015, Günter Obiltschnig.
//
// SPDX-License-Identifier:	BSL-1.0
//


#ifndef IoT_OPC_Variant_INCLUDED
#define IoT_OPC_Variant_INCLUDED


#include "IoT/OPC/OPC.h"
#include "Poco/Types.h"
#include "open62541.h"
/*#include "Poco/UUID.h"
#include "Poco/StringTokenizer.h"
#include "Poco/Dynamic/VarHolder.h"
#include <vector>
#include <cstring>
#include <chrono>*/


namespace IoT {
namespace OPC {


class Variant
{
public:
	Variant();

	~Variant();

	operator UA_Variant*();

	operator const UA_Variant*() const;

	operator UA_Variant&();

	bool hasData() const;

	const UA_DataType& type() const;

	bool isArray() const;

private:
	Variant(const Variant&);
	Variant& operator = (const Variant&);

	UA_Variant* _pVariant;
};


} } // namespace IoT::OPC


#endif // IoT_OPC_Variant_INCLUDED
