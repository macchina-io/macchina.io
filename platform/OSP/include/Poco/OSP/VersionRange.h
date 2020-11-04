//
// VersionRange.h
//
// Library: OSP
// Package: Util
// Module:  VersionRange
//
// Definition of the VersionRange class.
//
// Copyright (c) 2007-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef OSP_VersionRange_INCLUDED
#define OSP_VersionRange_INCLUDED


#include "Poco/OSP/OSP.h"
#include "Poco/OSP/Version.h"


namespace Poco {
namespace OSP {


class OSP_API VersionRange
	/// This utility class represents a range of versions.
	///
	/// A version range can be an open, half closed or
	/// closed interval.
{
public:
	VersionRange();
		/// Creates an empty VersionRange.

	explicit VersionRange(const Version& ver);
		/// Creates a VersionRange matching only a specific Version.

	VersionRange(const Version& lower, bool includeLower, const Version& upper, bool includeUpper);
		/// Creates the VersionRange.

	VersionRange(const VersionRange& range);
		/// Creates a VersionRange by copying another one.

	~VersionRange();
		/// Destroys the VersionRange.

	VersionRange& operator = (const VersionRange& range);
		/// Assigns another VersionRange.

	VersionRange& operator = (const Version& ver);
		/// Assigns a single Version.

	void swap(VersionRange& range);
		/// Swaps the VersionRange with another one.

	const Version& lowerBound() const;
		/// Returns the lower bound of the interval.

	const Version& upperBound() const;
		/// Returns the upper bound of the interval.

	bool includeLower() const;
		/// Returns true iff the lower bound lies within the interval.

	bool includeUpper() const;
		/// Returns true iff the upper bound lies within the interval.

	bool isInRange(const Version& version) const;
		/// Returns true iff the version lies within the range.

	bool isEmpty() const;
		/// Returns true iff the version range is empty.

	std::string toString() const;
		/// Returns a string representation of the version range.

private:
	Version _lower;
	Version _upper;
	bool    _includeLower;
	bool    _includeUpper;
};


//
// inlines
//
inline const Version& VersionRange::lowerBound() const
{
	return _lower;
}


inline const Version& VersionRange::upperBound() const
{
	return _upper;
}


inline bool VersionRange::includeLower() const
{
	return _includeLower;
}


inline bool VersionRange::includeUpper() const
{
	return _includeUpper;
}


inline void swap(VersionRange& vr1, VersionRange& vr2)
{
	vr1.swap(vr2);
}


} } // namespace Poco::OSP


#endif // OSP_VersionRange_INCLUDED
