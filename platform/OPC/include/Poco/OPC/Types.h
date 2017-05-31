//
// Types.h
//
// $Id$
//
// Library: OPC
// Package: OPC
// Module:  Node
//
// Definitions of the OPC standard types classes as specified in
// in OPC UA Part 3, 8. Standard Data Types.
//
// Copyright (c) 2010-2015, Günter Obiltschnig.
//
// SPDX-License-Identifier:	BSL-1.0
//


#ifndef OPC_Node_INCLUDED
#define OPC_Node_INCLUDED


#include "Poco/OPC/OPC.h"
#include "Poco/DateTime.h"
#include "Poco/Types.h"
#include "Poco/UUID.h"
#include "Poco/StringTokenizer.h"
#include "Poco/Dynamic/VarHolder.h"
#include <vector>
#include <cstring>


namespace Poco {
namespace OPC {
namespace open62541 {


#include "open62541.h"


}

inline std::string getError(UInt32 val)
{
	return std::string(open62541::UA_StatusCode_name(val)) + ": " + open62541::UA_StatusCode_explanation(val);
}

extern const UInt16 OPC_STANDARD_PORT;

typedef open62541::UA_StatusCode StatusCode;
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

typedef open62541::UA_String String;
typedef open62541::UA_ByteString ByteString;

#if 0
typedef struct {
    size_t length; /* The length of the string */
    UA_Byte *data; /* The content (not null-terminated) */
} UA_String;
#endif


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


inline int getUAType(const Int16&)
{
	return UA_TYPES_INT16;
}


inline int getUAType(const UInt16&)
{
	return UA_TYPES_UINT16;
}


inline int getUAType(const Int32&)
{
	return UA_TYPES_INT32;
}


inline int getUAType(const UInt32&)
{
	return UA_TYPES_UINT32;
}


inline int getUAType(const Int64&)
{
	return UA_TYPES_INT64;
}


inline int getUAType(const UInt64&)
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


class OPC_API UAString
	/// A string conversion utility class with value semantics.
	/// It can be constructed from std::string and provides
	/// implicit conversion to/from open62541::UA_String.
{
public:
	UAString();
		/// Creates the UAString.

	UAString(const UAString& from);
		/// Copy-constructs the UAString.

	UAString(const std::string& from);
		/// Creates the UAString from std::string.

	~UAString();
		/// Destroys the UAString.

	UAString& operator = (const std::string& from);
		/// Asignment operator.

	UAString& operator = (const UAString& from);
		/// Asignment operator.

	operator const String&();
		/// Cast operator.

	operator std::string();
		/// Cast operator.

	std::size_t length() const
	{
		return _to.length;
	}

	const unsigned char* data() const
	{
		return _to.data;
	}

private:
	void allocate(const unsigned char* data, std::size_t length);
	void release();

	String _to;
};

class OPC_API STDString
	/// A string conversion utility class with value semantics.
	/// It can be constructed from open62541::UA_String and provides
	/// implicit conversion to/from std::string.
{
public:
	STDString(const String& from);
		/// Creates the STDString.

	STDString(const STDString& from);
		/// Copy-constructs the STDString.

	~STDString();
		/// Destroys the STDString.

	STDString& operator = (const STDString& from);
		/// Asignment operator.

	operator const std::string&();
		/// Cast operator.

	operator const String&();
		/// Cast operator.

	std::size_t length() const
	{
		return _toUA.length;
	}

	const unsigned char* data() const
	{
		return _toUA.data;
	}

private:
	void assign(const char* data, std::size_t length);

	std::string _to;
	String      _toUA;
};


class UAVariant
{
public:
	UAVariant(): _pVariant(open62541::UA_Variant_new())
	{
		poco_check_ptr(_pVariant);
	}

	~UAVariant()
	{
		UA_Variant_delete(_pVariant);
	}

	operator open62541::UA_Variant*()
	{
		return _pVariant;
	}

	operator open62541::UA_Variant&()
	{
		poco_check_ptr(_pVariant);
		return *_pVariant;
	}

private:
	UAVariant(const UAVariant&);
	UAVariant& operator = (const UAVariant&);

