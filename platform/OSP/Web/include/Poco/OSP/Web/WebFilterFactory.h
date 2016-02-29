//
// WebFilterFactory.h
//
// $Id: //poco/1.7/OSP/Web/include/Poco/OSP/Web/WebFilterFactory.h#1 $
//
// Library: OSP/Web
// Package: Web
// Module:  WebFilterFactory
//
// Definition of the WebFilterFactory class.
//
// Copyright (c) 2007-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef OSP_Web_WebFilterFactory_INCLUDED
#define OSP_Web_WebFilterFactory_INCLUDED


#include "Poco/OSP/Web/Web.h"
#include "Poco/OSP/Web/WebFilter.h"
#include "Poco/OSP/BundleContext.h"
#include <istream>


namespace Poco {
namespace OSP {
namespace Web {


class OSPWeb_API WebFilterFactory
	/// A factory for WebFilter objects.
{
public:	
	WebFilterFactory();
		/// Creates the WebFilterFactory. The default constructor is called
		/// by the classloader (which requires a default constructor) followed by a call to init.

	virtual ~WebFilterFactory();
		/// Destroys the WebFilterFactory.

	virtual WebFilter* createFilter(const WebFilter::Args& args) = 0;
		/// Creates a WebFilter using the given arguments.

	void init(BundleContext::Ptr pContext);
		/// Initializes the object with the given BundleContext.

protected:
	BundleContext::Ptr context() const;
		/// Returns the context. The pointer is guaranteed to be valid.

	virtual void initImpl();
		/// Add extra initialization code by overriding this method in your subclass.

private:
	BundleContext::Ptr _pContext;
};


//
// inlines
//
inline BundleContext::Ptr WebFilterFactory::context() const
{
	return _pContext;
}


} } } // namespace Poco::OSP::Web


#endif // OSP_Web_WebFilterFactory_INCLUDED
