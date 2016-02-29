//
// BundleFactory.h
//
// $Id: //poco/1.7/OSP/include/Poco/OSP/BundleFactory.h#1 $
//
// Library: OSP
// Package: Bundle
// Module:  BundleFactory
//
// Definition of the BundleFactory class.
//
// Copyright (c) 2007-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef OSP_BundleFactory_INCLUDED
#define OSP_BundleFactory_INCLUDED


#include "Poco/OSP/OSP.h"
#include "Poco/OSP/LanguageTag.h"
#include "Poco/RefCountedObject.h"
#include "Poco/AutoPtr.h"


namespace Poco {
namespace OSP {


class Bundle;
class BundleLoader;


class OSP_API BundleFactory: public Poco::RefCountedObject
	/// A factory class for Bundle objects,
	/// used by the BundleLoader.
{
public:
	typedef Poco::AutoPtr<BundleFactory> Ptr;
	typedef const Ptr ConstPtr;

	BundleFactory(const LanguageTag& language);
		/// Creates the BundleFactory.
		
	virtual Bundle* createBundle(BundleLoader& loader, const std::string& path);
		/// Creates and returns a new Bundle object for
		/// the bundle stored in the given path, using
		/// the given BundleLoader.

protected:
	~BundleFactory();
		/// Destroys the BundleFactory.

private:
	BundleFactory();

	LanguageTag _language;
};


} } // namespace Poco::OSP


#endif // OSP_BundleFactory_INCLUDED
