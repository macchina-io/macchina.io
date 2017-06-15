//
// Types.h
//
// $Id$
//
// Library: OPC
// Package: OPC
// Module:  Types
//
// Definitions of the OPC standard types classes as specified in
// in OPC UA Part 3, 8. Standard Data Types.
//
// Copyright (c) 2010-2015, Günter Obiltschnig.
//
// SPDX-License-Identifier:	BSL-1.0
//


#ifndef IoT_OPC_Types_INCLUDED
#define IoT_OPC_Types_INCLUDED


#include "IoT/OPC/OPC.h"
#include "Poco/Types.h"
#include "Poco/UUID.h"
#include "Poco/StringTokenizer.h"
#include "Poco/Dynamic/VarHolder.h"
#include "open62541.h"
#include <vector>
#include <cstring>


namespace IoT {
namespace OPC {


extern const Poco::UInt16 OPC_STANDARD_PORT;

typedef UA_StatusCode StatusCode;
	/// A numeric identifier for an error or condition that is associated with a value
	/// or an operation.

typedef std::string LocaleID;
	/// This Simple DataType is specified as a string that is composed of a language component
	/// and a country/region component as specified by IETF RFC 3066. The <country/region>
	/// component is always preceded by a hyphen. The format of the LocaleId string is shown
	/// below:
	///           <language>[-<country/region>], where 
	///                 <language> is the two letter ISO 639 code for a language, 
	///                 <country/region> is the two letter ISO 3166 code for the country/region.
	///
	/// The rules for constructing LocaleIds defined by IETF RFC 3066 are restricted as follows:
	///
	///   - only zero or one <country/region> component can follow the <language> component;
	///   - “-CHS” and “-CHT” three-letter <country/region> codes for “Simplified” and “Traditional” Chinese locales;
	///   - use of other <country/region> codes as deemed necessary by the Client or the Server is allowed.

typedef bool Boolean;
	/// This Built-in DataType defines a value that is either TRUE or FALSE.

typedef unsigned char Byte;
	/// This Built-in DataType defines a value in the range of 0 to 255.

typedef UA_String String;
typedef UA_ByteString ByteString;


typedef double Double;
	/// This Built-in DataType defines a value that adheres to the IEEE 754-1985 double precision data type definition.

typedef double Duration;
	/// This Simple DataType is a Double that defines an interval of time in milliseconds (fractions can be used to
	/// define sub-millisecond values). Negative values are generally invalid but may have special meanings where
	/// the Duration is used.

typedef float Float;
	/// This Built-in DataType defines a value that adheres to the IEEE 754-1985 single precision data type definition.

typedef char SByte;
	/// This Built-in DataType defines a value that is a signed integer between −128 and 127 inclusive.

typedef ByteString Image;
	/// This abstract DataType defines a ByteString representing an image.

typedef ByteString ImageBMP;
	/// This abstract DataType defines a ByteString representing an image in BMP format.

typedef ByteString ImageGIF;
	/// This abstract DataType defines a ByteString representing an image in GIF format.

typedef ByteString ImageJPG;
	/// This abstract DataType defines a ByteString representing an image in JPG format.

typedef ByteString ImagePNG;
	/// This abstract DataType defines a ByteString representing an image in PNG format.

typedef UA_Int64 Integer;

typedef UA_Int16 Int16;
	/// This Built-in DataType defines a value that is a signed integer between −32,768 and 32,767 inclusive.

typedef UA_Int32 Int32;
	/// This Built-in DataType defines a value that is a signed integer between −2,147,483,648 and 2,147,483,647
	/// inclusive.

typedef UA_Int64 Int64;
	/// This Built-in DataType defines a value that is a signed integer between −9,223,372,036,854,775,808 and
	/// 9,223,372,036,854,775,807 inclusive.

typedef double Number;
	/// This abstract DataType defines a number.

typedef UA_UInt64 UInteger;
	/// This abstract DataType defines an unsigned integer

typedef UA_UInt16 UInt16;
	/// This Built-in DataType defines a value that is an unsigned integer between 0 and 65,535 inclusive.

typedef UA_UInt32 UInt32;
/// This Built-in DataType defines a value that is an unsigned integer between 0 and 4,294,967,295 inclusive.

typedef UA_UInt16 UInt16;
	/// This Built-in DataType defines a value that is an unsigned integer between 0 and 18 446,744,073,709,551,615 inclusive.

typedef ByteString AudioData;
	/// This abstract DataType defines a ByteString representing audio data. The audio stored in the ByteString could be
	/// formats like Wav or MP3 or any number of other audio formats. These formats are self-describing as part of the
	/// ByteString and are not specified in this specification.


class OPC_API NodeID
	/// This class represents an OPC Node identifier.
{
public:
	typedef std::vector<UA_Byte> ByteStringType;
	typedef UA_NodeId Type;
	typedef UA_NodeIdType IDType;

	NodeID();
		/// Creates a null NodeID.

	NodeID(int nsIndex, UInt32 id);
		/// Creates a NodeID of numeric type.

	NodeID(int nsIndex, const std::string& id);
		/// Creates a NodeID of string type.

	NodeID(int nsIndex, const Poco::UUID& id);
		/// Creates a NodeID of string type.

	NodeID(int nsIndex, const ByteStringType& id);
		/// Creates a NodeID of string type.

	NodeID(const NodeID& other);
		/// Copy constructs the nodeID.

	~NodeID();
		/// Destroys the NodeID.

	NodeID& operator = (const NodeID& uuid);
		/// Assignment operator.

	Boolean operator == (const NodeID& other) const;
		/// Equality operator.

	Boolean operator != (const NodeID& other) const;
		/// Equality operator.

	bool isNull() const;
		/// Returns true if Node ID is null.

	Poco::UInt16 getNSIndex() const;
		/// Returns the namespace index for this node ID.

	IDType getIDType() const;
		/// Returns the node ID type.

	Type getType() const;
		/// Returns the node type.

	bool isNumeric() const;
		/// Returns true if the value is numeric.

	bool isString() const;
		/// Returns true if the value is string.

	bool isByteString() const;
		/// Returns true if the value is byteString.

	bool isGuid() const;
		/// Returns true if the value is guid.

	UInt32 getNumeric() const;
		/// Returns the node ID numeric value.
		/// Throws if node ID is null or not numeric.

	std::string getString() const;
		/// Returns the node ID string value.
		/// Throws if node ID is null or not string.

	const ByteStringType& getByteString() const;
		/// Returns the node ID byteString value.
		/// Throws if node ID is null or not byteString.

	Poco::UUID getGuid() const;
		/// Returns the node ID guid value.
		/// Throws if node ID is null or not guid.

	static UA_Guid toUA(const Poco::UUID& uuid);
	static Poco::UUID toPoco(const UA_Guid& guid);

private:
	NodeID(const Type& other);
		/// Constructs the nodeID.

	void throwIfNull() const;
	void throwIf(bool cond) const;
	void assign(const NodeID& other);
	void assignNumeric(int nsIndex, UInt32 value);
	void assignString(int nsIndex, std::size_t length, const UA_Byte* data, UA_NodeIdType type);
	void assignGuid(int nsIndex, const UA_Guid& value);

	Type           _nodeId;
	ByteStringType _buf;
};


class OPC_API DataTypeMember
{
public:
	typedef UA_DataTypeMember Type;