	open62541::UA_Variant* _pVariant;
};


class DateTime: public Poco::DateTime
	/// This Built-in DataType defines an instance in time.
	/// It is implemented as an extension of Poco:DateTime, with addition 
	/// of nanoseconds.
{
public:
	DateTime(): Poco::DateTime(), _nanosecond(0)
		/// Creates the DateTime.
	{
	}

	DateTime(int year, int month, int day,
		int hour = 0, int minute = 0, int second = 0, 
		int millisecond = 0, int microsecond = 0, int nanosecond = 0):
			Poco::DateTime(year, month, day, hour, minute, second,
						   millisecond, microsecond), _nanosecond(nanosecond)
		/// Creates the DateTime.
	{
	}

	DateTime(UInt64 ts)
		/// Creates the DateTime.
	{
		open62541::UA_DateTimeStruct uDTS = open62541::UA_DateTime_toStruct(ts);
		assign(uDTS.year, uDTS.month, uDTS.day, uDTS.hour, uDTS.min, uDTS.sec, uDTS.milliSec, uDTS.microSec);
		_nanosecond = uDTS.nanoSec;
	}

	DateTime(open62541::UA_DateTimeStruct uDTS)
		/// Creates the DateTime.
	{
		assign(uDTS.year, uDTS.month, uDTS.day, uDTS.hour, uDTS.min, uDTS.sec, uDTS.milliSec, uDTS.microSec);
		_nanosecond = uDTS.nanoSec;
	}

	DateTime(const std::string& str)
	{
		*this = fromString(str);
	}

	DateTime(const Poco::DateTime& dt): Poco::DateTime(dt), _nanosecond(0)
		/// Copy-constructs the DateTime.
	{
	}

	~DateTime()
		/// Destroys the DateTime.
	{
	}

	DateTime& operator = (const DateTime& dt)
		/// Assignment operator.
	{
		if(&dt != this)
		{
			assign(dt.year(), dt.month(), dt.day(), dt.hour(), dt.minute(), dt.second(), dt.millisecond(), dt.microsecond());
			_nanosecond = dt._nanosecond;
		}
		return *this;
	}

	DateTime& operator = (UInt64 ts)
		/// Assignment operator.
	{
		open62541::UA_DateTimeStruct uDTS = open62541::UA_DateTime_toStruct(ts);
		assign(uDTS.year, uDTS.month, uDTS.day, uDTS.hour, uDTS.min, uDTS.sec, uDTS.milliSec, uDTS.microSec);
		_nanosecond = uDTS.nanoSec;
		return *this;
	}

	DateTime& operator = (const Poco::DateTime& dt)
		/// Assignment operator.
	{
		assign(dt.year(), dt.month(), dt.day(), dt.hour(), dt.minute(), dt.second(), dt.millisecond(), dt.microsecond());
		_nanosecond = 0;
		return *this;
	}

	DateTime& operator = (const std::string& str)
		/// Assignment operator.
	{
		*this = fromString(str);
		return *this;
	}

	int nanosecond() const
		/// Returns the nanosecond (0 to 999)
	{
		return _nanosecond;
	}

	static DateTime fromString(const std::string& from)
	{
		StringTokenizer st(from, "/ :.", StringTokenizer::TOK_TRIM | StringTokenizer::TOK_IGNORE_EMPTY);
		if(st.count() != 9)
		{
			throw Poco::InvalidArgumentException("Invalid DateTime format (expected MM/DD/YYYY HH24:MI:SS.mmm.uuu.nnn)");
		}
		return DateTime(NumberParser::parse(st[2]),
			NumberParser::parse(st[0]),
			NumberParser::parse(st[1]),
			NumberParser::parse(st[3]),
			NumberParser::parse(st[4]),
			NumberParser::parse(st[5]),
			NumberParser::parse(st[6]),
			NumberParser::parse(st[7]),
			NumberParser::parse(st[8]));
	}

	std::string toString() const
		/// Returns the DateTime as string.
	{
		std::vector<char> str(32);
		printNumber(month(), &str[0], 2);
		str[2] = '/';
		printNumber(day(), &str[3], 2);
		str[5] = '/';
		printNumber(year(), &str[6], 4);
		str[10] = ' ';
		printNumber(hour(), &str[11], 2);
		str[13] = ':';
		printNumber(minute(), &str[14], 2);
		str[16] = ':';
		printNumber(second(), &str[17], 2);
		str[19] = '.';
		printNumber(millisecond(), &str[20], 3);
		str[23] = '.';
		printNumber(microsecond(), &str[24], 3);
		str[27] = '.';
		printNumber(_nanosecond, &str[28], 3);
		return std::string(&str[0]);
	}

	static Int64 now()
	{
		return open62541::UA_DateTime_now();
	}

private:
	static void printNumber(UInt16 n, char* pos, size_t digits)
	{
		for(size_t i = digits; i > 0; --i)
		{
			pos[i-1] = ((n % 10) + '0');
			n = n / 10;
		}
	}

	UInt16 _nanosecond;
};


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

typedef open62541::UA_Int64 Integer;

typedef open62541::UA_Int16 Int16;
	/// This Built-in DataType defines a value that is a signed integer between −32,768 and 32,767 inclusive.

typedef open62541::UA_Int32 Int32;
	/// This Built-in DataType defines a value that is a signed integer between −2,147,483,648 and 2,147,483,647
	/// inclusive.

typedef open62541::UA_Int64 Int64;
	/// This Built-in DataType defines a value that is a signed integer between −9,223,372,036,854,775,808 and
	/// 9,223,372,036,854,775,807 inclusive.

typedef double Number;
	/// This abstract DataType defines a number.

typedef open62541::UA_UInt64 UInteger;
	/// This abstract DataType defines an unsigned integer

typedef open62541::UA_UInt16 UInt16;
	/// This Built-in DataType defines a value that is an unsigned integer between 0 and 65,535 inclusive.

typedef open62541::UA_UInt32 UInt32;
/// This Built-in DataType defines a value that is an unsigned integer between 0 and 4,294,967,295 inclusive.

typedef open62541::UA_UInt16 UInt16;
	/// This Built-in DataType defines a value that is an unsigned integer between 0 and 18 446,744,073,709,551,615 inclusive.

typedef ByteString AudioData;
	/// This abstract DataType defines a ByteString representing audio data. The audio stored in the ByteString could be
	/// formats like Wav or MP3 or any number of other audio formats. These formats are self-describing as part of the
	/// ByteString and are not specified in this specification.

#if 0
 * enum UA_NodeIdType {
    UA_NODEIDTYPE_NUMERIC    = 0, /* In the binary encoding, this can also
                                     become 1 or 2 (2byte and 4byte encoding of
                                     small numeric nodeids) */
UA_NODEIDTYPE_STRING     = 3,
		UA_NODEIDTYPE_GUID       = 4,
		UA_NODEIDTYPE_BYTESTRING = 5
};

