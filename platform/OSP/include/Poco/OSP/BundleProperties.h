//
// BundleProperties.h
//
// Library: OSP
// Package: Bundle
// Module:  BundleProperties
//
// Definition of the BundleProperties class.
//
// Copyright (c) 2007-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef OSP_BundleProperties_INCLUDED
#define OSP_BundleProperties_INCLUDED


#include "Poco/OSP/OSP.h"
#include "Poco/Util/LayeredConfiguration.h"
#include "Poco/Mutex.h"


namespace Poco {
namespace OSP {


class OSP_API BundleProperties: public Poco::Util::AbstractConfiguration
	/// A simple wrapper class around Poco::Util::LayeredConfiguration
	/// that adds thread safety.
{
public:
	using Ptr = Poco::AutoPtr<BundleProperties>;

	BundleProperties();
		/// Creates the BundleProperties.

	void addProperties(Poco::Util::AbstractConfiguration::Ptr pConfig);
		/// Adds a configuration.
		///
		/// If shared is true, increments the configuration's reference count.

	void addProperties(Poco::Util::AbstractConfiguration::Ptr pConfig, int priority);
		/// Adds a configuration with the given priority.
		///
		/// If shared is true, increments the configuration's reference count.

	void removeProperties(Poco::Util::AbstractConfiguration::Ptr pConfig);
		/// Removes the given configuration.

protected:
	~BundleProperties();

	bool getRaw(const std::string& key, std::string& value) const;
	void setRaw(const std::string& key, const std::string& value);
	void enumerate(const std::string& key, Keys& range) const;
	void removeRaw(const std::string& key);

	Poco::Util::LayeredConfiguration::Ptr _pLayeredConfig;
	mutable Poco::FastMutex _mutex;
};


} } // namespace Poco::OSP


#endif // OSP_BundleProperties_INCLUDED
