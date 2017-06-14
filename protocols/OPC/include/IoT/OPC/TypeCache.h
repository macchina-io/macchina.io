//
// Client.h
//
// $Id$
//
// Library: OPC
// Package: OPC
// Module:  TypeCache
//
// Definition of the TypeCache and related classes.
//
// Copyright (c) 2010-2015, Günter Obiltschnig.
//
// SPDX-License-Identifier:	BSL-1.0
//


#ifndef IoT_OPC_TypeCache_INCLUDED
#define IoT_OPC_TypeCache_INCLUDED


#include "IoT/OPC/OPC.h"
#include "Poco/Exception.h"
#include <unordered_map>
#include <sstream>

namespace IoT {
namespace OPC {


template <typename T>
class ValueNodeID
{
public:
	ValueNodeID() = delete;
	ValueNodeID(int nsIndex, const T& id): _nsIndex(nsIndex), _id(id)
	{
	}

	bool operator == (const ValueNodeID& other) const
	{
		return _nsIndex == other._nsIndex && _id == other._id;
	}

	int nsIndex() const
	{
		return _nsIndex;
	}

	const T& id() const
	{
		return _id;
	}

	std::string toString() const
	{
		std::ostringstream os;
		os << '(' << _nsIndex << ", " << _id << ')';
		return os.str();
	}

private:
	int _nsIndex;
	T   _id;
};

template <typename T>
struct ValueNodeHasher
{
	std::size_t operator()(const ValueNodeID<T>& key) const
	{
		std::size_t res = 17;
		res = res * 31 + std::hash<T>()(key.id());
		res = res * 31 + std::hash<int>()(key.nsIndex());
		return res;
	}
};

struct NodeType
{
	int  _type;
	bool _isArray;
};

typedef ValueNodeID<std::string> StringNodeID;
typedef ValueNodeHasher<std::string> StringNodeHasher;
typedef ValueNodeID<int> IntNodeID;
typedef ValueNodeHasher<int> IntNodeHasher;
typedef std::unordered_map<StringNodeID, NodeType, StringNodeHasher> StringTypeMap;
typedef std::unordered_map<IntNodeID, NodeType, IntNodeHasher> IntTypeMap;

class OPC_API TypeCache
{
public:
	TypeCache();
		/// Creates the type cache.
	
	~TypeCache();
		/// Destroys the type cache.

	void add(const IntNodeID& id, int type, bool array = false);
		/// Adds the integer node ID and its type to the cache.

	void add(const StringNodeID& id, int type, bool array = false);
		/// Adds the string node ID and its type to the cache.

	bool has(const IntNodeID& id) const;
		/// Returns true if the integer node is found in the cache.

	bool has(const StringNodeID& id) const;
		/// Returns true if the string node is found in the cache.

	bool has(const IntNodeID& id, int type, bool array = false) const;
		/// Returns true if the integer node of specified type is found in the cache.

	bool has(const StringNodeID& id, int type, bool array = false) const;
		/// Returns true if the string node of specified type is found in the cache.

	const NodeType& type(const IntNodeID& id) const;
		/// Returns the node type.

	const NodeType& type(const StringNodeID& id) const;
		/// Returns the node type.

	void clear();
		/// Clears the cache content.

private:
	template <typename N, typename T>
	const NodeType& getType(const N& id, const T& map) const
	{
		const auto& entry = map.find(id);
		if(entry != map.end())
		{
			return entry->second;
		}
		throw Poco::NotFoundException(id.toString());
	}

	StringTypeMap _stringIDs;
	IntTypeMap    _intIDs;
};


//
// inlines
//

inline void TypeCache::add(const IntNodeID& id, int type, bool array)
{
	NodeType nt = {type, array};
	_intIDs[id] = nt;
}


inline void TypeCache::add(const StringNodeID& id, int type, bool array)
{
	NodeType nt = {type, array};
	_stringIDs[id] = nt;
}


inline bool TypeCache::has(const IntNodeID& id) const
{
	const auto& it = _intIDs.find(id);
	return it != _intIDs.end();
}


inline bool TypeCache::has(const StringNodeID& id) const
{
	const auto& it = _stringIDs.find(id);
	return it != _stringIDs.end();
}


inline bool TypeCache::has(const IntNodeID& id, int type, bool array) const
{
	const auto& it = _intIDs.find(id);
	return it != _intIDs.end() && it->second._type == type && it->second._isArray == array;
}


inline bool TypeCache::has(const StringNodeID& id, int type, bool array) const
{
	const auto& it = _stringIDs.find(id);
	return it != _stringIDs.end() && it->second._type == type && it->second._isArray == array;
}


inline void TypeCache::clear()
{
	_intIDs.clear();
	_stringIDs.clear();
}


inline const NodeType& TypeCache::type(const IntNodeID& id) const
{
	return getType(id, _intIDs);
	/*const auto& entry = _intIDs.find(id);
	if(entry != _intIDs.end())
	{
		return entry->second;
	}
	throw Poco::NotFoundException(id.toString());*/
}


inline const NodeType& TypeCache::type(const StringNodeID& id) const
{
	return getType(id, _stringIDs);
	/*const auto& entry = _stringIDs.find(id);
	if(entry != _stringIDs.end())
	{
		return entry->second;
	}
	throw Poco::NotFoundException(id.toString());*/
}


} } // namespace IoT::OPC


#endif // IoT_OPC_TypeCache_INCLUDED