 * typedef struct {
    UA_UInt16 namespaceIndex;
    enum UA_NodeIdType identifierType;
    union {
        UA_UInt32     numeric;
        UA_String     string;
        UA_Guid       guid;
        UA_ByteString byteString;
    } identifier;
} UA_NodeId;
#endif
class OPC_API NodeID
	/// This class represents an OPC Node identifier.
{
public:
	typedef std::vector<open62541::UA_Byte> ByteStringType;
	typedef open62541::UA_NodeId Type;
	typedef open62541::UA_NodeIdType IDType;

	NodeID();
		/// Creates a null NodeID.

	NodeID(int nsIndex, UInt32 value);
		/// Creates a NodeID of numeric type.

	NodeID(int nsIndex, const std::string& value);
		/// Creates a NodeID of string type.

	NodeID(int nsIndex, const Poco::UUID& value);
		/// Creates a NodeID of string type.

	NodeID(int nsIndex, const ByteStringType& value);
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

	UUID getGuid() const;
		/// Returns the node ID guid value.
		/// Throws if node ID is null or not guid.

	static open62541::UA_Guid toUA(const Poco::UUID& uuid);
	static Poco::UUID toPoco(const open62541::UA_Guid& guid);

private:
	NodeID(const Type& other);
		/// Constructs the nodeID.

	void throwIfNull() const;
	void throwIf(bool cond) const;
	void assign(const NodeID& other);
	void assignNumeric(int nsIndex, UInt32 value);
	void assignString(int nsIndex, std::size_t length, const open62541::UA_Byte* data, open62541::UA_NodeIdType type);
	void assignGuid(int nsIndex, const open62541::UA_Guid& value);

	Type           _nodeId;
	ByteStringType _buf;

	friend class VariableNode;
};

#if 0
/**
 * .. _generic-types:
 *
 * Generic Type Handling
 * ---------------------
 * The builtin types can be combined to data structures. All information about a
 * (structured) data type is stored in a ``UA_DataType``. The array ``UA_TYPES``
 * contains the description of all standard-defined types and is used for
 * handling of generic types. */
typedef struct {
#ifdef UA_ENABLE_TYPENAMES
    const char *memberName;
#endif
    UA_UInt16 memberTypeIndex;    /* Index of the member in the array of data
                                     types */
    UA_Byte   padding;            /* How much padding is there before this
                                     member element? For arrays this is the
                                     padding before the size_t lenght member.
                                     (No padding between size_t and the
                                     following ptr.) */
    UA_Boolean namespaceZero : 1; /* The type of the member is defined in
                                     namespace zero. In this implementation,
                                     types from custom namespace may contain
                                     members from the same namespace or
                                     namespace zero only.*/
    UA_Boolean isArray       : 1; /* The member is an array */
} UA_DataTypeMember;

#endif

class OPC_API DataTypeMember
{
public:
	typedef open62541::UA_DataTypeMember Type;

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

#if 0
struct UA_DataType {
#ifdef UA_ENABLE_TYPENAMES
    const char *typeName;
#endif
    UA_NodeId  typeId;           /* The nodeid of the type */
UA_UInt16  memSize;          /* Size of the struct in memory */
UA_UInt16  typeIndex;        /* Index of the type in the datatypetable */
UA_Byte    membersSize;      /* How many members does the type have? */
UA_Boolean builtin      : 1; /* The type is "builtin" and has dedicated de-
                                    and encoding functions */
UA_Boolean fixedSize    : 1; /* The type (and its members) contains no
                                    pointers */
UA_Boolean overlayable  : 1; /* The type has the identical memory layout in
                                    memory and on the binary stream. */
UA_UInt16  binaryEncodingId; /* NodeId of datatype when encoded as binary */
//UA_UInt16  xmlEncodingId;  /* NodeId of datatype when encoded as XML */
UA_DataTypeMember *members;
};
#endif


class OPC_API DataType
{
public:
	typedef DataTypeMember::Type Member;
	typedef std::vector<Member> Members;
	typedef open62541::UA_DataType Type;

	DataType(): _type()
		/// Constructs the DataType.
	{
	}

	DataType(const std::string& name,
		const NodeID& nodeID,
		UInt16 memSize,
		UInt16 typeIndex,
		const Members& members,
		Boolean builtin,
		Boolean fixedSize,
		Boolean overlayable,
		UInt16 binaryEncodingId
		//UA_UInt16  xmlEncodingId
		): _name(name), _members(members), _nodeID(nodeID)
		/// Constructs the DataType.
	{
		_type.typeName = _name.c_str();
		_type.typeId = _nodeID.getType();
		_type.memSize = memSize;
		_type.typeIndex = typeIndex;
		_type.membersSize = _members.size();
		_type.builtin = builtin;
		_type.fixedSize = fixedSize;
		_type.overlayable = overlayable;
		_type.binaryEncodingId = binaryEncodingId;
		_type.members = &_members[0];
	}

