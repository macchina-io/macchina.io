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
// SPDX-License-Identifier: Apache-2.0
//


#include "Poco/JS/Data/RecordSetWrapper.h"
#include "Poco/JS/Core/PooledIsolate.h"
#include "Poco/Data/MetaColumn.h"
#include "Poco/Data/RowFormatter.h"
#include "Poco/Version.h"
#include "Poco/Data/Date.h"
#include "Poco/Data/Time.h"


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


RecordSetHolder::RecordSetHolder():
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
	Poco::JS::Core::PooledIsolate* pPooledIso = Poco::JS::Core::PooledIsolate::fromIsolate(pIsolate);
	poco_check_ptr (pPooledIso);
	v8::Persistent<v8::ObjectTemplate>& pooledObjectTemplate(pPooledIso->objectTemplate("Data.RecordSet"));
	if (pooledObjectTemplate.IsEmpty())
	{
		v8::Handle<v8::ObjectTemplate> objectTemplate = v8::ObjectTemplate::New(pIsolate);
		objectTemplate->SetInternalFieldCount(1);
		objectTemplate->SetAccessor(v8::String::NewFromUtf8(pIsolate, "columnCount"), getColumnCount);
		objectTemplate->SetAccessor(v8::String::NewFromUtf8(pIsolate, "rowCount"), getRowCount);
		objectTemplate->SetAccessor(v8::String::NewFromUtf8(pIsolate, "statement"), getStatement);

		objectTemplate->Set(v8::String::NewFromUtf8(pIsolate, "getValue"), v8::FunctionTemplate::New(pIsolate, getValue));
		objectTemplate->Set(v8::String::NewFromUtf8(pIsolate, "getName"), v8::FunctionTemplate::New(pIsolate, getName));
		objectTemplate->Set(v8::String::NewFromUtf8(pIsolate, "getType"), v8::FunctionTemplate::New(pIsolate, getType));
		objectTemplate->Set(v8::String::NewFromUtf8(pIsolate, "getLength"), v8::FunctionTemplate::New(pIsolate, getLength));
		objectTemplate->Set(v8::String::NewFromUtf8(pIsolate, "getPrecision"), v8::FunctionTemplate::New(pIsolate, getPrecision));
		objectTemplate->Set(v8::String::NewFromUtf8(pIsolate, "moveFirst"), v8::FunctionTemplate::New(pIsolate, moveFirst));
		objectTemplate->Set(v8::String::NewFromUtf8(pIsolate, "moveLast"), v8::FunctionTemplate::New(pIsolate, moveLast));
		objectTemplate->Set(v8::String::NewFromUtf8(pIsolate, "moveNext"), v8::FunctionTemplate::New(pIsolate, moveNext));
		objectTemplate->Set(v8::String::NewFromUtf8(pIsolate, "movePrevious"), v8::FunctionTemplate::New(pIsolate, movePrevious));
		objectTemplate->Set(v8::String::NewFromUtf8(pIsolate, "fetchNextPage"), v8::FunctionTemplate::New(pIsolate, fetchNextPage));
		objectTemplate->Set(v8::String::NewFromUtf8(pIsolate, "close"), v8::FunctionTemplate::New(pIsolate, close));
		objectTemplate->Set(v8::String::NewFromUtf8(pIsolate, "toJSON"), v8::FunctionTemplate::New(pIsolate, toJSON));

		pooledObjectTemplate.Reset(pIsolate, objectTemplate);
	}
	v8::Local<v8::ObjectTemplate> dateTimeTemplate = v8::Local<v8::ObjectTemplate>::New(pIsolate, pooledObjectTemplate);
	return handleScope.Escape(dateTimeTemplate);
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
				std::size_t col = args[0]->Uint32Value();
				value = pRecordSetHolder->recordSet().value(col);
				type  = pRecordSetHolder->recordSet().columnType(col);
			}
			else
			{
				std::string name = toString(args[0]);
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
					std::size_t col = args[0]->Uint32Value();
					std::size_t row = args[1]->Uint32Value();
					value = pRecordSetHolder->recordSet().value(col, row);
					type  = pRecordSetHolder->recordSet().columnType(col);
				}
				else
				{
					std::string name = toString(args[0]);
					value = pRecordSetHolder->recordSet().value(name, args[1]->Uint32Value());
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
	RecordSetHolder* pRecordSetHolder = Wrapper::unwrapNative<RecordSetHolder>(args);
	if (!pRecordSetHolder->isOpen()) return;
	try
	{
		if (args.Length() == 1)
		{
			if (args[0]->IsNumber())
			{
				std::size_t col = args[0]->Uint32Value();
				returnString(args, pRecordSetHolder->recordSet().columnName(col));
				return;
			}
		}
		returnException(args, std::string("bad arguments: column index required"));
	}
	catch (Poco::Exception& exc)
	{
		returnException(args, exc);
	}
}


