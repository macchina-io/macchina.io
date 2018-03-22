//
// UnitsOfMeasureServiceImpl.h
//
// Library: IoT/UnitsOfMeasure
// Package: UnitsOfMeasure
// Module:  UnitsOfMeasureServiceImpl
//
// Definition of the UnitsOfMeasureServiceImpl class.
//
// Copyright (c) 2018, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_UnitsOfMeasure_UnitsOfMeasureServiceImpl_INCLUDED
#define IoT_UnitsOfMeasure_UnitsOfMeasureServiceImpl_INCLUDED


#include "IoT/UnitsOfMeasure/UnitsOfMeasureService.h"
#include <map>


namespace IoT {
namespace UnitsOfMeasure {


class IoTUnitsOfMeasure_API UnitsOfMeasureServiceImpl: public UnitsOfMeasureService
	/// Implementation of UnitsOfMeasureService.
{
public:
	typedef Poco::SharedPtr<UnitsOfMeasureServiceImpl> Ptr;
	typedef std::map<std::string, Prefix::Ptr> PrefixMap;
	typedef std::map<std::string, Unit::Ptr> UnitMap;

	UnitsOfMeasureServiceImpl();
		/// Creates the UnitsOfMeasureService.

	virtual ~UnitsOfMeasureServiceImpl();
		/// Destroys the UnitsOfMeasureService.

	void addPrefix(const Prefix& prefix);
		/// Adds a Prefix.

	void addUnit(const Unit& unit);
		/// Adds a Unit.

	// UnitsOfMeasureService
	Prefix::Ptr findPrefix(const std::string& code) const;
	Unit::Ptr findUnit(const std::string& code) const;
	PrefixedUnit resolve(const std::string& code) const;
	std::string format(const std::string& code) const;
	CanonicalValue canonicalize(double value, const std::string& prefixedCode) const;
	double convert(double value, const std::string& fromPrefixedCode, const std::string& toPrefixedCode) const;

protected:
	CanonicalValue convertToBase(double value, const std::string& code) const;
	double convertFromBase(double value, const std::string& code, const std::string& base) const;
	PrefixedUnit tryResolve(const std::string& code) const;
	CanonicalValue reverseCanonicalize(double value, const std::string& prefixedCode) const;

private:
	PrefixMap _prefixes;
	UnitMap _units;
};


} } // namespace IoT::UnitsOfMeasure


#endif // IoT_UnitsOfMeasure_UnitsOfMeasureServiceImpl_INCLUDED