	~DataType()
		/// Destroys the DataType.
	{
	}

	const std::string& getName() const
	{
		return _name;
	}

	void setName(const std::string& name)
	{
		_name = name;
		_type.typeName = _name.c_str();
	}

	const NodeID& getTypeID() const
	{
		return _nodeID;
	}

	void setTypeID(const NodeID& nodeID)
	{
		_nodeID = nodeID;
	}

	UInt16 getTypeIndex() const
	{
		return _type.typeIndex;
	}

	void setTypeIndex(UInt16 idx)
	{
		_type.typeIndex = idx;
	}

	const Type& getType() const
	{
		return _type;
	}
/*
	void setType(const Type& type)
	{
		_type.typeId = type;
	}
*/
private:
	Type        _type;
	std::string _name;
	Members     _members;
	NodeID      _nodeID;

	friend class Variant;
};


#if 0
typedef enum {
        UA_VARIANT_DATA,          /* The data has the same lifecycle as the
                                     variant */
        UA_VARIANT_DATA_NODELETE, /* The data is "borrowed" by the variant and
                                     shall not be deleted at the end of the
                                     variant's lifecycle. */
} UA_VariantStorageType;

typedef struct {
    const UA_DataType *type;      /* The data type description */
    UA_VariantStorageType storageType;
    size_t arrayLength;           /* The number of elements in the data array */
    void *data;                   /* Points to the scalar or array data */
    size_t arrayDimensionsSize;   /* The number of dimensions */
    UA_UInt32 *arrayDimensions;   /* The length of each dimension */
} UA_Variant;
#endif

class OPC_API Variant
{
public:
	typedef open62541::UA_VariantStorageType StorageType;
	typedef std::vector<UInt32> DimType;

	Variant(): _val()
		/// Constructs an empty Variant.
	{
	}

	Variant(void* data,
		const DataType& dataType,
		StorageType storeType = open62541::UA_VARIANT_DATA,
		std::size_t arrLen = 0,
		const DimType& arrDim = DimType()): _dataType(dataType/*.getType()*/)
		/// Constructs the Variant.
	{
		_val.storageType = storeType;
		_val.arrayLength = arrLen;
		if(arrDim.size())
		{
			_val.arrayDimensionsSize = arrDim.size();
			_val.arrayDimensions = const_cast<UInt32*>(&arrDim[0]);
		}
		else
		{
			_val.arrayDimensionsSize = 0;
			_val.arrayDimensions = 0;
		}
		_val.data = data;
	}

	~Variant()
		/// Destroys the Variant.
	{
	}

	bool isNull() const
	{
		return true;//TODO
	}
/*
	const T& getData() const
	{
		return Poco::RefAnyCast<T>(*_data);
	}
*/
private:
	const open62541::UA_Variant& variant() const
	{
		return _val;
	}

	DataType              _dataType;
	open62541::UA_Variant _val;

	friend class DataValue;
};

#if 0

/**
 * .. _datavalue:
 *
 * DataValue
 * ^^^^^^^^^
 * A data value with an associated status code and timestamps. */
typedef struct {
    UA_Boolean    hasValue             : 1;
    UA_Boolean    hasStatus            : 1;
    UA_Boolean    hasSourceTimestamp   : 1;
    UA_Boolean    hasServerTimestamp   : 1;
    UA_Boolean    hasSourcePicoseconds : 1;
    UA_Boolean    hasServerPicoseconds : 1;
    UA_Variant    value;
    UA_StatusCode status;
    UA_DateTime   sourceTimestamp;
    UA_UInt16     sourcePicoseconds;
    UA_DateTime   serverTimestamp;
    UA_UInt16     serverPicoseconds;
} UA_DataValue;
#endif

class OPC_API DataValue
{
public:
	typedef open62541::UA_DataValue Value;

	DataValue()
		/// Constructs an empty DataValue.
	{
	}

	DataValue(void* data,
		const DataType& type,
		Variant::StorageType storeType = open62541::UA_VARIANT_DATA,
		std::size_t arrLen = 0,
		const Variant::DimType& arrDim = Variant::DimType())
		/// Constructs the DataValue.
	{
		_value.hasValue = false;
		_value.hasStatus = false;
		_value.hasSourceTimestamp = false;
		_value.hasServerTimestamp = false;
		_value.hasSourcePicoseconds = false;
		_value.hasServerPicoseconds = false;
		_value.value = Variant(data, type, storeType, arrLen, arrDim).variant();
		_value.status = 0xffffffff;
		_value.sourceTimestamp = 0;
		_value.sourcePicoseconds= 0;
		_value.serverTimestamp = 0;
		_value.serverPicoseconds = 0;
	}

	~DataValue()
		/// Destroys the DataValue.
	{

	}

private:
	//Variant<T> _varValue;
	Value _value;
};

class BaseData
{
public:
	BaseData();
		/// Constructs an empty BaseData.