	DataTypeMember(UInt16 index = 0,
		const std::string& name = "",
		Byte padding = 0,
		Boolean nsZero = true,
		Boolean isArray = false);
		/// Constructs the DataTypeMember.

	~DataTypeMember();
		/// Destroys the DataTypeMember.

	UInt16 getIndex() const;
		/// Returns the index of the member in the array of data types.

	void setIndex(UInt16 idx);
		/// Sets the index of the member in the array of data types.

	const std::string& getName() const;
		/// Returns the name of this DataTypeMember.

	void setName(const std::string& name);
		/// Sets the name of this ataTypeMember.

	Byte getPadding() const;
		/// Returns the size of the padding before this member element.
		/// For arrays this is the padding before the size_t lenght member.
		/// (There is no padding between size_t and the following ptr.

	void setPadding(Byte padding);
		/// Sets the size of the padding before this member element.

	Boolean getNSZero() const;
		/// Returns true if the type of the member is defined in namespace zero.
		/// In this implementation, types from custom namespace may contain
		/// members from the same namespace or namespace zero only.

	void setNSZero(Boolean nsZero);
		/// Sets te flag indicating whether the type of the member is defined in namespace zero.

	Boolean getIsArray() const;
		/// Returns true if the member is an array.

	void setIsArray(Boolean isArray);
		/// Sets te flag indicating whether the member is an array.

