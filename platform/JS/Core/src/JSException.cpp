//
// JSException.cpp
//
// $Id$
//
// Library: JSCore
// Package: JSCore
// Module:  JSException
//
// Copyright (c) 2013-2016, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier:	Apache-2.0
//


#include "Poco/JS/Core/JSException.h"
#include <typeinfo>


namespace Poco {
namespace JS {
namespace Core {


POCO_IMPLEMENT_EXCEPTION(JSException, Poco::RuntimeException, "JavaScript Exception")
POCO_IMPLEMENT_EXCEPTION(ModuleNotFoundException, JSException, "JavaScript module not found")


} } } // namespace Poco::JS::Core
