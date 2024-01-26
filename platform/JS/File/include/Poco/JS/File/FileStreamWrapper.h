//
// FileStreamWrapper.h
//
// Library: JS/File
// Package: Wrappers
// Module:  FileStreamWrapper
//
// Definition of the FileStreamWrapper class.
//
// Copyright (c) 2023, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef JS_File_FileStreamWrapper_INCLUDED
#define JS_File_FileStreamWrapper_INCLUDED


#include "Poco/JS/File/File.h"
#include "Poco/JS/Core/Wrapper.h"
#include "Poco/FileStream.h"
#include "Poco/LineEndingConverter.h"
#include <memory>


namespace Poco {
namespace JS {
namespace File {


class JSFile_API FileStreamHolder
{
public:
	FileStreamHolder(std::unique_ptr<Poco::FileStream>&& pStream, std::ios::openmode mode):
		_pStream(std::move(pStream)),
		_mode(mode),
		_lineEnding(Poco::LineEnding::NEWLINE_LF)
	{
	}
	
	~FileStreamHolder()
	{
	}

	Poco::FileStream& stream()
	{
		return *_pStream;
	}

	const std::string& getLineEnding() const
	{
		return _lineEnding;
	}

	void setLineEnding(const std::string& lineEnding)
	{
		_lineEnding = lineEnding;
	}

	std::ios::openmode mode() const
	{
		return _mode;
	}

private:
	std::unique_ptr<Poco::FileStream> _pStream;
	std::ios::openmode _mode;
	std::string _lineEnding;
};


class JSFile_API FileStreamWrapper: public Poco::JS::Core::Wrapper
	/// JavaScript wrapper for Poco::File.
{
public:
	enum SeekDir
	{
		SEEK_DIR_BEG = 0,
		SEEK_DIR_CUR = 1,
		SEEK_DIR_END = 2
	};

	FileStreamWrapper();
		/// Creates the FileWrapper.

	~FileStreamWrapper();
		/// Destroys the FileWrapper.

	// Wrapper
	v8::Handle<v8::ObjectTemplate> objectTemplate(v8::Isolate* pIsolate);

protected:
	static void getReadable(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info);
	static void getWritable(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info);
	static void getGood(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info);
	static void getEOF(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info);
	static void getLineEnding(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info);
	static void setLineEnding(v8::Local<v8::String> name, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void>& info);
	static void tell(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void seek(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void readln(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void writeln(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void read(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void write(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void peekByte(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void readByte(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void writeByte(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void reset(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void flush(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void close(const v8::FunctionCallbackInfo<v8::Value>& args);
};


} } } // namespace Poco::JS::File


#endif // JS_File_FileStreamWrapper_INCLUDED