	~BaseData();
		/// Destroys the BaseData.

private:
};



/*
template <typename T, typename C>
class StringTemplate
	/// This template is basis for the definition of OPC UA ByteString and String.
{
public:
	typedef T Type;

	StringTemplate(const Type& data = Type())
	{
		if(typeid(Type) == typeid(std::string)) purge(data);
	}

	~StringTemplate()
	{
		for(CollectType::iterator it = _collector.begin(), end = _collector.end(); it != end; ++it)
		{
			free(*it);
		}
	}

	operator const Type&() const
	{
		return _data;
	}

private:
	typedef open62541::UA_Byte MemberType;
	typedef std::vector<MemberType*> CollectType;

	operator C() const
	{
		C str;
		str.length = _data.length();
		if(str.length)
		{
			str.data = (open62541::UA_Byte*) std::malloc(str.length, sizeof(open62541::UA_Byte));
			std::memcpy((str.data, &_data[0]));
			_collector.push_back(str.data);
		}
		return str;
	}

	static std::string purge(const std::string& str)
	{
		std::string purged;
		//TODO: purge non-printable chars except spaces
		return purged;
	}

	Type _data;
	CollectType _collector;
};

typedef StringTemplate<std::vector<Byte>, open62541::UA_ByteString> ByteString;
	/// This Built-in DataType defines a value that is a sequence of Byte values.

typedef StringTemplate<std::string, open62541::UA_ByteString> String;
	/// This Built-in DataType defines a Unicode character string that should exclude control characters
	/// that are not whitespaces.
*/

/*
class Guid: public Poco::UUID
	/// This Built-in DataType defines a value that is a 128-bit Globally Unique Identifier.
{
public:
	Guid();
		/// Constructs the Guid.

	explicit Guid(const std::string& uuid);
	/// Parses the UUID from a string.

	explicit Guid(const char* uuid);
	/// Parses the UUID from a string.

	~Guid();
	/// Destroys the Guid.

private:
	operator open62541::UA_Guid() const;
};
*/



class OPC_API Decimal
	/// This Simple DataType defines a high-precision signed decimal number. It consists of an arbitrary precision
	/// integer unscaled value and an integer scale. The scale is the inverse power of ten that is applied to the
	/// unscaled value.
{
public:
	Decimal(Int64 value = 0, UInt64 scale = 1);
		/// Creates Decimal.

	~Decimal();
		/// Destroys Decimal.

	double value() const;
		/// Returns scaled value.

	Int64 getValue() const;
		/// Returns the non-scaled value.

	void setValue(Int64 val);
		/// Sets the non-scaled value.

	Int64 getScale() const;
		/// Returs the scale.

	void setScale(UInt64 scale);
		/// Sets the scale.

private:
	void checkScale(UInt64 val) const;

	Int64 _value;
	UInt64 _scale;
};


typedef DateTime UtcTime;
	/// This simple DataType is a DateTime used to define Coordinated Universal Time (UTC) values.
	/// All time values conveyed between OPC UA Servers and Clients are UTC values. Clients shall provide any
	/// conversions between UTC and local time. UTC has the concept of leap seconds. Leap seconds can lead to
	/// repeating seconds. Therefore applications are allowed to use TAI (International Atomic Time) instead of UTC
	/// in any place where UtcTime is used. Details on time synchronization are discussed in Part 6. TODO
	///
	/// It should be noted that the Source and Server Timestamps may originate from different clocks that have no
	/// synchronization. It is also possible that one may use UTC while the other uses TAI.


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

// typedef ??? XmlElement TODO
	/// This Built-in DataType is used to define XML elements. Part 6 defines details about this DataType.
	/// XML data can always be modelled as a subtype of the Structure DataType with a single DataTypeEncoding
	/// that represents the XML complexType that defines the XML element (it is not necessary to have access to
	/// the XML Schema to define a DataTypeEncoding). For this reason a Server should never define Variables
	/// that use the XmlElement DataType unless the Server has no information about the XML elements that
	/// might be in the Variable Value.


class OPC_API DataTypeDefinition
	/// This abstract DataType is the base type for all DataTypes used to provide the meta data for custom DataTypes
	/// like Structures and Enumerations.
{
};


class OPC_API LocalizedText
	/// This Built-in DataType defines a structure containing a String in a locale-specific translation
	/// specified in the identifier for the locale. TODO
{
public:
	typedef open62541::UA_LocalizedText Type;

	LocalizedText(const std::string& text, const LocaleID& localeID = "en-US");
		/// Creates the LocalizedText.

	LocalizedText(const LocalizedText& other);
		/// Copy-constructs the LocalizedText.

	~LocalizedText();
		/// Destroys the LocalizedText.

	LocalizedText& operator = (const LocalizedText& other);
		/// assignment operator.

private:
	LocalizedText(const Type& other);
		/// Copy-constructs the LocalizedText.

	LocalizedText& operator = (const Type& other);
		/// Assignment operator.

	LocalizedText();


	void copy(const LocalizedText& other);
	void copy(const Type& other);
	void cleanup();

	Type _text;

	friend class VariableNode;
};


class OPC_API StructureField
{
public:
	typedef std::vector<StructureField> List;

