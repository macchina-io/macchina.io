//
// UCUMEssenceParser.h
//
// Library: IoT/UnitsOfMeasure
// Package: UnitsOfMeasure
// Module:  UCUMEssenceParser
//
// Definition of the UCUMEssenceParser class.
//
// Copyright (c) 2018, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_UnitsOfMeasure_UCUMEssenceParser_INCLUDED
#define IoT_UnitsOfMeasure_UCUMEssenceParser_INCLUDED


#include "IoT/UnitsOfMeasure/UnitsOfMeasure.h"
#include <istream>


namespace IoT {
namespace UnitsOfMeasure {


class UnitsOfMeasureServiceImpl;


class IoTUnitsOfMeasure_API UCUMEssenceParser
	/// A parser for the ucum-essence.xml file.
{
public:
	UCUMEssenceParser(UnitsOfMeasureServiceImpl& uoms);
		/// Creates the UCUMEssenceParser with the given UnitsOfMeasureServiceImpl.

	~UCUMEssenceParser();
		/// Destroys the UCUMEssenceParser.

	void parse(std::istream& istr);
		/// Parses the ucum-essence XML file from the given stream.

private:
	UnitsOfMeasureServiceImpl& _uoms;
};


} } // namespace IoT::UnitsOfMeasure


#endif // IoT_UnitsOfMeasure_UCUMEssenceParser_INCLUDED
