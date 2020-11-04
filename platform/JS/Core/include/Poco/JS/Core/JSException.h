//
// JSException.h
//
// Library: JS/Core
// Package: Execution
// Module:  JSException
//
// Definition of the JSException class.
//
// Copyright (c) 2013-2016, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef JS_Core_JSException_INCLUDED
#define JS_Core_JSException_INCLUDED


#include "Poco/JS/Core/Core.h"
#include "Poco/Exception.h"


namespace Poco {
namespace JS {
namespace Core {


POCO_DECLARE_EXCEPTION(JSCore_API, JSException, Poco::RuntimeException)
POCO_DECLARE_EXCEPTION(JSCore_API, ModuleNotFoundException, JSException)


} } } // namespace Poco::JS::Core


#endif // JS_Core_JSException_INCLUDED
