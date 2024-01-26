//
// FileWrapper.h
//
// Library: JS/File
// Package: Wrappers
// Module:  FileWrapper
//
// Definition of the FileWrapper class.
//
// Copyright (c) 2023, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef JS_File_FileWrapper_INCLUDED
#define JS_File_FileWrapper_INCLUDED


#include "Poco/JS/File/File.h"
#include "Poco/JS/Core/Wrapper.h"
#include "Poco/File.h"


namespace Poco {
namespace JS {
namespace File {


class JSFile_API FileWrapper: public Poco::JS::Core::Wrapper
	/// JavaScript wrapper for Poco::File.
{
public:
	enum OpenMode
	{
		OPEN_READ      = 0x01,
		OPEN_WRITE     = 0x02,
		OPEN_APPEND    = 0x04,
		OPEN_ATEND     = 0x08,
		OPEN_EXISTING  = 0x10,
		OPEN_NOREPLACE = 0x20,
		OPEN_TRUNCATE  = 0x40
	};

	FileWrapper();
		/// Creates the FileWrapper.

	~FileWrapper();
		/// Destroys the FileWrapper.

	v8::Handle<v8::FunctionTemplate> constructor(v8::Isolate* pIsolate);
		/// Creates and returns a V8 FunctionTemplate for the constructor function.

	static void isFileWrapper(const v8::FunctionCallbackInfo<v8::Value>& args);
		/// Checks whether the given argument is a File.

	static void construct(const v8::FunctionCallbackInfo<v8::Value>& args);
		/// Creates a new FileWrapper.

	// Wrapper
	v8::Handle<v8::ObjectTemplate> objectTemplate(v8::Isolate* pIsolate);

protected:
	static void getExists(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info);
	static void getLastModified(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info);
	static void setLastModified(v8::Local<v8::String> name, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void>& info);
	static void getCreated(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info);
	static void getSize(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info);
	static void setSize(v8::Local<v8::String> name, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void>& info);
	static void getPath(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info);
	static void getAbsolutePath(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info);
	static void getName(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info);
	static void getBaseName(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info);
	static void getExtension(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info);
	static void getParent(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info);
	static void toString(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void isFile(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void isDirectory(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void isDevice(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void isLink(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void isHidden(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void canRead(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void canWrite(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void canExecute(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void copyTo(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void moveTo(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void linkTo(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void renameTo(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void remove(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void list(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void freeSpace(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void totalSpace(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void usableSpace(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void open(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void createFile(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void createDirectory(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void createDirectories(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void roots(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void glob(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void concatPaths(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void resolvePath(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void currentDirectory(const v8::FunctionCallbackInfo<v8::Value>& args);
};


} } } // namespace Poco::JS::File


#endif // JS_File_FileWrapper_INCLUDED