	StructureField(const String& name,
		const LocalizedText& description,
		const NodeID& nodeID,
		Int32 valueRank,
		bool isOptional): _name(name),
			_description(description),
			_nodeID(nodeID),
			_valueRank(valueRank),
			_isOptional(isOptional)
		/// Creates StructureField.
	{
	}

	~StructureField()
		/// Destroys StructureField.
	{
	}

	const String& getName() const
		/// Returns name for the field that is unique within the StructureDefinition.
	{
		return _name;
	}

	const LocalizedText& getDescription() const
		/// Returns the localized description of the field.
	{
		return _description;
	}

	const NodeID& getNodeID() const
		/// Returns the NodeId of the DataType for the field.
	{
		return _nodeID;
	}

	Int32 getValueRank() const
		/// Returns the value rank for the field.
		/// It shall be Scalar (-1) or a fixed rank Array (>=1).
	{
		return _valueRank;
	}

	bool isOptional() const
		/// Returns true if the data type field in a Structure is optional.
	{
		return _isOptional;
	}

private:
	String        _name;
	LocalizedText _description;
	NodeID        _nodeID;
	Int32         _valueRank;
	bool          _isOptional;
};


class OPC_API StructureDefinition : public DataTypeDefinition
	/// This Structured DataType is used to provide the meta data for a custom Structure DataType. TODO
{
public:
	typedef typename StructureField::List FieldList;

	enum StructureType
	{
		OPC_STRUCT_TYPE_STRUCT = 0, // Structure without optional fields.
		OPC_STRUCT_TYPE_OPT_FLD,    // Structure with optional fields.
		OPC_STRUCT_TYPE_UNION       // Union DataType
	};


	StructureDefinition(const NodeID& defaultEncodingID,
		const NodeID& baseDataType,
		StructureType structureType,
		const FieldList& fields): _defaultEncodingID(defaultEncodingID),
			_baseDataType(baseDataType),
			_structureType(structureType),
			_fields(fields)
		// Creates StructureDefinition.
	{
	}

	~StructureDefinition()
		/// Destroys StructureDefinition.
	{
	}

	const NodeID& getDefaultEncodingID() const
		/// Returns the NodeId of the default DataTypeEncoding for the DataType.
		/// The default depends on the message encoding, Default Binary for UA Binary encoding and
		/// Default XML for XML encoding.
		/// If the DataType is only used inside nested Structures and is not directly contained in an ExtensionObject,
		/// the encoding NodeId is null.
	{
		return _defaultEncodingID;
	}

	const NodeID& getBaseDataType() const
		/// The NodeId of the direct supertype of the DataType. This might be the abstract Structure or the Union
		/// DataType.
	{
		return _baseDataType;
	}

	StructureType getStructureType() const
		/// Returns an enumeration value that specifies the type of Structure defined by the DataType.
	{
		return _structureType;
	}

	const FieldList& getFields() const
		/// Returns the list of fields that make up the data type.
		/// This definition assumes the structure has a sequential layout.
	{
		return _fields;
	}

private:
	NodeID        _defaultEncodingID;
	NodeID        _baseDataType;
	StructureType _structureType;
	FieldList     _fields;
};


class OPC_API EnumField
{
public:
	typedef std::vector<EnumField> List;

	EnumField(const String& name);
		/// Creates EnumField.

	~EnumField();
		/// Destroys EnumField.

	const String& getName() const;
		/// Returns the name of the field that must be unique within the EnumDefinition.

private:
	EnumField();

	String _name;
};


class OPC_API EnumDefinition
{
public:
	EnumDefinition(const EnumField::List& fields);
		/// Creates EnumDefinition.

	~EnumDefinition();
		/// Destroys EnumDefinition.

	const EnumField::List& getFields() const;
	/// The list of fields that make up the data type.

private:
	EnumField::List _fields;
};


enum NamingRuleType
	/// This DataType is an enumeration that identifies the NamingRule (see 6.4.4.2.1) TODO
{
	OPC_NAMING_RULE_MANDATORY = 1,
	OPC_NAMING_RULE_OPTIONAL,
	OPC_NAMING_RULE_CONSTRAINT
};


class OPC_API Enumeration
	/// This abstract DataType is the base DataType for all enumeration DataTypes like NodeClass.
	/// All DataTypes inheriting from this DataType have special handling for the encoding as defined in Part 6.TODO
	/// All enumeration DataTypes shall inherit from this DataType.
	///
	/// Some special rules apply when subtyping enumerations:
	/// Any enumeration DataType not directly inheriting from the Enumeration DataType can only restrict the
	/// enumeration values of its supertype. That is, it shall neither add enumeration values nor change the text
	/// associated to the enumeration value.
	///
	/// As an example, the enumeration Days having {‘Mo’, ‘Tu’, ‘We’, ‘Th’, ‘Fr’, ‘Sa’, ‘Su’} as values can be
	/// subtyped to the enumeration Workdays having {‘Mo’, ‘Tu’, ‘We’, ‘Th’, ‘Fr’}. The other direction, subtyping
	/// Workdays to Days would not be allowed as Days has values not allowed by Workdays (‘Sa’ and ‘Su’).
{
	//TODO, see 8.30
};

//typedef NodeID::IDType IdType; TODO ???
/// This DataType is an enumeration that identifies the IdType of a NodeId.

class QualifiedName
	/// Contains a qualified name. It is, for example, used as BrowseName.
	/// The name part of the QualifiedName is restricted to 512 characters.
{
public:
	QualifiedName(Poco::UInt16 nsIndex, const std::string& name);
		/// Creates the QualifiedName.

	~QualifiedName();
		/// Destroys the QualifiedName.

private:
	QualifiedName();

	Poco::UInt16 _nsIndex;
	std::string  _name;
	static const unsigned OPC_MAX_QNAME_LENGTH;
};


class OPC_API EnumValueType
	/// This Structured DataType is used to represent a human-readable representation of an Enumeration.
	/// Its elements are described in Table 35. When this type is used in an array representing human-readable
	/// representations of an enumeration, each Value shall be unique in that array.
{
public:
	EnumValueType(Int64 value,
		const LocalizedText& displayName,
		const LocalizedText& description);

	~EnumValueType();

	Int64 getValue() const;
	const LocalizedText& getDisplayName() const;
	const LocalizedText& getDescription() const;

private:
	Int64 _value;
	LocalizedText _displayName;
	LocalizedText _description;
};


class OPC_API OptionSet
{
public:
	OptionSet(const ByteString& value, const ByteString& validBits);

