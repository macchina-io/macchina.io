//
// UnitsOfMeasureServiceRemoteObject.h
//
// Library: IoT/UnitsOfMeasure
// Package: Generated
// Module:  UnitsOfMeasureServiceRemoteObject
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2018, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_UnitsOfMeasure_UnitsOfMeasureServiceRemoteObject_INCLUDED
#define IoT_UnitsOfMeasure_UnitsOfMeasureServiceRemoteObject_INCLUDED


#include "IoT/UnitsOfMeasure/IUnitsOfMeasureService.h"
#include "Poco/RemotingNG/Identifiable.h"
#include "Poco/RemotingNG/RemoteObject.h"
#include "Poco/SharedPtr.h"


namespace IoT {
namespace UnitsOfMeasure {


class UnitsOfMeasureServiceRemoteObject: public IoT::UnitsOfMeasure::IUnitsOfMeasureService, public Poco::RemotingNG::RemoteObject
	/// The UnitsOfMeasureService service is mainly used to map
	/// [[http://unitsofmeasure.org/ucum.html Unified Code for Units of Measure]] (UCUM),
	/// codes, such as used with the IoT::Devices::Sensor interface, to display/print units.
	///
	/// It provides a programmatic interface to the
	/// [[http://unitsofmeasure.org/ucum-essence.xml UCUM-Essence XML file]]
	/// containing unit definitions.
{
public:
	typedef Poco::AutoPtr<UnitsOfMeasureServiceRemoteObject> Ptr;

	UnitsOfMeasureServiceRemoteObject(const Poco::RemotingNG::Identifiable::ObjectId& oid, Poco::SharedPtr<IoT::UnitsOfMeasure::UnitsOfMeasureService> pServiceObject);
		/// Creates a UnitsOfMeasureServiceRemoteObject.

	virtual ~UnitsOfMeasureServiceRemoteObject();
		/// Destroys the UnitsOfMeasureServiceRemoteObject.

	IoT::UnitsOfMeasure::CanonicalValue canonicalize(double value, const std::string& prefixedCode) const;
		/// Removes the prefix from the code and scales the value accordingly.

	virtual double convert(double value, const std::string& fromPrefixedCode, const std::string& toPrefixedCode) const;
		/// Attempts to convert the value from one unit (given in fromPrefixedCode) to a different one
		/// (given in toPrefixedCode). Conversion only works if both units share the same base unit,
		/// which must be atomic. Unfortunately, this means that conversion only works for
		/// a small set of unit pairs, e.g. from km to nautical miles [nmi_i].
		///
		/// Temperature conversions between degrees Celsius ("Cel"), degrees Fahrenheit ("[degF]") and Kelvin ("K") are supported.
		///
		/// Throws a Poco::InvalidArgumentException if the conversion cannot be performed.

	Poco::SharedPtr < IoT::UnitsOfMeasure::Prefix > findPrefix(const std::string& code) const;
		/// Looks up the prefix with the given code.
		///
		/// Returns the Prefix, or a null pointer if not found.

	Poco::SharedPtr < IoT::UnitsOfMeasure::Unit > findUnit(const std::string& code) const;
		/// Looks up the unit with the given (non-prefixed) code.
		///
		/// Returns the Unit, or a null pointer if not found.

	virtual std::string format(const std::string& prefixedCode) const;
		/// Looks up the given unit code with optional prefix (e.g., "cm")
		/// and returns the "printable" string.
		///
		/// If not found, simply returns prefixedCode.

	virtual const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId() const;

	IoT::UnitsOfMeasure::PrefixedUnit resolve(const std::string& prefixedCode) const;
		/// Looks up the given unit code with optional prefix (e.g., "cm")
		/// and returns a PrefixUnit structure containing the (optional) prefix
		/// and unit information.
		///
		/// Throws a Poco::NotFoundException if no matching unit is found.

private:
	Poco::SharedPtr<IoT::UnitsOfMeasure::UnitsOfMeasureService> _pServiceObject;
};


inline IoT::UnitsOfMeasure::CanonicalValue UnitsOfMeasureServiceRemoteObject::canonicalize(double value, const std::string& prefixedCode) const
{
	return _pServiceObject->canonicalize(value, prefixedCode);
}


inline double UnitsOfMeasureServiceRemoteObject::convert(double value, const std::string& fromPrefixedCode, const std::string& toPrefixedCode) const
{
	return _pServiceObject->convert(value, fromPrefixedCode, toPrefixedCode);
}


inline Poco::SharedPtr < IoT::UnitsOfMeasure::Prefix > UnitsOfMeasureServiceRemoteObject::findPrefix(const std::string& code) const
{
	return _pServiceObject->findPrefix(code);
}


inline Poco::SharedPtr < IoT::UnitsOfMeasure::Unit > UnitsOfMeasureServiceRemoteObject::findUnit(const std::string& code) const
{
	return _pServiceObject->findUnit(code);
}


inline std::string UnitsOfMeasureServiceRemoteObject::format(const std::string& prefixedCode) const
{
	return _pServiceObject->format(prefixedCode);
}


inline const Poco::RemotingNG::Identifiable::TypeId& UnitsOfMeasureServiceRemoteObject::remoting__typeId() const
{
	return IUnitsOfMeasureService::remoting__typeId();
}


inline IoT::UnitsOfMeasure::PrefixedUnit UnitsOfMeasureServiceRemoteObject::resolve(const std::string& prefixedCode) const
{
	return _pServiceObject->resolve(prefixedCode);
}


} // namespace UnitsOfMeasure
} // namespace IoT


#endif // IoT_UnitsOfMeasure_UnitsOfMeasureServiceRemoteObject_INCLUDED

