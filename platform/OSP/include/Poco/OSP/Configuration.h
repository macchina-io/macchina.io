//
// Configuration.h
//
// Library: OSP
// Package: PreferencesService
// Module:  Configuration
//
// Definition of the Configuration class.
//
// Copyright (c) 2007-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef OSP_Configuration_INCLUDED
#define OSP_Configuration_INCLUDED


#include "Poco/OSP/OSP.h"
#include "Poco/Util/AbstractConfiguration.h"
#include "Poco/AutoPtr.h"


namespace Poco {
namespace OSP {


class OSP_API Configuration: public Poco::Util::AbstractConfiguration
	/// A simple wrapper class for Poco::Util::AbstractConfiguration,
	/// used by the PreferencesService.
{
public:
	using Ptr = Poco::AutoPtr<Configuration>;
	using ConstPtr = const Ptr;

	Configuration(Poco::Util::AbstractConfiguration* pConfig);
		/// Creates the Configuration.

protected:
	bool getRaw(const std::string& key, std::string& value) const;
	void setRaw(const std::string& key, const std::string& value);
	void enumerate(const std::string& key, Keys& range) const;
	void removeRaw(const std::string& key);
	~Configuration();

private:
	Configuration();

	AbstractConfiguration* _pConfig;
};


} } // namespace Poco::OSP


#endif // OSP_Configuration_INCLUDED