	~OptionSet();

	const ByteString& getValue() const;
	const ByteString& getValidBits() const;

private:
	ByteString _value;
	ByteString _validBits;
};


class Union
	/// This abstract DataType is the base DataType for all union DataTypes. The DataType is a subtype of
	/// Structure DataType. All DataTypes inheriting from this DataType have special handling for the encoding
	/// as defined in Part 6. All union DataTypes shall inherit directly from this DataType. TODO
{
public:
private:
};


class OPC_API Argument
	/// This Structured DataType defines a Method input or output argument specification.
	/// It is for example used in the input and output argument Properties for Methods.
{
public:
	typedef std::vector<unsigned> ArrayDimensions;

	Argument(const NodeID& nodeId, const std::string& description, const std::string& localeID = "en-US"):
		_nodeId(nodeId),
		_description(description, localeID)
		/// Creates the Argument.
	{
	}

	~Argument()
		/// Destroys the Argument.
	{
	}

	const String& getName() const
		/// Returns the name of the argument.
	{
		return _name;
	}

	const NodeID& getType() const
		/// The NodeId of the DataType of this argument.
	{
		return _nodeId;
	}

	Poco::UInt32 getValueRank() const
		/// Indicates whether the dataType is an array and how many dimensions the array has.
		/// It may have the following values:
		///   - n > 1: the dataType is an array with the specified number of dimensions.
		///   - OneDimension (1): The dataType is an array with one dimension.
		///   - OneOrMoreDimensions (0): The dataType is an array with one or more dimensions.
		///   - Scalar (−1): The dataType is not an array.
		///   - Any (−2): The dataType can be a scalar or an array with any number of dimensions.
		///   - ScalarOrOneDimension (−3): The dataType can be a scalar or a one dimensional array.
		///
		/// NOTE: All DataTypes are considered to be scalar, even if they have array-like semantics,
		/// like ByteString and String.
	{
		return _valueRank;
	}

	const ArrayDimensions& getArrayDimensions() const
		/// Returns the length of each dimension for an array dataType. It is intended to describe the capability
		/// of the dataType, not the current size.
		/// The number of elements shall be equal to the value of the valueRank. Shall be null if valueRank ≤ 0.
		/// A value of 0 for an individual dimension indicates that the dimension has a variable length.
	{
		return _arrayDimensions;
	}

	const LocalizedText& getDescription()
		/// A localized description of the argument.
	{
		return _description;
	}

private:
	Argument();

	String          _name;
	NodeID          _nodeId;
	Poco::UInt32    _valueRank;
	ArrayDimensions _arrayDimensions;
	LocalizedText   _description;
};


class OPC_API BaseNode
	/// This class represents an OPC BaseNode.
{
public:
	BaseNode();
		/// Creates the BaseNode.
		
	~BaseNode();
		/// Destroys the BaseNode.

private:

};


class OPC_API RolePermission
	/// This class represents the optional RolePermissions Attribute specifies the Permissions
	/// that apply to a Node for all Roles which have access to the Node.
{
public:
	RolePermission();
		/// Creates the RolePermission.

	~RolePermission();
		/// Destroys the RolePermission.

	const NodeID& getNodeID() const
		/// Returns the NodeId of the RolePermission object.
	{
		return _nodeID;
	}

	UInt32 getPermissions() const
		/// Returns the mask specifying which permissions are available to the Role.
	{
		return _permissions;
	}

private:
	NodeID _nodeID;
	UInt32 _permissions;
};

/*
 * typedef struct {
    UA_UInt32 specifiedAttributes;
    UA_LocalizedText displayName;
    UA_LocalizedText description;
    UA_UInt32 writeMask;
    UA_UInt32 userWriteMask;
} UA_NodeAttributes;

 typedef enum {
    UA_NODECLASS_UNSPECIFIED = 0,
    UA_NODECLASS_OBJECT = 1,
    UA_NODECLASS_VARIABLE = 2,
    UA_NODECLASS_METHOD = 4,
    UA_NODECLASS_OBJECTTYPE = 8,
    UA_NODECLASS_VARIABLETYPE = 16,
    UA_NODECLASS_REFERENCETYPE = 32,
    UA_NODECLASS_DATATYPE = 64,
    UA_NODECLASS_VIEW = 128
} UA_NodeClass;
 */
class OPC_API Node
{
public:
	typedef open62541::UA_NodeClass ClassType;

