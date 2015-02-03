//
// Wrapper.cpp
//
// $Id: //poco/1.4/JS/Core/src/Wrapper.cpp#4 $
//
// Library: JSCore
// Package: JSCore
// Module:  Wrapper
//
// Copyright (c) 2013-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#include "Poco/JS/Core/Wrapper.h"


namespace Poco {
namespace JS {
namespace Core {


Wrapper::Wrapper()
{
}


Wrapper::~Wrapper()
{
}


std::string Wrapper::toString(v8::Local<v8::Value> value)
{
	v8::String::Utf8Value utf8(value);
	return std::string(*utf8);
}


} } } // namespace Poco::JS::Core
