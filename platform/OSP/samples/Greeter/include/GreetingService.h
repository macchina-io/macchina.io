//
// GreetingService.cpp
//
// Definition of the GreetingService class.
//
// Copyright (c) 2007-2016, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef GreetingService_INCLUDED
#define GreetingService_INCLUDED


#include "Poco/OSP/Service.h"
#include "Poco/AutoPtr.h"


class GreetingService: public Poco::OSP::Service
	/// This is an example for a very simple
	/// OSP service.
	///
	/// The service is available under the name
	/// "com.appinf.osp.samples.GreetingService".
{
public:
	using Ptr = Poco::AutoPtr<GreetingService>;

	virtual std::string greeting() = 0;
		/// Return a greeting in the user's language, if the
		/// language is known, or in English otherwise.
};


#endif // GreetingService_INCLUDED
