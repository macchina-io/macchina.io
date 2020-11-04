//
// ModuleFactory.h
//
// Library: OSP/JS
// Package: Module
// Module:  ModuleFactory
//
// Definition of the ModuleFactory class.
//
// Copyright (c) 2016, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef OSP_JS_ModuleFactory_INCLUDED
#define OSP_JS_ModuleFactory_INCLUDED


#include "Poco/OSP/JS/JS.h"
#include "Poco/OSP/BundleContext.h"
#include "Poco/JS/Core/Module.h"


namespace Poco {
namespace OSP {
namespace JS {


class OSPJS_API ModuleFactory
	/// A factory for Poco::JS::Core::Module objects.
{
public:
	ModuleFactory();
		/// Creates the ModuleFactory.
		
	virtual ~ModuleFactory();
		/// Destroys the ModuleFactory.
		
	virtual Poco::JS::Core::Module* createModule() = 0;
		/// Create a Module object.

	void init(Poco::OSP::BundleContext::Ptr pContext);
		/// Initializes the factory with the given BundleContext.

	Poco::OSP::BundleContext::Ptr context() const;
		/// Returns the context. The pointer is guaranteed to be valid.

protected:	
	virtual void initImpl();
		/// Add extra initialization code by overriding this method in your subclass.

private:
	ModuleFactory(const ModuleFactory&);
	ModuleFactory& operator = (const ModuleFactory&);
	
	BundleContext::Ptr _pContext;
};


//
// inlines
//
inline Poco::OSP::BundleContext::Ptr ModuleFactory::context() const
{
	return _pContext;
}


} } } // namespace Poco::OSP::JS


#endif // OSP_JS_ModuleFactory_INCLUDED
