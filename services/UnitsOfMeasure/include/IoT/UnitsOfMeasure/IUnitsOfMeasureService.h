//
// IUnitsOfMeasureService.h
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


#ifndef IoT_UnitsOfMeasure_IUnitsOfMeasureService_INCLUDED
#define IoT_UnitsOfMeasure_IUnitsOfMeasureService_INCLUDED


#include "IoT/UnitsOfMeasure/UnitsOfMeasureService.h"
#include "Poco/AutoPtr.h"
#include "Poco/OSP/Service.h"
#include "Poco/RemotingNG/Identifiable.h"


namespace IoT {
namespace UnitsOfMeasure {


class IUnitsOfMeasureService: public Poco::OSP::Service
	/// The UnitsOfMeasureService service is mainly used to map
	/// [[http://unitsofmeasure.org/ucum.html Unified Code for Units of Measure]] (UCUM),
	/// codes, such as used with the IoT::Devices::Sensor interface, to display/print units.
	///
	/// It provides a programmatic interface to the
	/// [[http://unitsofmeasure.org/ucum-essence.xml UCUM-Essence XML file]]
	/// containing unit definitions.
{
public:
	using Ptr = Poco::AutoPtr<IUnitsOfMeasureService>;

	IUnitsOfMeasureService();
		/// Creates a IUnitsOfMeasureService.

	virtual ~IUnitsOfMeasureService();
		/// Destroys the IUnitsOfMeasureService.

	virtual IoT::UnitsOfMeasure::CanonicalValue canonicalize(double value, const std::string& prefixedCode) const = 0;
		/// Removes the prefix from the code and scales the value accordingly.

	virtual double convert(double value, const std::string& fromPrefixedCode, const std::string& toPrefixedCode) const = 0;
		/// Attempts to convert the value from one unit (given in fromPrefixedCode) to a different one
		/// (given in toPrefixedCode). Conversion only works if both units share the same base unit,
		/// which must be atomic. Unfortunately, this means that conversion only works for
		/// a small set of unit pairs, e.g. from km to nautical miles [nmi_i].
		///
		/// Temperature conversions between degrees Celsius ("Cel"), degrees Fahrenheit ("[degF]") and Kelvin ("K") are supported.
		///
		/// Throws a Poco::InvalidArgumentException if the conversion cannot be performed.

	virtual Poco::SharedPtr < IoT::UnitsOfMeasure::Prefix > findPrefix(const std::string& code) const = 0;
		/// Looks up the prefix with the given code.
		///
		/// Returns the Prefix, or a null pointer if not found.

	virtual Poco::SharedPtr < IoT::UnitsOfMeasure::Unit > findUnit(const std::string& code) const = 0;
		/// Looks up the unit with the given (non-prefixed) code.
		///
		/// Returns the Unit, or a null pointer if not found.

	virtual std::string format(const std::string& prefixedCode) const = 0;
		/// Looks up the given unit code with optional prefix (e.g., "cm")
		/// and returns the "printable" string.
		///
		/// If not found, simply returns prefixedCode.

	bool isA(const std::type_info& otherType) const;
		/// Returns true if the class is a subclass of the class given by otherType.

	static const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId();
		/// Returns the TypeId of the class.

	virtual IoT::UnitsOfMeasure::PrefixedUnit resolve(const std::string& prefixedCode) const = 0;
		/// Looks up the given unit code with optional prefix (e.g., "cm")
		/// and returns a PrefixUnit structure containing the (optional) prefix
		/// and unit information.
		///
		/// Throws a Poco::NotFoundException if no matching unit is found.

	const std::type_info& type() const;
		/// Returns the type information for the object's class.

};


} // namespace UnitsOfMeasure
} // namespace IoT


#endif // IoT_UnitsOfMeasure_IUnitsOfMeasureService_INCLUDED

