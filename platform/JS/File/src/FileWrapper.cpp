//
// FileWrapper.cpp
//
// Library: JS/File
// Package: Wrappers
// Module:  FileWrapper
//
// Copyright (c) 2023, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#include "Poco/JS/File/FileWrapper.h"
#include "Poco/JS/File/FileStreamWrapper.h"
#include "Poco/JS/Core/PooledIsolate.h"
#include "Poco/JS/Core/DateTimeWrapper.h"
#include "Poco/JS/Core/LocalDateTimeWrapper.h"
#include "Poco/File.h"
#include "Poco/Path.h"
#include "Poco/Glob.h"
#include "Poco/DirectoryIterator.h"
#include "Poco/FileStream.h"
#include "Poco/LineEndingConverter.h"
#include <cstddef>
#include <limits>


using namespace std::string_literals;


namespace Poco {
namespace JS {
namespace File {


FileWrapper::FileWrapper()
{
}


FileWrapper::~FileWrapper()
{
}


v8::Handle<v8::FunctionTemplate> FileWrapper::constructor(v8::Isolate* pIsolate)
{
	v8::EscapableHandleScope handleScope(pIsolate);
	v8::Local<v8::FunctionTemplate> funcTemplate = v8::FunctionTemplate::New(pIsolate, construct);
	funcTemplate->Set(toV8String(pIsolate, "isFile"s), v8::FunctionTemplate::New(pIsolate, isFileWrapper));
	funcTemplate->Set(toV8String(pIsolate, "roots"s), v8::FunctionTemplate::New(pIsolate, roots));
	funcTemplate->Set(toV8String(pIsolate, "glob"s), v8::FunctionTemplate::New(pIsolate, glob));
	funcTemplate->Set(toV8String(pIsolate, "concatPaths"s), v8::FunctionTemplate::New(pIsolate, concatPaths));
	funcTemplate->Set(toV8String(pIsolate, "resolvePath"s), v8::FunctionTemplate::New(pIsolate, resolvePath));
	funcTemplate->Set(toV8String(pIsolate, "currentDirectory"s), v8::FunctionTemplate::New(pIsolate, currentDirectory));
	funcTemplate->Set(toV8String(pIsolate, "GLOB_DOT_SPECIAL"s), v8::Int32::New(pIsolate, Poco::Glob::GLOB_DOT_SPECIAL));
	funcTemplate->Set(toV8String(pIsolate, "GLOB_FOLLOW_SYMLINKS"s), v8::Int32::New(pIsolate, Poco::Glob::GLOB_FOLLOW_SYMLINKS));
	funcTemplate->Set(toV8String(pIsolate, "GLOB_CASELESS"s), v8::Int32::New(pIsolate, Poco::Glob::GLOB_CASELESS));
	funcTemplate->Set(toV8String(pIsolate, "LINK_HARD"s), v8::False(pIsolate));
	funcTemplate->Set(toV8String(pIsolate, "LINK_SYMBOLIC"s), v8::True(pIsolate));
	funcTemplate->Set(toV8String(pIsolate, "OPT_FAIL_ON_OVERWRITE"s), v8::Int32::New(pIsolate, Poco::File::OPT_FAIL_ON_OVERWRITE));
	funcTemplate->Set(toV8String(pIsolate, "OPEN_READ"s), v8::Int32::New(pIsolate, OPEN_READ));
	funcTemplate->Set(toV8String(pIsolate, "OPEN_WRITE"s), v8::Int32::New(pIsolate, OPEN_WRITE));
	funcTemplate->Set(toV8String(pIsolate, "OPEN_APPEND"s), v8::Int32::New(pIsolate, OPEN_APPEND));
	funcTemplate->Set(toV8String(pIsolate, "OPEN_ATEND"s), v8::Int32::New(pIsolate, OPEN_ATEND));
	funcTemplate->Set(toV8String(pIsolate, "OPEN_EXISTING"s), v8::Int32::New(pIsolate, OPEN_EXISTING));
	funcTemplate->Set(toV8String(pIsolate, "OPEN_NOREPLACE"s), v8::Int32::New(pIsolate, OPEN_NOREPLACE));
	funcTemplate->Set(toV8String(pIsolate, "OPEN_TRUNCATE"s), v8::Int32::New(pIsolate, OPEN_TRUNCATE));
	funcTemplate->Set(toV8String(pIsolate, "NEWLINE_CRLF"s), toV8String(pIsolate, Poco::LineEnding::NEWLINE_CRLF));
	funcTemplate->Set(toV8String(pIsolate, "NEWLINE_LF"s), toV8String(pIsolate, Poco::LineEnding::NEWLINE_LF));
	funcTemplate->Set(toV8String(pIsolate, "NEWLINE_DEFAULT"s), toV8String(pIsolate, Poco::LineEnding::NEWLINE_DEFAULT));
	funcTemplate->Set(toV8String(pIsolate, "SEEK_BEG"s), v8::Int32::New(pIsolate, FileStreamWrapper::SEEK_DIR_BEG));
	funcTemplate->Set(toV8String(pIsolate, "SEEK_CUR"s), v8::Int32::New(pIsolate, FileStreamWrapper::SEEK_DIR_CUR));
	funcTemplate->Set(toV8String(pIsolate, "SEEK_END"s), v8::Int32::New(pIsolate, FileStreamWrapper::SEEK_DIR_END));
	funcTemplate->Set(toV8String(pIsolate, "EOF"s), v8::Int32::New(pIsolate, -1));
	funcTemplate->Set(toV8String(pIsolate, "PATH_SEPARATOR"s), toV8String(pIsolate, std::string(1, Poco::Path::separator())));
	return handleScope.Escape(funcTemplate);
}


v8::Handle<v8::ObjectTemplate> FileWrapper::objectTemplate(v8::Isolate* pIsolate)
{
	v8::EscapableHandleScope handleScope(pIsolate);
	Poco::JS::Core::PooledIsolate* pPooledIso = Poco::JS::Core::PooledIsolate::fromIsolate(pIsolate);
	poco_check_ptr (pPooledIso);
	v8::Persistent<v8::ObjectTemplate>& pooledObjectTemplate(pPooledIso->objectTemplate("File.File"s));
	if (pooledObjectTemplate.IsEmpty())
	{
		v8::Handle<v8::ObjectTemplate> objectTemplate = v8::ObjectTemplate::New(pIsolate);
		objectTemplate->SetInternalFieldCount(1);
		objectTemplate->SetAccessor(toV8Internalized(pIsolate, "exists"s), getExists);
		objectTemplate->SetAccessor(toV8Internalized(pIsolate, "lastModified"s), getLastModified, setLastModified);
		objectTemplate->SetAccessor(toV8Internalized(pIsolate, "created"s), getCreated);
		objectTemplate->SetAccessor(toV8Internalized(pIsolate, "size"s), getSize, setSize);
		objectTemplate->SetAccessor(toV8Internalized(pIsolate, "path"s), getPath);
		objectTemplate->SetAccessor(toV8Internalized(pIsolate, "absolutePath"s), getAbsolutePath);
		objectTemplate->SetAccessor(toV8Internalized(pIsolate, "name"s), getName);
		objectTemplate->SetAccessor(toV8Internalized(pIsolate, "baseName"s), getBaseName);
		objectTemplate->SetAccessor(toV8Internalized(pIsolate, "extension"s), getExtension);
		objectTemplate->SetAccessor(toV8Internalized(pIsolate, "parent"s), getParent);

		objectTemplate->Set(toV8Internalized(pIsolate, "toString"s), v8::FunctionTemplate::New(pIsolate, toString));
		objectTemplate->Set(toV8Internalized(pIsolate, "isFile"s), v8::FunctionTemplate::New(pIsolate, isFile));
		objectTemplate->Set(toV8Internalized(pIsolate, "isDirectory"s), v8::FunctionTemplate::New(pIsolate, isDirectory));
		objectTemplate->Set(toV8Internalized(pIsolate, "isDevice"s), v8::FunctionTemplate::New(pIsolate, isDevice));
		objectTemplate->Set(toV8Internalized(pIsolate, "isLink"s), v8::FunctionTemplate::New(pIsolate, isLink));
		objectTemplate->Set(toV8Internalized(pIsolate, "isHidden"s), v8::FunctionTemplate::New(pIsolate, isHidden));
		objectTemplate->Set(toV8Internalized(pIsolate, "canRead"s), v8::FunctionTemplate::New(pIsolate, canRead));
		objectTemplate->Set(toV8Internalized(pIsolate, "canWrite"s), v8::FunctionTemplate::New(pIsolate, canWrite));
		objectTemplate->Set(toV8Internalized(pIsolate, "canExecute"s), v8::FunctionTemplate::New(pIsolate, canExecute));
		objectTemplate->Set(toV8Internalized(pIsolate, "copyTo"s), v8::FunctionTemplate::New(pIsolate, copyTo));
		objectTemplate->Set(toV8Internalized(pIsolate, "moveTo"s), v8::FunctionTemplate::New(pIsolate, moveTo));
		objectTemplate->Set(toV8Internalized(pIsolate, "linkTo"s), v8::FunctionTemplate::New(pIsolate, linkTo));
		objectTemplate->Set(toV8Internalized(pIsolate, "renameTo"s), v8::FunctionTemplate::New(pIsolate, renameTo));
		objectTemplate->Set(toV8Internalized(pIsolate, "remove"s), v8::FunctionTemplate::New(pIsolate, remove));
		objectTemplate->Set(toV8Internalized(pIsolate, "list"s), v8::FunctionTemplate::New(pIsolate, list));
		objectTemplate->Set(toV8Internalized(pIsolate, "freeSpace"s), v8::FunctionTemplate::New(pIsolate, freeSpace));
		objectTemplate->Set(toV8Internalized(pIsolate, "totalSpace"s), v8::FunctionTemplate::New(pIsolate, totalSpace));
		objectTemplate->Set(toV8Internalized(pIsolate, "usableSpace"s), v8::FunctionTemplate::New(pIsolate, usableSpace));
		objectTemplate->Set(toV8Internalized(pIsolate, "open"s), v8::FunctionTemplate::New(pIsolate, open));
		objectTemplate->Set(toV8Internalized(pIsolate, "createFile"s), v8::FunctionTemplate::New(pIsolate, createFile));
		objectTemplate->Set(toV8Internalized(pIsolate, "createDirectory"s), v8::FunctionTemplate::New(pIsolate, createDirectory));
		objectTemplate->Set(toV8Internalized(pIsolate, "createDirectories"s), v8::FunctionTemplate::New(pIsolate, createDirectories));
		pooledObjectTemplate.Reset(pIsolate, objectTemplate);
	}
	v8::Local<v8::ObjectTemplate> fileTemplate = v8::Local<v8::ObjectTemplate>::New(pIsolate, pooledObjectTemplate);
	return handleScope.Escape(fileTemplate);
}


void FileWrapper::construct(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	v8::Isolate* pIsolate(args.GetIsolate());

	Poco::File* pFile = nullptr;
	try
	{
		if (args.Length() == 0)
		{
			returnException(args, "A path is required to create a file"s);
		}
		else
		{
			if (args[0]->IsString())
			{
				pFile = new Poco::File(Poco::JS::Core::Wrapper::toString(pIsolate, args[0]));
			}
			else
			{
				returnException(args, "Path argument must be a string"s);
			}
		}
		
		if (pFile)
		{
			FileWrapper wrapper;
			v8::Persistent<v8::Object>& fileObject(wrapper.wrapNativePersistent(pIsolate, pFile));
			args.GetReturnValue().Set(v8::Local<v8::Object>::New(pIsolate, fileObject));
		}
	}
	catch (Poco::Exception& exc)
	{
		delete pFile;
		returnException(args, exc);
	}
}


void FileWrapper::isFileWrapper(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	if (args.Length() > 0)
	{
		args.GetReturnValue().Set(Poco::JS::Core::Wrapper::isWrapper<Poco::File>(args.GetIsolate(), args[0]));
	}
	else
	{
		args.GetReturnValue().Set(false);
	}
}


void FileWrapper::getExists(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info)
{
	Poco::File* pFile = Poco::JS::Core::Wrapper::unwrapNative<Poco::File>(info);
	info.GetReturnValue().Set(pFile->exists());
}


void FileWrapper::getSize(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info)
{
	Poco::File* pFile = Poco::JS::Core::Wrapper::unwrapNative<Poco::File>(info);
	try
	{	
		const Poco::File::FileSize size = pFile->getSize();
		if (size <= std::numeric_limits<std::uint32_t>::max())
			info.GetReturnValue().Set(static_cast<std::uint32_t>(size));
		else
			info.GetReturnValue().Set(static_cast<double>(size));
	}
	catch (Poco::Exception& exc)
	{
		returnException(info, exc);
	}
}


void FileWrapper::setSize(v8::Local<v8::String> name, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void>& info)
{
	v8::Isolate* pIsolate(info.GetIsolate());
	v8::HandleScope scope(pIsolate);
	v8::Local<v8::Context> context(pIsolate->GetCurrentContext());

	Poco::File* pFile = Poco::JS::Core::Wrapper::unwrapNative<Poco::File>(info);
	Poco::File::FileSize size = 0;
	if (value->IsInt32())
	{
		size = value->Int32Value(context).FromMaybe(0);
	}
	else if (value->IsUint32())
	{
		size = value->Uint32Value(context).FromMaybe(0);
	}
	else
	{
		size = static_cast<Poco::File::FileSize>(value->NumberValue(context).FromMaybe(0.0));
	}
	try
	{
		pFile->setSize(size);
	}
	catch (Poco::Exception& exc)
	{
		returnException(info, exc);
	}
}


void FileWrapper::getLastModified(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info)
{
	v8::Isolate* pIsolate(info.GetIsolate());
	v8::HandleScope scope(pIsolate);
	v8::Local<v8::Context> context(pIsolate->GetCurrentContext());

	Poco::File* pFile = Poco::JS::Core::Wrapper::unwrapNative<Poco::File>(info);
	try
	{
		const Poco::Timestamp lastModified = pFile->getLastModified();

		double millis = lastModified.epochMicroseconds()/1000.0;
		v8::MaybeLocal<v8::Value> maybeJSDate(v8::Date::New(context, millis));
		v8::Local<v8::Value> jsDate;
		if (maybeJSDate.ToLocal(&jsDate))
		{
			info.GetReturnValue().Set(jsDate);
		}
	}
	catch (Poco::Exception& exc)
	{
		returnException(info, exc);
	}
}


void FileWrapper::setLastModified(v8::Local<v8::String> name, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void>& info)
{
	v8::Isolate* pIsolate(info.GetIsolate());
	v8::HandleScope scope(pIsolate);

	Poco::File* pFile = Poco::JS::Core::Wrapper::unwrapNative<Poco::File>(info);
	Poco::Timestamp lastModified;

	if (value->IsDate())
	{
		v8::Local<v8::Date> jsDate = v8::Local<v8::Date>::Cast(value);
		double millis = jsDate->ValueOf();
		lastModified = static_cast<Poco::Timestamp::TimeVal>(millis*1000);
	}
	else if (Poco::JS::Core::Wrapper::isWrapper<Poco::DateTime>(pIsolate, value))
	{
		Poco::DateTime* pDateTime = Poco::JS::Core::Wrapper::unwrapNativeObject<Poco::DateTime>(value);
		if (pDateTime)
		{
			lastModified = pDateTime->timestamp();
		}
	}
	else if (Poco::JS::Core::Wrapper::isWrapper<Poco::LocalDateTime>(pIsolate, value))
	{
		Poco::LocalDateTime* pLocalDateTime = Poco::JS::Core::Wrapper::unwrapNativeObject<Poco::LocalDateTime>(value);
		if (pLocalDateTime)
		{
			lastModified = pLocalDateTime->timestamp();
		}
	}
	else
	{
		returnException(info, "Argument to setLastModified must be Date, DateTime or LocalDateTime"s);
		return;
	}

	try
	{
		pFile->setLastModified(lastModified);
	}
	catch (Poco::Exception& exc)
	{
		returnException(info, exc);
	}
}


void FileWrapper::getCreated(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info)
{
	v8::Isolate* pIsolate(info.GetIsolate());
	v8::HandleScope scope(pIsolate);
	v8::Local<v8::Context> context(pIsolate->GetCurrentContext());

	Poco::File* pFile = Poco::JS::Core::Wrapper::unwrapNative<Poco::File>(info);
	try
	{
		const Poco::Timestamp created = pFile->created();
		double millis = created.epochMicroseconds()/1000.0;
		v8::MaybeLocal<v8::Value> maybeJSDate(v8::Date::New(context, millis));
		v8::Local<v8::Value> jsDate;
		if (maybeJSDate.ToLocal(&jsDate))
		{
			info.GetReturnValue().Set(jsDate);
		}
	}
	catch (Poco::Exception& exc)
	{
		returnException(info, exc);
	}
}


void FileWrapper::getPath(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info)
{
	Poco::File* pFile = Poco::JS::Core::Wrapper::unwrapNative<Poco::File>(info);
	returnString(info, pFile->path());
}


void FileWrapper::getAbsolutePath(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info)
{
	Poco::File* pFile = Poco::JS::Core::Wrapper::unwrapNative<Poco::File>(info);
	try
	{
		Poco::Path path(pFile->path());
		path.makeAbsolute();
		returnString(info, path.toString());
	}
	catch (Poco::Exception& exc)
	{
		returnException(info, exc);
	}
}


void FileWrapper::getName(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info)
{
	Poco::File* pFile = Poco::JS::Core::Wrapper::unwrapNative<Poco::File>(info);
	try
	{
		Poco::Path path(pFile->path());
		returnString(info, path.getFileName());
	}
	catch (Poco::Exception& exc)
	{
		returnException(info, exc);
	}
}


void FileWrapper::getBaseName(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info)
{
	Poco::File* pFile = Poco::JS::Core::Wrapper::unwrapNative<Poco::File>(info);
	try
	{
		Poco::Path path(pFile->path());
		returnString(info, path.getBaseName());
	}
	catch (Poco::Exception& exc)
	{
		returnException(info, exc);
	}
}


void FileWrapper::getExtension(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info)
{
	Poco::File* pFile = Poco::JS::Core::Wrapper::unwrapNative<Poco::File>(info);
	try
	{
		Poco::Path path(pFile->path());
		returnString(info, path.getExtension());
	}
	catch (Poco::Exception& exc)
	{
		returnException(info, exc);
	}
}


void FileWrapper::getParent(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info)
{
	Poco::File* pFile = Poco::JS::Core::Wrapper::unwrapNative<Poco::File>(info);
	try
	{
		Poco::Path path(pFile->path());
		path.makeAbsolute();
		returnString(info, path.parent().toString());
	}
	catch (Poco::Exception& exc)
	{
		returnException(info, exc);
	}
}


void FileWrapper::toString(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	Poco::File* pFile = Poco::JS::Core::Wrapper::unwrapNative<Poco::File>(args);
	returnString(args, pFile->path());
}


void FileWrapper::isFile(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	try
	{
		Poco::File* pFile = Poco::JS::Core::Wrapper::unwrapNative<Poco::File>(args);
		args.GetReturnValue().Set(pFile->isFile());
	}
	catch (Poco::Exception& exc)
	{
		returnException(args, exc);
	}
}


void FileWrapper::isDirectory(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	try
	{
		Poco::File* pFile = Poco::JS::Core::Wrapper::unwrapNative<Poco::File>(args);
		args.GetReturnValue().Set(pFile->isDirectory());
	}
	catch (Poco::Exception& exc)
	{
		returnException(args, exc);
	}
}


void FileWrapper::isDevice(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	try
	{
		Poco::File* pFile = Poco::JS::Core::Wrapper::unwrapNative<Poco::File>(args);
		args.GetReturnValue().Set(pFile->isDevice());
	}
	catch (Poco::Exception& exc)
	{
		returnException(args, exc);
	}
}


void FileWrapper::isLink(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	try
	{
		Poco::File* pFile = Poco::JS::Core::Wrapper::unwrapNative<Poco::File>(args);
		args.GetReturnValue().Set(pFile->isLink());
	}
	catch (Poco::Exception& exc)
	{
		returnException(args, exc);
	}
}


void FileWrapper::isHidden(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	try
	{
		Poco::File* pFile = Poco::JS::Core::Wrapper::unwrapNative<Poco::File>(args);
		args.GetReturnValue().Set(pFile->isHidden());
	}
	catch (Poco::Exception& exc)
	{
		returnException(args, exc);
	}
}


void FileWrapper::canRead(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	try
	{
		Poco::File* pFile = Poco::JS::Core::Wrapper::unwrapNative<Poco::File>(args);
		args.GetReturnValue().Set(pFile->canRead());
	}
	catch (Poco::Exception& exc)
	{
		returnException(args, exc);
	}
}


void FileWrapper::canWrite(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	try
	{
		Poco::File* pFile = Poco::JS::Core::Wrapper::unwrapNative<Poco::File>(args);
		args.GetReturnValue().Set(pFile->canWrite());
	}
	catch (Poco::Exception& exc)
	{
		returnException(args, exc);
	}
}


void FileWrapper::canExecute(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	try
	{
		Poco::File* pFile = Poco::JS::Core::Wrapper::unwrapNative<Poco::File>(args);
		args.GetReturnValue().Set(pFile->canExecute());
	}
	catch (Poco::Exception& exc)
	{
		returnException(args, exc);
	}
}


void FileWrapper::copyTo(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	v8::Isolate* pIsolate(args.GetIsolate());
	v8::HandleScope scope(pIsolate);
	v8::Local<v8::Context> context(pIsolate->GetCurrentContext());

	if (args.Length() > 0)
	{
		try
		{
			Poco::File* pFile = Poco::JS::Core::Wrapper::unwrapNative<Poco::File>(args);
			std::string target = Poco::JS::Core::Wrapper::toString(args.GetIsolate(), args[0]);
			int options = args.Length() > 1 ? args[1]->Int32Value(context).FromMaybe(0) : 0;
			pFile->copyTo(target, options);
		}
		catch (Poco::Exception& exc)
		{
			returnException(args, exc);
		}
	}
}


void FileWrapper::moveTo(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	v8::Isolate* pIsolate(args.GetIsolate());
	v8::HandleScope scope(pIsolate);
	v8::Local<v8::Context> context(pIsolate->GetCurrentContext());

	if (args.Length() > 0)
	{
		try
		{
			Poco::File* pFile = Poco::JS::Core::Wrapper::unwrapNative<Poco::File>(args);
			std::string target = Poco::JS::Core::Wrapper::toString(args.GetIsolate(), args[0]);
			int options = args.Length() > 1 ? args[1]->Int32Value(context).FromMaybe(0) : 0;
			pFile->moveTo(target, options);
		}
		catch (Poco::Exception& exc)
		{
			returnException(args, exc);
		}
	}
}


void FileWrapper::linkTo(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	v8::Isolate* pIsolate(args.GetIsolate());
	v8::HandleScope scope(pIsolate);

	if (args.Length() > 0)
	{
		try
		{
			Poco::File* pFile = Poco::JS::Core::Wrapper::unwrapNative<Poco::File>(args);
			std::string target = Poco::JS::Core::Wrapper::toString(args.GetIsolate(), args[0]);
			bool symbolic = args.Length() > 1 ? args[1]->BooleanValue(pIsolate) : true;
			pFile->linkTo(target, symbolic ? Poco::File::LINK_SYMBOLIC : Poco::File::LINK_HARD);
		}
		catch (Poco::Exception& exc)
		{
			returnException(args, exc);
		}
	}
}


void FileWrapper::renameTo(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	v8::Isolate* pIsolate(args.GetIsolate());
	v8::HandleScope scope(pIsolate);
	v8::Local<v8::Context> context(pIsolate->GetCurrentContext());

	if (args.Length() > 0)
	{
		try
		{
			Poco::File* pFile = Poco::JS::Core::Wrapper::unwrapNative<Poco::File>(args);
			std::string target = Poco::JS::Core::Wrapper::toString(args.GetIsolate(), args[0]);
			int options = args.Length() > 1 ? args[1]->Int32Value(context).FromMaybe(0) : 0;
			pFile->renameTo(target, options);
		}
		catch (Poco::Exception& exc)
		{
			returnException(args, exc);
		}
	}
}


void FileWrapper::remove(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	v8::Isolate* pIsolate(args.GetIsolate());
	v8::HandleScope scope(pIsolate);

	try
	{
		Poco::File* pFile = Poco::JS::Core::Wrapper::unwrapNative<Poco::File>(args);
		bool recursive = args.Length() > 0 ? args[0]->BooleanValue(pIsolate) : false;
		pFile->remove(recursive);
	}
	catch (Poco::Exception& exc)
	{
		returnException(args, exc);
	}
}


void FileWrapper::list(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	v8::Isolate* pIsolate(args.GetIsolate());
	v8::HandleScope scope(pIsolate);
	v8::Local<v8::Context> context(pIsolate->GetCurrentContext());

	Poco::File* pFile = Poco::JS::Core::Wrapper::unwrapNative<Poco::File>(args);
	std::vector<Poco::File> files;
	try
	{
		std::vector<std::string> patterns;
		if (args.Length() > 0)
		{
			for (int i = 0; i < args.Length(); i++)
			{
				patterns.push_back(Poco::JS::Core::Wrapper::toString(pIsolate, args[i]));
			}
		}

		if (patterns.empty())
		{
			pFile->list(files);
		}
		else
		{
			std::vector<std::unique_ptr<Poco::Glob>> globs;
			for (const auto& p: patterns)
			{
				globs.push_back(std::make_unique<Poco::Glob>(p));
			}
			Poco::DirectoryIterator it(*pFile);
			Poco::DirectoryIterator end;
			while (it != end)
			{
				bool match = false;
				for (const auto& g: globs)
				{
					if (g->match(it.name()))
					{
						match = true;
						break;
					}
				}
				if (match)
				{
					files.push_back(*it);
				}
				++it;
			}
		}

		v8::Local<v8::Array> filesArray = v8::Array::New(pIsolate, static_cast<int>(files.size()));
		if (!filesArray.IsEmpty())
		{
			for (unsigned i = 0; i < static_cast<unsigned>(files.size()); i++)
			{
				Poco::File* pListedFile = new Poco::File(files[i]);
				FileWrapper wrapper;
				v8::Persistent<v8::Object>& fileObject(wrapper.wrapNativePersistent(pIsolate, pListedFile));
				V8_CHECK_SET_RESULT(filesArray->Set(context, i, v8::Local<v8::Object>::New(pIsolate, fileObject)));
			}
		}
		args.GetReturnValue().Set(filesArray);
	}
	catch (Poco::Exception& exc)
	{
		returnException(args, exc);
	}
}


void FileWrapper::freeSpace(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	Poco::File* pFile = Poco::JS::Core::Wrapper::unwrapNative<Poco::File>(args);
	try
	{
		const Poco::File::FileSize size = pFile->freeSpace();
		if (size <= std::numeric_limits<std::uint32_t>::max())
			args.GetReturnValue().Set(static_cast<std::uint32_t>(size));
		else
			args.GetReturnValue().Set(static_cast<double>(size));
	}
	catch (Poco::Exception& exc)
	{
		returnException(args, exc);
	}
}


void FileWrapper::totalSpace(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	Poco::File* pFile = Poco::JS::Core::Wrapper::unwrapNative<Poco::File>(args);
	try
	{
		const Poco::File::FileSize size = pFile->totalSpace();
		if (size <= std::numeric_limits<std::uint32_t>::max())
			args.GetReturnValue().Set(static_cast<std::uint32_t>(size));
		else
			args.GetReturnValue().Set(static_cast<double>(size));
	}
	catch (Poco::Exception& exc)
	{
		returnException(args, exc);
	}
}


void FileWrapper::usableSpace(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	Poco::File* pFile = Poco::JS::Core::Wrapper::unwrapNative<Poco::File>(args);
	try
	{
		const Poco::File::FileSize size = pFile->usableSpace();
		if (size <= std::numeric_limits<std::uint32_t>::max())
			args.GetReturnValue().Set(static_cast<std::uint32_t>(size));
		else
			args.GetReturnValue().Set(static_cast<double>(size));
	}
	catch (Poco::Exception& exc)
	{
		returnException(args, exc);
	}
}


void FileWrapper::open(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	v8::Isolate* pIsolate(args.GetIsolate());
	v8::HandleScope scope(pIsolate);
	v8::Local<v8::Context> context(pIsolate->GetCurrentContext());

	Poco::File* pFile = Poco::JS::Core::Wrapper::unwrapNative<Poco::File>(args);

	int mode = 0;
	if (args.Length() > 0)
	{
		mode = args[0]->Int32Value(context).FromMaybe(0);
	}
	if (mode == 0)
	{
		mode = OPEN_READ | OPEN_EXISTING;
	}

	std::ios::openmode omode{};
	if (mode & OPEN_READ) 
		omode |= std::ios::in;
	if (mode & OPEN_WRITE)
		omode |= std::ios::out;
	if (mode & OPEN_APPEND)
		omode |= std::ios::app | std::ios::out;
	if (mode & OPEN_ATEND)
		omode |= std::ios::ate | std::ios::out;
	if (mode & OPEN_TRUNCATE)
		omode |= std::ios::trunc | std::ios::out;
	if (mode & OPEN_NOREPLACE)
		omode |= std::ios::out;
	if ((mode & OPEN_EXISTING) && (omode & std::ios::out) == 0)
		omode |= std::ios::in;
	
	try
	{
		if ((mode & OPEN_EXISTING) != 0 && !pFile->exists())
		{
			returnException(args, "Cannot open non-existing file: "s + pFile->path());
			return;
		}

		if ((mode & OPEN_NOREPLACE) != 0 && !pFile->createFile())
		{
			returnException(args, "File already exists and cannot be created with OPEN_NOREPLACE: "s + pFile->path());
			return;
		}

		std::unique_ptr<Poco::FileStream> pStream = std::make_unique<Poco::FileStream>(pFile->path(), omode);
		FileStreamHolder* pHolder = new FileStreamHolder(std::move(pStream), omode);

		FileStreamWrapper wrapper;
		v8::Persistent<v8::Object>& streamObject(wrapper.wrapNativePersistent(pIsolate, pHolder));
		args.GetReturnValue().Set(v8::Local<v8::Object>::New(pIsolate, streamObject));
	}
	catch (Poco::Exception& exc)
	{
		returnException(args, exc);
	}
}


void FileWrapper::createFile(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	Poco::File* pFile = Poco::JS::Core::Wrapper::unwrapNative<Poco::File>(args);
	try
	{
		bool created = pFile->createFile();
		args.GetReturnValue().Set(created);
	}
	catch (Poco::Exception& exc)
	{
		returnException(args, exc);
	}
}


void FileWrapper::createDirectory(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	Poco::File* pFile = Poco::JS::Core::Wrapper::unwrapNative<Poco::File>(args);
	try
	{
		bool created = pFile->createDirectory();
		args.GetReturnValue().Set(created);
	}
	catch (Poco::Exception& exc)
	{
		returnException(args, exc);
	}
}


void FileWrapper::createDirectories(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	Poco::File* pFile = Poco::JS::Core::Wrapper::unwrapNative<Poco::File>(args);
	try
	{
		pFile->createDirectories();
	}
	catch (Poco::Exception& exc)
	{
		returnException(args, exc);
	}
}


void FileWrapper::roots(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	v8::Isolate* pIsolate(args.GetIsolate());
	v8::HandleScope scope(pIsolate);
	v8::Local<v8::Context> context(pIsolate->GetCurrentContext());

	std::vector<std::string> roots;
	try
	{
		Poco::Path::listRoots(roots);

		v8::Local<v8::Array> rootsArray = v8::Array::New(pIsolate, static_cast<int>(roots.size()));
		if (!rootsArray.IsEmpty())
		{
			int i = 0;
			for (const auto& root: roots)
			{
				V8_CHECK_SET_RESULT(rootsArray->Set(context, i++, toV8String(pIsolate, root)));
			}
		}
		args.GetReturnValue().Set(rootsArray);
	}
	catch (Poco::Exception& exc)
	{
		returnException(args, exc);
	}
}


void FileWrapper::glob(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	v8::Isolate* pIsolate(args.GetIsolate());
	v8::HandleScope scope(pIsolate);
	v8::Local<v8::Context> context(pIsolate->GetCurrentContext());

	std::set<std::string> names;
	try
	{
		std::string pattern;
		if (args.Length() > 0)
		{
			pattern = Poco::JS::Core::Wrapper::toString(pIsolate, args[0]);
		}
		int options = args.Length() > 1 ? args[1]->Int32Value(context).FromMaybe(0) : 0;

		Poco::Glob::glob(pattern, names, options);

		v8::Local<v8::Array> namesArray = v8::Array::New(pIsolate, static_cast<int>(names.size()));
		if (!namesArray.IsEmpty())
		{
			int i = 0;
			for (const auto& name: names)
			{
				V8_CHECK_SET_RESULT(namesArray->Set(context, i++, toV8String(pIsolate, name)));
			}
		}
		args.GetReturnValue().Set(namesArray);
	}
	catch (Poco::Exception& exc)
	{
		returnException(args, exc);
	}
}


void FileWrapper::concatPaths(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	v8::Isolate* pIsolate(args.GetIsolate());

	try
	{
		if (args.Length() > 0)
		{
			Poco::Path p(Poco::JS::Core::Wrapper::toString(pIsolate, args[0]));
			for (int i = 1; i < args.Length(); i++)
			{
				p.append(Poco::JS::Core::Wrapper::toString(pIsolate, args[i]));
			}
			returnString(args, p.toString());
		}
	}
	catch (Poco::Exception& exc)
	{
		returnException(args, exc);
	}
}


void FileWrapper::resolvePath(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	v8::Isolate* pIsolate(args.GetIsolate());

	try
	{
		if (args.Length() > 0)
		{
			Poco::Path p(Poco::JS::Core::Wrapper::toString(pIsolate, args[0]));
			if (args.Length() > 1)
			{
				p.resolve(Poco::Path(Poco::JS::Core::Wrapper::toString(pIsolate, args[1])));
			}
			returnString(args, p.toString());
		}
	}
	catch (Poco::Exception& exc)
	{
		returnException(args, exc);
	}
}


void FileWrapper::currentDirectory(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	returnString(args, Poco::Path::current());
}


} } } // namespace Poco::JS::File
