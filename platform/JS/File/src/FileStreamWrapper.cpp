//
// FileStreamWrapper.cpp
//
// Library: JS/File
// Package: Wrappers
// Module:  FileStreamWrapper
//
// Definition of the FileWrapper class.
//
// Copyright (c) 2023, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#include "Poco/JS/File/FileStreamWrapper.h"
#include "Poco/JS/Core/PooledIsolate.h"
#include "Poco/JS/Core/BufferWrapper.h"
#include <limits>


using namespace std::string_literals;


namespace Poco {
namespace JS {
namespace File {


FileStreamWrapper::FileStreamWrapper()
{
}


FileStreamWrapper::~FileStreamWrapper()
{
}


v8::Handle<v8::ObjectTemplate> FileStreamWrapper::objectTemplate(v8::Isolate* pIsolate)
{
	v8::EscapableHandleScope handleScope(pIsolate);
	Poco::JS::Core::PooledIsolate* pPooledIso = Poco::JS::Core::PooledIsolate::fromIsolate(pIsolate);
	poco_check_ptr (pPooledIso);
	v8::Persistent<v8::ObjectTemplate>& pooledObjectTemplate(pPooledIso->objectTemplate("File.FileStream"s));
	if (pooledObjectTemplate.IsEmpty())
	{
		v8::Handle<v8::ObjectTemplate> objectTemplate = v8::ObjectTemplate::New(pIsolate);
		objectTemplate->SetInternalFieldCount(1);
		objectTemplate->SetAccessor(toV8Internalized(pIsolate, "readable"s), getReadable);
		objectTemplate->SetAccessor(toV8Internalized(pIsolate, "writable"s), getWritable);
		objectTemplate->SetAccessor(toV8Internalized(pIsolate, "good"s), getGood);
		objectTemplate->SetAccessor(toV8Internalized(pIsolate, "eof"s), getEOF);
		objectTemplate->SetAccessor(toV8Internalized(pIsolate, "lineEnding"s), getLineEnding, setLineEnding);

		objectTemplate->Set(toV8Internalized(pIsolate, "tell"s), v8::FunctionTemplate::New(pIsolate, tell));
		objectTemplate->Set(toV8Internalized(pIsolate, "seek"s), v8::FunctionTemplate::New(pIsolate, seek));
		objectTemplate->Set(toV8Internalized(pIsolate, "readln"s), v8::FunctionTemplate::New(pIsolate, readln));
		objectTemplate->Set(toV8Internalized(pIsolate, "writeln"s), v8::FunctionTemplate::New(pIsolate, writeln));
		objectTemplate->Set(toV8Internalized(pIsolate, "read"s), v8::FunctionTemplate::New(pIsolate, read));
		objectTemplate->Set(toV8Internalized(pIsolate, "write"s), v8::FunctionTemplate::New(pIsolate, write));
		objectTemplate->Set(toV8Internalized(pIsolate, "peekByte"s), v8::FunctionTemplate::New(pIsolate, peekByte));
		objectTemplate->Set(toV8Internalized(pIsolate, "readByte"s), v8::FunctionTemplate::New(pIsolate, readByte));
		objectTemplate->Set(toV8Internalized(pIsolate, "writeByte"s), v8::FunctionTemplate::New(pIsolate, writeByte));
		objectTemplate->Set(toV8Internalized(pIsolate, "reset"s), v8::FunctionTemplate::New(pIsolate, reset));
		objectTemplate->Set(toV8Internalized(pIsolate, "flush"s), v8::FunctionTemplate::New(pIsolate, flush));
		objectTemplate->Set(toV8Internalized(pIsolate, "close"s), v8::FunctionTemplate::New(pIsolate, close));
		pooledObjectTemplate.Reset(pIsolate, objectTemplate);
	}
	v8::Local<v8::ObjectTemplate> fileTemplate = v8::Local<v8::ObjectTemplate>::New(pIsolate, pooledObjectTemplate);
	return handleScope.Escape(fileTemplate);
}


void FileStreamWrapper::getReadable(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info)
{
	FileStreamHolder* pHolder = Poco::JS::Core::Wrapper::unwrapNative<FileStreamHolder>(info);
	info.GetReturnValue().Set((pHolder->mode() & std::ios::in) != 0);
}


void FileStreamWrapper::getWritable(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info)
{
	FileStreamHolder* pHolder = Poco::JS::Core::Wrapper::unwrapNative<FileStreamHolder>(info);
	info.GetReturnValue().Set((pHolder->mode() & std::ios::out) != 0);
}


void FileStreamWrapper::getGood(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info)
{
	FileStreamHolder* pHolder = Poco::JS::Core::Wrapper::unwrapNative<FileStreamHolder>(info);
	info.GetReturnValue().Set(pHolder->stream().good());
}


void FileStreamWrapper::getEOF(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info)
{
	FileStreamHolder* pHolder = Poco::JS::Core::Wrapper::unwrapNative<FileStreamHolder>(info);
	info.GetReturnValue().Set(pHolder->stream().eof());
}


void FileStreamWrapper::getLineEnding(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info)
{
	FileStreamHolder* pHolder = Poco::JS::Core::Wrapper::unwrapNative<FileStreamHolder>(info);
	returnString(info, pHolder->getLineEnding());
}


void FileStreamWrapper::setLineEnding(v8::Local<v8::String> name, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void>& info)
{
	v8::Isolate* pIsolate(info.GetIsolate());
	v8::HandleScope scope(pIsolate);

	FileStreamHolder* pHolder = Poco::JS::Core::Wrapper::unwrapNative<FileStreamHolder>(info);
	std::string lineEnding = toString(pIsolate, value);

	if (lineEnding == Poco::LineEnding::NEWLINE_LF || lineEnding == Poco::LineEnding::NEWLINE_CRLF)
	{
		pHolder->setLineEnding(lineEnding);
	}
	else
	{
		returnException(info, "Invalid line ending specified. Must be NEWLINE_LF or NEWLINE_CRLF."s);
	}
}


void FileStreamWrapper::tell(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	FileStreamHolder* pHolder = Poco::JS::Core::Wrapper::unwrapNative<FileStreamHolder>(args);
	std::streamoff off = (pHolder->mode() & std::ios::in) != 0 ? pHolder->stream().tellg() : pHolder->stream().tellp();
	if (off <= std::numeric_limits<std::int32_t>::max())
		args.GetReturnValue().Set(static_cast<std::int32_t>(off));
	else
		args.GetReturnValue().Set(static_cast<double>(off));
}


void FileStreamWrapper::seek(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	v8::Isolate* pIsolate(args.GetIsolate());
	v8::HandleScope scope(pIsolate);
	v8::Local<v8::Context> context(pIsolate->GetCurrentContext());

	FileStreamHolder* pHolder = Poco::JS::Core::Wrapper::unwrapNative<FileStreamHolder>(args);
	std::streamoff off = 0;
	std::ios::seekdir dir = std::ios::beg;
	if (args.Length() > 0)
	{
		if (args[0]->IsInt32())
		{
			off = args[0]->Int32Value(context).FromMaybe(0);
		}
		else if (args[0]->IsUint32())
		{
			off = args[0]->Uint32Value(context).FromMaybe(0);
		}
		else
		{
			off = static_cast<std::streamoff>(args[0]->NumberValue(context).FromMaybe(0.0));
		}
		if (args.Length() > 1)
		{
			int n = args[1]->Int32Value(context).FromMaybe(0);
			switch (n)
			{
			case SEEK_DIR_BEG:
				dir = std::ios::beg;
				break;
			case SEEK_DIR_CUR:
				dir = std::ios::cur;
				break;
			case SEEK_DIR_END:
				dir = std::ios::end;
				break;
			}
		}
	}

	if (pHolder->mode() & std::ios::in)
	{
		pHolder->stream().seekg(off, dir);
	}
	if (pHolder->mode() & std::ios::out)
	{
		pHolder->stream().seekp(off, dir);
	}
}


void FileStreamWrapper::readln(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	v8::Isolate* pIsolate(args.GetIsolate());
	v8::HandleScope scope(pIsolate);

	FileStreamHolder* pHolder = Poco::JS::Core::Wrapper::unwrapNative<FileStreamHolder>(args);
	std::string line;
	std::getline(pHolder->stream(), line);
	if (line.size() > 0 && pHolder->getLineEnding()[0] == line[line.size() - 1]) // accounts for CRLF
	{
		line.resize(line.size() - 1);
	}
	returnString(args, line);
}


void FileStreamWrapper::writeln(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	v8::Isolate* pIsolate(args.GetIsolate());

	FileStreamHolder* pHolder = Poco::JS::Core::Wrapper::unwrapNative<FileStreamHolder>(args);
	std::string line;
	if (args.Length() > 0)
	{
		line = toString(pIsolate, args[0]);
	}
	line += pHolder->getLineEnding();
	pHolder->stream().write(line.data(), static_cast<std::streamsize>(line.size()));
}


void FileStreamWrapper::read(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	v8::Isolate* pIsolate(args.GetIsolate());
	v8::HandleScope scope(pIsolate);
	v8::Local<v8::Context> context(pIsolate->GetCurrentContext());

	std::streamsize n = 0;
	if (args.Length() > 0)
	{
		n = args[0]->Int32Value(context).FromMaybe(0);
	}
	
	FileStreamHolder* pHolder = Poco::JS::Core::Wrapper::unwrapNative<FileStreamHolder>(args);

	std::unique_ptr<Poco::JS::Core::BufferWrapper::Buffer> pBuffer = std::make_unique<Poco::JS::Core::BufferWrapper::Buffer>(n);

	std::streamsize read = pHolder->stream().read(pBuffer->begin(), n).gcount();
	pBuffer->resize(read);

	Poco::JS::Core::BufferWrapper wrapper;
	v8::Persistent<v8::Object>& bufferObject(wrapper.wrapNativePersistent(pIsolate, pBuffer.release()));
	args.GetReturnValue().Set(v8::Local<v8::Object>::New(pIsolate, bufferObject));
}


void FileStreamWrapper::write(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	v8::Isolate* pIsolate(args.GetIsolate());

	FileStreamHolder* pHolder = Poco::JS::Core::Wrapper::unwrapNative<FileStreamHolder>(args);

	if (args.Length() > 0)
	{
		if (Poco::JS::Core::Wrapper::isWrapper<Poco::JS::Core::BufferWrapper::Buffer>(args.GetIsolate(), args[0]))
		{
			Poco::JS::Core::BufferWrapper::Buffer* pBuffer = Poco::JS::Core::Wrapper::unwrapNativeObject<Poco::JS::Core::BufferWrapper::Buffer>(args[0]);
			pHolder->stream().write(pBuffer->begin(), pBuffer->size());
		}
		else
		{
			std::string str = toString(pIsolate, args[0]);
			pHolder->stream().write(str.data(), str.size());
		}
	}
}


void FileStreamWrapper::peekByte(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	FileStreamHolder* pHolder = Poco::JS::Core::Wrapper::unwrapNative<FileStreamHolder>(args);
	int ch = pHolder->stream().peek();
	args.GetReturnValue().Set(ch);
}


void FileStreamWrapper::readByte(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	FileStreamHolder* pHolder = Poco::JS::Core::Wrapper::unwrapNative<FileStreamHolder>(args);
	int ch = pHolder->stream().get();
	args.GetReturnValue().Set(ch);
}


void FileStreamWrapper::writeByte(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	v8::Isolate* pIsolate(args.GetIsolate());
	v8::HandleScope scope(pIsolate);
	v8::Local<v8::Context> context(pIsolate->GetCurrentContext());

	FileStreamHolder* pHolder = Poco::JS::Core::Wrapper::unwrapNative<FileStreamHolder>(args);
	unsigned byte = args[0]->Uint32Value(context).FromMaybe(0);
	pHolder->stream().put(static_cast<char>(byte));
}


void FileStreamWrapper::reset(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	FileStreamHolder* pHolder = Poco::JS::Core::Wrapper::unwrapNative<FileStreamHolder>(args);
	pHolder->stream().clear();
	if (pHolder->mode() & std::ios::in)
	{
		pHolder->stream().seekg(0, std::ios::beg);
	}
	if (pHolder->mode() & std::ios::out)
	{
		pHolder->stream().seekp(0, std::ios::beg);
	}
}


void FileStreamWrapper::flush(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	FileStreamHolder* pHolder = Poco::JS::Core::Wrapper::unwrapNative<FileStreamHolder>(args);
	pHolder->stream().flush();
}


void FileStreamWrapper::close(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	FileStreamHolder* pHolder = Poco::JS::Core::Wrapper::unwrapNative<FileStreamHolder>(args);
	pHolder->stream().close();
}


} } } // namespace Poco::JS::File