	Node(ClassType classType): _classType(static_cast<UInt32>(classType))
	{
	}

	~Node()
	{
	}

	virtual NodeID getNodeID() const = 0;

	UInt32 getClass() const
	{
		return _classType;
	}

	bool isClass(ClassType type)
	{
		return (_classType & type) != 0;
	}

	void addClass(ClassType type)
	{
		_classType |= type;
	}

	void removeClass(ClassType type)
	{
		_classType &= ~type;
	}

	virtual UInt32 getSpecifiedAttributes() const = 0;

	virtual LocalizedText getDisplayName() const = 0;

	virtual LocalizedText getDescription() const = 0;

	virtual UInt32 getWriteMask() const = 0;

	virtual UInt32 getUserWriteMask() const = 0;

protected:
	UInt32  _classType;
};


/*
 * typedef struct {
    UA_UInt32 specifiedAttributes;
    UA_LocalizedText displayName;
    UA_LocalizedText description;
    UA_UInt32 writeMask;
    UA_UInt32 userWriteMask;
    UA_Variant value;
    UA_NodeId dataType;
    UA_Int32 valueRank;
    size_t arrayDimensionsSize;
    UA_UInt32 *arrayDimensions;
    UA_Byte accessLevel;
    UA_Byte userAccessLevel;
    UA_Double minimumSamplingInterval;
    UA_Boolean historizing;
} UA_VariableAttributes;
 */

class OPC_API VariableNode: public Node
{
public:
	typedef open62541::UA_VariableAttributes Attributes;

	VariableNode(ClassType classType, const NodeID& nodeID, const Attributes& attributes): Node(classType),
		_nodeID(nodeID),
		_attributes(attributes)
	{
	}

	~VariableNode()
	{
	}

	//
	// atributes common to all nodes
	//

	virtual UInt32 getSpecifiedAttributes() const
	{
		return _attributes.specifiedAttributes;
	}

	virtual LocalizedText getDisplayName() const
	{
		return _attributes.displayName;
	}

	virtual LocalizedText getDescription() const
	{
		return _attributes.description;
	}

	virtual UInt32 getWriteMask() const
	{
		return _attributes.writeMask;
	}

	virtual UInt32 getUserWriteMask() const
	{
		return _attributes.userWriteMask;
	}

	//
	// VariableNode attributes
	//

	NodeID getNodeID() const
	{
		return _attributes.dataType;
	}
/*
	UA_Variant value;
	UA_NodeId dataType;
	UA_Int32 valueRank;
	size_t arrayDimensionsSize;
	UA_UInt32 *arrayDimensions;
	UA_Byte accessLevel;
	UA_Byte userAccessLevel;
	UA_Double minimumSamplingInterval;
	UA_Boolean historizing;*/

private:
	NodeID     _nodeID;
	Attributes _attributes;
};


//
// inlines
//


} // namespace OPC


namespace Dynamic {


template <>
class VarHolderImpl<OPC::DateTime>: public VarHolder
{
public:
	VarHolderImpl(const OPC::DateTime& val): _val(val)
	{
	}

	~VarHolderImpl()
	{
	}

	const std::type_info& type() const
	{
		return typeid(OPC::DateTime);
	}

	void convert(Int8& /*val*/) const
	{
		throw BadCastException();
	}

	void convert(Int16& /*val*/) const
	{
		throw BadCastException();
	}

	void convert(Int32& /*val*/) const
	{
		throw BadCastException();
	}

	void convert(Int64& val) const
	{
		throw BadCastException(); // TODO
		//val = _val.timestamp().epochMicroseconds();
	}

	void convert(UInt64& val) const
	{
		throw BadCastException(); // TODO
		//val = _val.timestamp().epochMicroseconds();
	}

	void convert(std::string& val) const
	{
		val = _val.toString();
	}

	void convert(OPC::DateTime& val) const
	{
		val = _val;
	}

	void convert(LocalDateTime& ldt) const
	{
		ldt = _val;
	}

	void convert(Timestamp& ts) const
	{
		throw BadCastException(); // TODO
		//ts = _val.timestamp();
	}

	VarHolder* clone(Placeholder<VarHolder>* pVarHolder = 0) const
	{
		return cloneHolder(pVarHolder, _val);
	}

	const OPC::DateTime& value() const
	{
		return _val;
	}

	bool isArray() const
	{
		return false;
	}

	bool isStruct() const
	{
		return false;
	}

	bool isInteger() const
	{
		return false;
	}

	bool isSigned() const
	{
		return false;
	}

	bool isNumeric() const
	{
		return false;
	}

	bool isBoolean() const
	{
		return false;
	}

	bool isString() const
	{
		return false;
	}

private:
	VarHolderImpl();
	VarHolderImpl(const VarHolderImpl&);
	VarHolderImpl& operator = (const VarHolderImpl&);

	OPC::DateTime _val;
};


} } // namespace Poco::Dynamic


#endif // OPC_Node_INCLUDED