void RecordSetWrapper::getType(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	RecordSetHolder* pRecordSetHolder = Wrapper::unwrapNative<RecordSetHolder>(args);
	if (!pRecordSetHolder->isOpen()) return;
	try
	{
		if (args.Length() == 1)
		{
			Poco::Data::MetaColumn::ColumnDataType type;
			if (args[0]->IsNumber())
			{
				std::size_t col = args[0]->Uint32Value();
				type = pRecordSetHolder->recordSet().columnType(col);
			}
			else
			{
				std::string name = toString(args[0]);
				type = pRecordSetHolder->recordSet().columnType(name);
			}
			std::string typeString;
			switch (type)
			{
			case Poco::Data::MetaColumn::FDT_BOOL:
				typeString = "bool";
				break;
			case Poco::Data::MetaColumn::FDT_INT8:
				typeString = "Int8";
				break;
			case Poco::Data::MetaColumn::FDT_INT16:
				typeString = "Int16";
				break;
			case Poco::Data::MetaColumn::FDT_INT32:
				typeString = "Int32";
				break;
			case Poco::Data::MetaColumn::FDT_INT64:
				typeString = "Int64";
				break;
			case Poco::Data::MetaColumn::FDT_UINT8:
				typeString = "UInt8";
				break;
			case Poco::Data::MetaColumn::FDT_UINT16:
				typeString = "UInt16";
				break;
			case Poco::Data::MetaColumn::FDT_UINT32:
				typeString = "UInt32";
				break;
			case Poco::Data::MetaColumn::FDT_UINT64:
				typeString = "UInt64";
				break;
			case Poco::Data::MetaColumn::FDT_FLOAT:
				typeString = "float";
				break;
			case Poco::Data::MetaColumn::FDT_DOUBLE:
				typeString = "double";
				break;
			case Poco::Data::MetaColumn::FDT_STRING:
				typeString = "string";
				break;
			case Poco::Data::MetaColumn::FDT_BLOB:
				typeString = "BLOB";
				break;
			case Poco::Data::MetaColumn::FDT_UNKNOWN:
				typeString = "unknown";
				break;
			case Poco::Data::MetaColumn::FDT_TIMESTAMP:
				typeString = "DateTime";
				break;
			case Poco::Data::MetaColumn::FDT_CLOB:
				typeString = "CLOB";
				break;
			case Poco::Data::MetaColumn::FDT_WSTRING:
				typeString = "wstring";
				break;
			case Poco::Data::MetaColumn::FDT_DATE:
				typeString = "Date";
				break;
			case Poco::Data::MetaColumn::FDT_TIME:
				typeString = "Time";
				break;
			}
			returnString(args, typeString);
			return;
		}
		returnException(args, std::string("bad arguments: column name or index required"));
	}
	catch (Poco::Exception& exc)
	{
		returnException(args, exc);
	}
}


void RecordSetWrapper::getLength(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	RecordSetHolder* pRecordSetHolder = Wrapper::unwrapNative<RecordSetHolder>(args);
	if (!pRecordSetHolder->isOpen()) return;
	try
	{
		if (args.Length() == 1)
		{
			if (args[0]->IsNumber())
			{
				std::size_t col = args[0]->Uint32Value();
				args.GetReturnValue().Set(static_cast<Poco::UInt32>(pRecordSetHolder->recordSet().columnLength(col)));
			}
			else
			{
				std::string name = toString(args[0]);
				args.GetReturnValue().Set(static_cast<Poco::UInt32>(pRecordSetHolder->recordSet().columnLength(name)));
			}
			return;
		}
		returnException(args, std::string("bad arguments: column name or index required"));
	}
	catch (Poco::Exception& exc)
	{
		returnException(args, exc);
	}
}


void RecordSetWrapper::getPrecision(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	RecordSetHolder* pRecordSetHolder = Wrapper::unwrapNative<RecordSetHolder>(args);
	if (!pRecordSetHolder->isOpen()) return;
	try
	{
		if (args.Length() == 1)
		{
			if (args[0]->IsNumber())
			{
				std::size_t col = args[0]->Uint32Value();
				args.GetReturnValue().Set(static_cast<Poco::UInt32>(pRecordSetHolder->recordSet().columnPrecision(col)));
			}
			else
			{
				std::string name = toString(args[0]);
				args.GetReturnValue().Set(static_cast<Poco::UInt32>(pRecordSetHolder->recordSet().columnPrecision(name)));
			}
			return;
		}
		returnException(args, std::string("bad arguments: column name or index required"));
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

	pRecordSetHolder->recordSet().setRowFormatter(new JSONFormatter);
	std::ostringstream ostr;
	ostr << pRecordSetHolder->recordSet();
	returnString(args, ostr.str());
}


void RecordSetWrapper::returnDynamicAny(const v8::FunctionCallbackInfo<v8::Value>& args, const Poco::DynamicAny& value, Poco::Data::MetaColumn::ColumnDataType typeHint)
{
	v8::HandleScope scope(args.GetIsolate());

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
			v8::Local<v8::Value> jsDate(v8::Date::New(args.GetIsolate(), millis));
			args.GetReturnValue().Set(jsDate);
		}
		break;
	case Poco::Data::MetaColumn::FDT_DATE:
		{
			Poco::Data::Date date = value.extract<Poco::Data::Date>();
			Poco::DateTime dt(date.year(), date.month(), date.day());
			double millis = dt.timestamp().epochMicroseconds()/1000.0;
			v8::Local<v8::Value> jsDate(v8::Date::New(args.GetIsolate(), millis));
			args.GetReturnValue().Set(jsDate);
		}
		break;
	case Poco::Data::MetaColumn::FDT_TIME:
		{
			Poco::DateTime now;
			Poco::Data::Time time = value.extract<Poco::Data::Time>();
			Poco::DateTime dt(now.year(), now.month(), now.day(), time.hour(), time.minute(), time.second());
			double millis = dt.timestamp().epochMicroseconds()/1000.0;
			v8::Local<v8::Value> jsDate(v8::Date::New(args.GetIsolate(), millis));
			args.GetReturnValue().Set(jsDate);
		}
		break;
	case Poco::Data::MetaColumn::FDT_BLOB:
	case Poco::Data::MetaColumn::FDT_CLOB:
	case Poco::Data::MetaColumn::FDT_WSTRING:
	case Poco::Data::MetaColumn::FDT_UNKNOWN:
	default:
		returnException(args, std::string("cannot convert value"));
		break;
	}
}


} } } // namespace Poco::JS::Data
