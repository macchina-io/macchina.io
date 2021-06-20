//
// RecordSetWrapper.cpp
//
// Library: JS/Data
// Package: Wrappers
// Module:  RecordSetWrapper
//
// Copyright (c) 2013-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#include "Poco/JS/Data/RecordSetWrapper.h"
#include "Poco/JS/Core/PooledIsolate.h"
#include "Poco/JS/Core/BufferWrapper.h"
#include "Poco/JS/Core/UUIDWrapper.h"
#include "Poco/Data/MetaColumn.h"
#include "Poco/Data/RowFormatter.h"
#include "Poco/Data/LOB.h"
#include "Poco/Version.h"
#include "Poco/Data/Date.h"
#include "Poco/Data/Time.h"


using namespace std::string_literals;


namespace Poco {
namespace JS {
namespace Data {


class JSONFormatter: public Poco::Data::RowFormatter
{
public:
	JSONFormatter():
		_isFirst(true)
	{
		setPrefix("[");
		setPostfix("\n]\n");
	}

	std::string& formatNames(const NameVecPtr pNames, std::string& formattedNames)
	{
		_isFirst = true;
		_pNames = pNames;
		formattedNames.clear();
		return formattedNames;
	}

	std::string& formatValues(const ValueVec& vals, std::string& formattedValues)
	{
		std::ostringstream str;
		if (_isFirst)
		{
			_isFirst = false;
		}
		else
		{
			str << ",";
		}
		str << "\n\t{\n";
		for (int i = 0; i < vals.size(); i++)
		{
			if (i > 0) str << ",";
			str << "\n\t\t\"" << (*_pNames)[i] << "\": ";
			if (vals[i].isNumeric())
			{
				str << vals[i].convert<std::string>();
			}
			else if (vals[i].isEmpty())
			{
				str << "null";
			}
			else
			{
				std::string val = Poco::Dynamic::Var::toString(vals[i]);
				if (val.empty() || val[0] != '"')
				{
					str << '"' << val << '"';
				}
				else
				{
					str << val;
				}
			}
		}
		str << "\n\t}";
		return formattedValues = str.str();
	}

private:
	bool _isFirst;
	NameVecPtr _pNames;
};


RecordSetHolder::RecordSetHolder(const Poco::SharedPtr<Poco::Data::Session>& pSession):
	_pSession(pSession),
	_pStatement(0),
	_pRecordSet(0)
{
}


RecordSetHolder::~RecordSetHolder()
{
	try
	{
		close();
	}
	catch (...)
	{
		poco_unexpected();
	}
}


void RecordSetHolder::close()
{
	delete _pRecordSet;
	_pRecordSet = 0;
	delete _pStatement;
	_pStatement = 0;
	_pSession.reset();
}


void RecordSetHolder::assignStatement(Poco::Data::Statement& statement)
{
	poco_assert (!_pStatement);

	_pStatement = new Poco::Data::Statement(statement);
}


void RecordSetHolder::updateRecordSet()
{
	poco_check_ptr (_pStatement);

	delete _pRecordSet;
	_pRecordSet = new Poco::Data::RecordSet(*_pStatement);
}


RecordSetWrapper::RecordSetWrapper()
{
}


RecordSetWrapper::~RecordSetWrapper()
{
}


v8::Handle<v8::ObjectTemplate> RecordSetWrapper::objectTemplate(v8::Isolate* pIsolate)
{
	v8::EscapableHandleScope handleScope(pIsolate);
	Core::PooledIsolate* pPooledIso = Core::PooledIsolate::fromIsolate(pIsolate);
	poco_check_ptr (pPooledIso);
	v8::Persistent<v8::ObjectTemplate>& pooledObjectTemplate(pPooledIso->objectTemplate("Data.RecordSet"s));
	if (pooledObjectTemplate.IsEmpty())
	{
		v8::Handle<v8::ObjectTemplate> objectTemplate = v8::ObjectTemplate::New(pIsolate);
		objectTemplate->SetInternalFieldCount(1);
		objectTemplate->SetAccessor(toV8Internalized(pIsolate, "columnCount"s), getColumnCount);
		objectTemplate->SetAccessor(toV8Internalized(pIsolate, "rowCount"s), getRowCount);
		objectTemplate->SetAccessor(toV8Internalized(pIsolate, "statement"s), getStatement);

		objectTemplate->Set(toV8Internalized(pIsolate, "getValue"s), v8::FunctionTemplate::New(pIsolate, getValue));
		objectTemplate->Set(toV8Internalized(pIsolate, "getName"s), v8::FunctionTemplate::New(pIsolate, getName));
		objectTemplate->Set(toV8Internalized(pIsolate, "getType"s), v8::FunctionTemplate::New(pIsolate, getType));
		objectTemplate->Set(toV8Internalized(pIsolate, "getLength"s), v8::FunctionTemplate::New(pIsolate, getLength));
		objectTemplate->Set(toV8Internalized(pIsolate, "getPrecision"s), v8::FunctionTemplate::New(pIsolate, getPrecision));
		objectTemplate->Set(toV8Internalized(pIsolate, "moveFirst"s), v8::FunctionTemplate::New(pIsolate, moveFirst));
		objectTemplate->Set(toV8Internalized(pIsolate, "moveLast"s), v8::FunctionTemplate::New(pIsolate, moveLast));
		objectTemplate->Set(toV8Internalized(pIsolate, "moveNext"s), v8::FunctionTemplate::New(pIsolate, moveNext));
		objectTemplate->Set(toV8Internalized(pIsolate, "movePrevious"s), v8::FunctionTemplate::New(pIsolate, movePrevious));
		objectTemplate->Set(toV8Internalized(pIsolate, "fetchNextPage"s), v8::FunctionTemplate::New(pIsolate, fetchNextPage));
		objectTemplate->Set(toV8Internalized(pIsolate, "close"s), v8::FunctionTemplate::New(pIsolate, close));
		objectTemplate->Set(toV8Internalized(pIsolate, "toJSON"s), v8::FunctionTemplate::New(pIsolate, toJSON));

		pooledObjectTemplate.Reset(pIsolate, objectTemplate);
	}
	v8::Local<v8::ObjectTemplate> recordSetTemplate = v8::Local<v8::ObjectTemplate>::New(pIsolate, pooledObjectTemplate);
	return handleScope.Escape(recordSetTemplate);
}


void RecordSetWrapper::destruct(const v8::WeakCallbackInfo<RecordSetHolder>& data)
{
	delete data.GetParameter();
}


void RecordSetWrapper::getColumnCount(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info)
{
	RecordSetHolder* pRecordSetHolder = Wrapper::unwrapNative<RecordSetHolder>(info);
	if (!pRecordSetHolder->isOpen()) return;
	info.GetReturnValue().Set(static_cast<Poco::UInt32>(pRecordSetHolder->recordSet().columnCount()));
}


void RecordSetWrapper::getRowCount(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info)
{
	RecordSetHolder* pRecordSetHolder = Wrapper::unwrapNative<RecordSetHolder>(info);
	if (!pRecordSetHolder->isOpen()) return;
	info.GetReturnValue().Set(static_cast<Poco::UInt32>(pRecordSetHolder->recordSet().rowCount()));
}


void RecordSetWrapper::getStatement(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info)
{
	RecordSetHolder* pRecordSetHolder = Wrapper::unwrapNative<RecordSetHolder>(info);
	if (!pRecordSetHolder->isOpen()) return;
	returnString(info, pRecordSetHolder->statement().toString());
}


void RecordSetWrapper::getValue(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	v8::Isolate* pIsolate(args.GetIsolate());
	v8::HandleScope handleScope(pIsolate);
	v8::Local<v8::Context> context(pIsolate->GetCurrentContext());
	RecordSetHolder* pRecordSetHolder = Wrapper::unwrapNative<RecordSetHolder>(args);
	if (!pRecordSetHolder->isOpen()) return;
	try
	{
		Poco::DynamicAny value;
		Poco::Data::MetaColumn::ColumnDataType type = Poco::Data::MetaColumn::FDT_UNKNOWN;
		if (args.Length() == 1)
		{
			if (args[0]->IsNumber())
			{
				std::size_t col = args[0]->Uint32Value(context).FromMaybe(0);
				value = pRecordSetHolder->recordSet().value(col);
				type  = pRecordSetHolder->recordSet().columnType(col);
			}
			else
			{
				std::string name = toString(pIsolate, args[0]);
				value = pRecordSetHolder->recordSet().value(name);
				type  = pRecordSetHolder->recordSet().columnType(name);
			}
			returnDynamicAny(args, value, type);
			return;
		}
		else if (args.Length() == 2)
		{
			if (args[1]->IsNumber())
			{
				if (args[0]->IsNumber())
				{
					std::size_t col = args[0]->Uint32Value(context).FromMaybe(0);
					std::size_t row = args[1]->Uint32Value(context).FromMaybe(0);
					value = pRecordSetHolder->recordSet().value(col, row);
					type  = pRecordSetHolder->recordSet().columnType(col);
				}
				else
				{
					std::string name = toString(pIsolate, args[0]);
					value = pRecordSetHolder->recordSet().value(name, args[1]->Uint32Value(context).FromMaybe(0));
					type  = pRecordSetHolder->recordSet().columnType(name);
				}
				returnDynamicAny(args, value, type);
				return;
			}
		}
		returnException(args, std::string("bad arguments: column name or index required, row index optional"));
	}
	catch (Poco::Exception& exc)
	{
		returnException(args, exc);
	}
}


void RecordSetWrapper::getName(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	v8::Isolate* pIsolate(args.GetIsolate());
	v8::HandleScope handleScope(pIsolate);
	v8::Local<v8::Context> context(pIsolate->GetCurrentContext());
	RecordSetHolder* pRecordSetHolder = Wrapper::unwrapNative<RecordSetHolder>(args);
	if (!pRecordSetHolder->isOpen()) return;
	try
	{
		if (args.Length() == 1)
		{
			if (args[0]->IsNumber())
			{
				std::size_t col = args[0]->Uint32Value(context).FromMaybe(0);
				returnString(args, pRecordSetHolder->recordSet().columnName(col));
				return;
			}
		}
		returnException(args, "bad arguments: column index required"s);
	}
	catch (Poco::Exception& exc)
	{
		returnException(args, exc);
	}
}


void RecordSetWrapper::getType(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	v8::Isolate* pIsolate(args.GetIsolate());
	v8::HandleScope handleScope(pIsolate);
	v8::Local<v8::Context> context(pIsolate->GetCurrentContext());
	RecordSetHolder* pRecordSetHolder = Wrapper::unwrapNative<RecordSetHolder>(args);
	if (!pRecordSetHolder->isOpen()) return;
	try
	{
		if (args.Length() == 1)
		{
			Poco::Data::MetaColumn::ColumnDataType type;
			if (args[0]->IsNumber())
			{
				std::size_t col = args[0]->Uint32Value(context).FromMaybe(0);
				type = pRecordSetHolder->recordSet().columnType(col);
			}
			else
			{
				std::string name = toString(pIsolate, args[0]);
				type = pRecordSetHolder->recordSet().columnType(name);
			}
			std::string typeString = typeToString(type);
			returnString(args, typeString);
			return;
		}
		returnException(args, "bad arguments: column name or index required"s);
	}
	catch (Poco::Exception& exc)
	{
		returnException(args, exc);
	}
}


void RecordSetWrapper::getLength(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	v8::Isolate* pIsolate(args.GetIsolate());
	v8::HandleScope handleScope(pIsolate);
	v8::Local<v8::Context> context(pIsolate->GetCurrentContext());
	RecordSetHolder* pRecordSetHolder = Wrapper::unwrapNative<RecordSetHolder>(args);
	if (!pRecordSetHolder->isOpen()) return;
	try
	{
		if (args.Length() == 1)
		{
			if (args[0]->IsNumber())
			{
				std::size_t col = args[0]->Uint32Value(context).FromMaybe(0);
				args.GetReturnValue().Set(static_cast<Poco::UInt32>(pRecordSetHolder->recordSet().columnLength(col)));
			}
			else
			{
				std::string name = toString(pIsolate, args[0]);
				args.GetReturnValue().Set(static_cast<Poco::UInt32>(pRecordSetHolder->recordSet().columnLength(name)));
			}
			return;
		}
		returnException(args, "bad arguments: column name or index required"s);
	}
	catch (Poco::Exception& exc)
	{
		returnException(args, exc);
	}
}


void RecordSetWrapper::getPrecision(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	v8::Isolate* pIsolate(args.GetIsolate());
	v8::HandleScope handleScope(pIsolate);
	v8::Local<v8::Context> context(pIsolate->GetCurrentContext());
	RecordSetHolder* pRecordSetHolder = Wrapper::unwrapNative<RecordSetHolder>(args);
	if (!pRecordSetHolder->isOpen()) return;
	try
	{
		if (args.Length() == 1)
		{
			if (args[0]->IsNumber())
			{
				std::size_t col = args[0]->Uint32Value(context).FromMaybe(0);
				args.GetReturnValue().Set(static_cast<Poco::UInt32>(pRecordSetHolder->recordSet().columnPrecision(col)));
			}
			else
			{
				std::string name = toString(pIsolate, args[0]);
				args.GetReturnValue().Set(static_cast<Poco::UInt32>(pRecordSetHolder->recordSet().columnPrecision(name)));
			}
			return;
		}
		returnException(args, "bad arguments: column name or index required"s);
	}
	catch (Poco::Exception& exc)
	{
		returnException(args, exc);
	}
}


void RecordSetWrapper::moveFirst(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	RecordSetHolder* pRecordSetHolder = Wrapper::unwrapNative<RecordSetHolder>(args);
	if (!pRecordSetHolder->isOpen()) return;
	try
	{
		args.GetReturnValue().Set(pRecordSetHolder->recordSet().moveFirst());
	}
	catch (Poco::Exception& exc)
	{
		returnException(args, exc);
	}
}


void RecordSetWrapper::moveLast(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	RecordSetHolder* pRecordSetHolder = Wrapper::unwrapNative<RecordSetHolder>(args);
	if (!pRecordSetHolder->isOpen()) return;
	try
	{
		args.GetReturnValue().Set(pRecordSetHolder->recordSet().moveLast());
	}
	catch (Poco::Exception& exc)
	{
		returnException(args, exc);
	}
}


void RecordSetWrapper::moveNext(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	RecordSetHolder* pRecordSetHolder = Wrapper::unwrapNative<RecordSetHolder>(args);
	if (!pRecordSetHolder->isOpen()) return;
	try
	{
		args.GetReturnValue().Set(pRecordSetHolder->recordSet().moveNext());
	}
	catch (Poco::Exception& exc)
	{
		returnException(args, exc);
	}
}


void RecordSetWrapper::movePrevious(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	RecordSetHolder* pRecordSetHolder = Wrapper::unwrapNative<RecordSetHolder>(args);
	if (!pRecordSetHolder->isOpen()) return;
	try
	{
		args.GetReturnValue().Set(pRecordSetHolder->recordSet().movePrevious());
	}
	catch (Poco::Exception& exc)
	{
		returnException(args, exc);
	}
}


void RecordSetWrapper::fetchNextPage(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	RecordSetHolder* pRecordSetHolder = Wrapper::unwrapNative<RecordSetHolder>(args);
	if (!pRecordSetHolder->isOpen()) return;
	try
	{
		if (!pRecordSetHolder->statement().done())
		{
			args.GetReturnValue().Set(static_cast<Poco::UInt32>(pRecordSetHolder->statement().execute()));
			pRecordSetHolder->updateRecordSet();
		}
		else
		{
			args.GetReturnValue().Set(0);
		}
	}
	catch (Poco::Exception& exc)
	{
		returnException(args, exc);
	}
}


void RecordSetWrapper::close(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	RecordSetHolder* pRecordSetHolder = Wrapper::unwrapNative<RecordSetHolder>(args);
	if (!pRecordSetHolder->isOpen()) return;
	pRecordSetHolder->close();
}


void RecordSetWrapper::toJSON(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	v8::HandleScope scope(args.GetIsolate());

	RecordSetHolder* pRecordSetHolder = Wrapper::unwrapNative<RecordSetHolder>(args);
	if (!pRecordSetHolder->isOpen()) return;

	try
	{
		Poco::Data::RecordSet& rs = pRecordSetHolder->recordSet();
		if (rs.begin() != rs.end())
		{
			rs.setRowFormatter(new JSONFormatter);
			std::ostringstream ostr;
			ostr << rs;
			returnString(args, ostr.str());
		}
		else
		{
			returnString(args, "[]"s);
		}
	}
	catch (Poco::Exception& exc)
	{
		returnException(args, exc);
	}
}


void RecordSetWrapper::returnDynamicAny(const v8::FunctionCallbackInfo<v8::Value>& args, const Poco::DynamicAny& value, Poco::Data::MetaColumn::ColumnDataType typeHint)
{
	v8::Isolate* pIsolate(args.GetIsolate());
	v8::HandleScope scope(pIsolate);
	v8::Local<v8::Context> context(pIsolate->GetCurrentContext());

	switch (typeHint)
	{
	case Poco::Data::MetaColumn::FDT_BOOL:
		args.GetReturnValue().Set(value.convert<bool>());
		break;
	case Poco::Data::MetaColumn::FDT_INT8:
	case Poco::Data::MetaColumn::FDT_INT16:
	case Poco::Data::MetaColumn::FDT_INT32:
		args.GetReturnValue().Set(value.convert<Poco::Int32>());
		break;
	case Poco::Data::MetaColumn::FDT_UINT8:
	case Poco::Data::MetaColumn::FDT_UINT16:
	case Poco::Data::MetaColumn::FDT_UINT32:
		args.GetReturnValue().Set(value.convert<Poco::UInt32>());
		break;
	case Poco::Data::MetaColumn::FDT_INT64:
	case Poco::Data::MetaColumn::FDT_UINT64:
	case Poco::Data::MetaColumn::FDT_FLOAT:
	case Poco::Data::MetaColumn::FDT_DOUBLE:
		args.GetReturnValue().Set(value.convert<double>());
		break;
	case Poco::Data::MetaColumn::FDT_STRING:
		returnString(args, value.convert<std::string>());
		break;
	case Poco::Data::MetaColumn::FDT_TIMESTAMP:
		{
			Poco::DateTime dt = value.extract<Poco::DateTime>();
			double millis = dt.timestamp().epochMicroseconds()/1000.0;
			v8::MaybeLocal<v8::Value> maybeJSDate(v8::Date::New(context, millis));
			v8::Local<v8::Value> jsDate;
			if (maybeJSDate.ToLocal(&jsDate))
			{
				args.GetReturnValue().Set(jsDate);
			}
		}
		break;
	case Poco::Data::MetaColumn::FDT_DATE:
		{
			Poco::Data::Date date = value.extract<Poco::Data::Date>();
			Poco::DateTime dt(date.year(), date.month(), date.day());
			double millis = dt.timestamp().epochMicroseconds()/1000.0;
			v8::MaybeLocal<v8::Value> maybeJSDate(v8::Date::New(context, millis));
			v8::Local<v8::Value> jsDate;
			if (maybeJSDate.ToLocal(&jsDate))
			{
				args.GetReturnValue().Set(jsDate);
			}
		}
		break;
	case Poco::Data::MetaColumn::FDT_TIME:
		{
			Poco::DateTime now;
			Poco::Data::Time time = value.extract<Poco::Data::Time>();
			Poco::DateTime dt(now.year(), now.month(), now.day(), time.hour(), time.minute(), time.second());
			double millis = dt.timestamp().epochMicroseconds()/1000.0;
			v8::MaybeLocal<v8::Value> maybeJSDate(v8::Date::New(context, millis));
			v8::Local<v8::Value> jsDate;
			if (maybeJSDate.ToLocal(&jsDate))
			{
				args.GetReturnValue().Set(jsDate);
			}
		}
		break;
	case Poco::Data::MetaColumn::FDT_UUID:
		{
			Poco::UUID uuid = value.extract<Poco::UUID>();
			Poco::UUID* pUUID = nullptr;
			try
			{
				pUUID = new Poco::UUID(uuid);
				Poco::JS::Core::UUIDWrapper wrapper;
				v8::Persistent<v8::Object>& uuidObject(wrapper.wrapNativePersistent(args.GetIsolate(), pUUID));
				args.GetReturnValue().Set(v8::Local<v8::Object>::New(pIsolate, uuidObject));
			}
			catch (...)
			{
				delete pUUID;
				throw;
			}
		}
		break;
	case Poco::Data::MetaColumn::FDT_BLOB:
		{
			Poco::Data::BLOB blob = value.extract<Poco::Data::BLOB>();
			Poco::JS::Core::BufferWrapper::Buffer* pBuffer = nullptr;
			try
			{
				pBuffer = new Poco::JS::Core::BufferWrapper::Buffer(reinterpret_cast<const char*>(blob.rawContent()), blob.size());
				Poco::JS::Core::BufferWrapper wrapper;
				v8::Persistent<v8::Object>& bufferObject(wrapper.wrapNativePersistent(pIsolate, pBuffer));
				args.GetReturnValue().Set(v8::Local<v8::Object>::New(pIsolate, bufferObject));
			}
			catch (...)
			{
				delete pBuffer;
				throw;
			}
		}
		break;
	case Poco::Data::MetaColumn::FDT_CLOB:
		{
			Poco::Data::CLOB clob = value.extract<Poco::Data::CLOB>();
			Poco::JS::Core::BufferWrapper::Buffer* pBuffer = nullptr;
			try
			{
				pBuffer = new Poco::JS::Core::BufferWrapper::Buffer(clob.rawContent(), clob.size());
				Poco::JS::Core::BufferWrapper wrapper;
				v8::Persistent<v8::Object>& bufferObject(wrapper.wrapNativePersistent(pIsolate, pBuffer));
				args.GetReturnValue().Set(v8::Local<v8::Object>::New(pIsolate, bufferObject));
			}
			catch (...)
			{
				delete pBuffer;
				throw;
			}
		}
		break;
	case Poco::Data::MetaColumn::FDT_WSTRING:
	case Poco::Data::MetaColumn::FDT_UNKNOWN:
	default:
		returnException(args, "cannot convert value of type "s + typeToString(typeHint));
		break;
	}
}


std::string RecordSetWrapper::typeToString(Poco::Data::MetaColumn::ColumnDataType type)
{
	switch (type)
	{
	case Poco::Data::MetaColumn::FDT_BOOL:
		return "bool"s;
	case Poco::Data::MetaColumn::FDT_INT8:
		return "Int8"s;
	case Poco::Data::MetaColumn::FDT_INT16:
		return "Int16"s;
	case Poco::Data::MetaColumn::FDT_INT32:
		return "Int32"s;
	case Poco::Data::MetaColumn::FDT_INT64:
		return "Int64"s;
	case Poco::Data::MetaColumn::FDT_UINT8:
		return "UInt8"s;
	case Poco::Data::MetaColumn::FDT_UINT16:
		return "UInt16"s;
	case Poco::Data::MetaColumn::FDT_UINT32:
		return "UInt32"s;
	case Poco::Data::MetaColumn::FDT_UINT64:
		return "UInt64"s;
	case Poco::Data::MetaColumn::FDT_FLOAT:
		return "float"s;
	case Poco::Data::MetaColumn::FDT_DOUBLE:
		return "double"s;
	case Poco::Data::MetaColumn::FDT_STRING:
		return "string"s;
	case Poco::Data::MetaColumn::FDT_BLOB:
		return "BLOB"s;
	case Poco::Data::MetaColumn::FDT_CLOB:
		return "CLOB"s;
	case Poco::Data::MetaColumn::FDT_TIMESTAMP:
		return "DateTime"s;
	case Poco::Data::MetaColumn::FDT_WSTRING:
		return "wstring"s;
	case Poco::Data::MetaColumn::FDT_DATE:
		return "Date"s;
	case Poco::Data::MetaColumn::FDT_TIME:
		return "Time"s;
	case Poco::Data::MetaColumn::FDT_UUID:
		return "UUID"s;
	case Poco::Data::MetaColumn::FDT_UNKNOWN:
		return "unknown"s;
	default:
		return "unknown"s;
	}
}


} } } // namespace Poco::JS::Data
