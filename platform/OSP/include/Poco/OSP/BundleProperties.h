//
// BundleProperties.h
//
// $Id: //poco/1.7/OSP/include/Poco/OSP/BundleProperties.h#1 $
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
// SPDX-License-Identifier: Apache-2.0
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
	typedef Poco::AutoPtr<BundleProperties> Ptr;

	BundleProperties();
		/// Creates the BundleProperties.

	void addProperties(Poco::Util::AbstractConfiguration* pConfig, bool shared);
		/// Adds a configuration.
		///
		/// If shared is true, increments the configuration's reference count.
		
	void addProperties(Poco::Util::AbstractConfiguration* pConfig, int priority, bool shared);
		/// Adds a configuration with the given priority.
		///
		/// If shared is true, increments the configuration's reference count.
		
	void removeProperties(Poco::Util::AbstractConfiguration* pConfig);
		/// Removes the given configuration.

protected:
	~BundleProperties();

	bool getRaw(const std::string& key, std::string& value) const;
	void setRaw(const std::string& key, const std::string& value);
	void enumerate(const std::string& key, Keys& range) const;
	void removeRaw(const std::string& key);

	Poco::Util::LayeredConfiguration* _pLayeredConfig;
	mutable Poco::FastMutex _mutex;
};


} } // namespace Poco::OSP


#endif // OSP_BundleProperties_INCLUDED