	const Type& get() const;
		/// Returns the underlying data structure.
		///
		/// Important:
		/// The `memberName` struct member points to a
		/// char array that has the lifespan of this object.

	void set(const Type& type);
		/// Sets the entire underlying data structure.
		/// The `memberName` struct member, if present and non-empty,
		/// is assigned to the internal std::string object.

private:
	Type        _type;
	std::string _name;
};


typedef std::string DateString;
	/// This Simple DataType defines a value which is a day in the Gregorian calendar in string. Lexical representation
	/// of the string shall conform to calendar date defined in ISO 8601-2000.
	///
	///  NOTE: According to ISO 8601-2000, ‘calendar date representations are in the form [YYYY-MM-DD].
	///        [YYYY] indicates a four-digit year, 0000 through 9999. [MM] indicates a two-digit month of the year,
	///               01 through 12.
	///        [DD] indicates a two-digit day of that month, 01 through 31. For example, "the 5th of April 1981"
	///             may be represented as either "1981-04-05" in the extended format or "19810405" in the basic format.’
	///
	///  NOTE: ISO 8601-2000 also allows for calendar dates to be written with reduced precision. For example, one may
	///        write "1981-04" to mean "1981 April", and one may simply write "1981" to refer to that year or "19" to
	///        refer to the century from 1900 to 1999 inclusive.
	///
	///  NOTE: Although ISO 8601-2000 allows both the YYYY-MM-DD and YYYYMMDD formats for complete calendar date
	///        representations, if the day [DD] is omitted then only the YYYY-MM format is allowed. By disallowing
	///        dates of the form YYYYMM, ISO 8601-2000 avoids confusion with the truncated representation YYMMDD
	///        (still often used).


typedef std::string DecimalString;
	/// This Simple DataType defines a value that represents a decimal number as a string. Lexical representation of the
	/// string shall conform to decimal type defined in W3C XML Schema Definition Language (XSD) 1.1 Part 2: DataTypes.
	/// The DecimalString is a numeric string with an optional sign and decimal point.


typedef std::string DurationString;
	/// This Simple DataType defines a value that represents a duration of time as a string. It shall conform to
	/// duration as defined in ISO 8601-2000.
	///
	/// NOTE: According to ISO 8601—2000 ‘Durations are represented by the format P[n]Y[n]M[n]DT[n]H[n]M[n]S or P[n]W
	///       as shown to the right. In these representations, the [n] is replaced by the value for each of the date and
	///       time elements that follow the [n]. Leading zeros are not required, but the maximum number of digits for
	///       each element should be agreed to by the communicating parties. The capital letters P, Y, M, W, D, T, H, M,
	///       and S are designators for each of the date and time elements and are not replaced.
	///
	///       P is the duration designator ("period") placed at the start of the duration representation.
	///       Y is the year designator that follows the value for the number of years.
	///       M is the month designator that follows the value for the number of months.
	///       W is the week designator that follows the value for the number of weeks.
	///       D is the day designator that follows the value for the number of days.
	///       T is the time designator that precedes the time components of the representation.
	///       H is the hour designator that follows the value for the number of hours.
	///       M is the minute designator that follows the value for the number of minutes.
	///       S is the second designator that follows the value for the number of seconds.
	///
	///       For example, "P3Y6M4DT12H30M5S" represents a duration of "three years, six months, four days,
	///       twelve hours, thirty minutes, and five seconds". Date and time elements including their designator may be
	///       omitted if their value is zero, and lower order elements may also be omitted for reduced precision.
	///       For example, "P23DT23H" and "P4Y" are both acceptable duration representations.’


typedef std::string NormalizedString;
	/// This Simple DataType defines a string value that shall be normalized according to Unicode Annex 15,
	/// Version 7.0.0, Normalization Form C.
	///
	/// NOTE: Some Unicode characters have multiple equivalent binary representations consisting of sets of combining
	/// and/or composite Unicode characters. Unicode defines a process called normalization that returns one binary
	/// representation when given any of the equivalent binary representations of a character.
	/// The Win32 and the .NET Framework currently support normalization forms C, D, KC, and KD, as defined in Annex 15
	/// of Unicode. NormalizedString uses Normalization Form C for all content, because this form avoids potential
	/// interoperability problems caused by the use of canonically equivalent, yet different, character sequences in
	/// document formats.


typedef std::string TimeString;
	/// This Simple DataType defines a value that represents a time as a string. It shall conform to time of day as
	/// defined in ISO 8601-2000.
	///   NOTE: ISO 8601-2000 uses the 24-hour clock system. The basic format is [hh][mm][ss] and the extended format is
	///        [hh]:[mm]:[ss].
	///
	///        [hh] refers to a zero-padded hour between 00 and 24 (where 24 is only used to notate midnight at the end
	///             of a calendar day).
	///        [mm] refers to a zero-padded minute between 00 and 59.
	///        [ss] refers to a zero-padded second between 00 and 60 (where 60 is used to notate an added leap second).
	///             So a time might appear as either "134730" in the basic format or "13:47:30" in the extended format.
	///             It is also acceptable to omit lower order time elements for reduced accuracy: [hh]:[mm], [hh][mm]
	///             and [hh] are all used.
	///
	///        Midnight is a special case and can be referred to as both "00:00" and "24:00". The notation "00:00" is
	///        used at the beginning of a calendar day and is the more frequently used. At the end of a day use "24:00"


struct TimeZoneDataType
	/// This Structured DataType defines the local time that may take daylight saving time into account.
{
	Poco::UInt16 _offset;
	bool         _daylightSavingInOffset;
};


//
// inlines
//

inline std::string getError(UInt32 val)
{
	return std::string(UA_StatusCode_name(val)) + ": " + UA_StatusCode_explanation(val);
}


inline int getUAType(const bool&)
{
	return UA_TYPES_BOOLEAN;
}


inline int getUAType(const unsigned char&)
{
	return UA_TYPES_SBYTE;
}


inline int getUAType(const char&)
{
	return UA_TYPES_BYTE;
}


inline int getUAType(const Poco::Int16&)
{
	return UA_TYPES_INT16;
}


inline int getUAType(const Poco::UInt16&)
{
	return UA_TYPES_UINT16;
}


inline int getUAType(const Poco::Int32&)
{
	return UA_TYPES_INT32;
}


inline int getUAType(const Poco::UInt32&)
{
	return UA_TYPES_UINT32;
}


inline int getUAType(const Poco::Int64&)
{
	return UA_TYPES_INT64;
}


inline int getUAType(const Poco::UInt64&)
{
	return UA_TYPES_UINT64;
}


inline int getUAType(const float&)
{
	return UA_TYPES_FLOAT;
}


inline int getUAType(const double&)
{
	return UA_TYPES_DOUBLE;
}


inline int getUAType(const std::string&)
{
	return UA_TYPES_STRING;
}


inline int getUAType(const Poco::DateTime&)
{
	return UA_TYPES_DATETIME;
}


} } // namespace IoT::OPC


#endif // IoT_OPC_Types_INCLUDED
