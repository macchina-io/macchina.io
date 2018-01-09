//
// RecordSetWrapper.h
//
// Library: JS/Data
// Package: Wrappers
// Module:  RecordSetWrapper
//
// Definition of the RecordSetWrapper class.
//
// Copyright (c) 2013-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef JS_Data_RecordSetWrapper_INCLUDED
#define JS_Data_RecordSetWrapper_INCLUDED


#include "Poco/JS/Data/Data.h"
#include "Poco/JS/Core/Wrapper.h"
#include "Poco/Data/RecordSet.h"
#include "Poco/Any.h"


namespace Poco {
namespace JS {
namespace Data {


class JSData_API RecordSetHolder
{
public:
	RecordSetHolder();
		/// Creates the RecordSetHolder.

	~RecordSetHolder();
		/// Destroys the RecordSetHolder.

	Poco::Data::Statement& statement()
	{
		poco_check_ptr (_pStatement);

		return *_pStatement;
	}

	Poco::Data::RecordSet& recordSet()
	{
		poco_check_ptr (_pRecordSet);

		return *_pRecordSet;
	}

	void assignStatement(Poco::Data::Statement& statement);
	void updateRecordSet();

	void close();
	bool isOpen() const
	{
		return _pStatement != 0;
	}

private:
	Poco::Data::Statement* _pStatement;
	Poco::Data::RecordSet* _pRecordSet;
};


class JSData_API RecordSetWrapper: public JS::Core::Wrapper
	/// JavaScript wrapper for Poco::Data::RecordSet.
{
public:
	RecordSetWrapper();
		/// Creates the RecordSetWrapper.

	~RecordSetWrapper();
		/// Destroys the RecordSetWrapper.

	// Wrapper
	v8::Handle<v8::ObjectTemplate> objectTemplate(v8::Isolate* pIsolate);

protected:
	static void construct(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void destruct(const v8::WeakCallbackInfo<RecordSetHolder>& data);

	static void getColumnCount(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info);
	static void getRowCount(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info);
	static void getStatement(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info);

	static void getValue(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void getName(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void getType(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void getLength(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void getPrecision(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void moveFirst(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void moveLast(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void moveNext(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void movePrevious(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void fetchNextPage(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void close(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void toJSON(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void returnDynamicAny(const v8::FunctionCallbackInfo<v8::Value>& args, const Poco::DynamicAny& value, Poco::Data::MetaColumn::ColumnDataType typeHint);

	friend class SessionWrapper;
};


} } } // namespace Poco::JS::Data


#endif // JS_Data_RecordSetWrapper_INCLUDED
