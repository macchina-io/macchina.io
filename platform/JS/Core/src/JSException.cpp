//
// JSException.cpp
//
// Library: JS/Core
// Package: Execution
// Module:  JSException
//
// Copyright (c) 2013-2016, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#include "Poco/JS/Core/JSException.h"
#include <typeinfo>


namespace Poco {
namespace JS {
namespace Core {


POCO_IMPLEMENT_EXCEPTION(JSException, Poco::RuntimeException, "JavaScript Exception")
POCO_IMPLEMENT_EXCEPTION(ModuleNotFoundException, JSException, "JavaScript module not found")


} } } // namespace Poco::JS::Core
