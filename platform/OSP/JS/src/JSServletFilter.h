//
// JSServletFilter.h
//
// $Id: //poco/1.4/OSP/JS/src/JSServletFilter.h#1 $
//
// Copyright (c) 2013-2014, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef OSP_JS_JSServletFilter_INCLUDED
#define OSP_JS_JSServletFilter_INCLUDED


#include "Poco/OSP/Web/WebFilter.h"
#include "Poco/OSP/Web/WebFilterFactory.h"
#include "Poco/Mutex.h"
#include "JSServletExecutor.h"


namespace Poco {
namespace OSP {
namespace JS {


class JSServletFilter: public Poco::OSP::Web::WebFilter
	/// A web filter for executing JavaScript servlets.
{
public:
	JSServletFilter(Poco::OSP::BundleContext::Ptr pContext, const Poco::OSP::Web::WebFilter::Args& args);
		/// Creates the JSServletFilter using the given BundleContext.
	
	// Poco::OSP::Web::WebFilter
	void process(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response, const std::string& path, std::istream& resourceStream, Poco::OSP::Bundle::ConstPtr pBundle);

protected:
	virtual void preprocess(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response, const std::string& uri, std::istream& resourceStream, std::string& servlet);
	Poco::OSP::BundleContext::Ptr context() const;
	void sendErrorResponse(Poco::Net::HTTPServerResponse& response, const std::string& message); 
		
private:
	BundleContext::Ptr _pContext;
	Poco::UInt64 _memoryLimit;
	JSServletExecutor::Ptr _pServletExecutor;
	Poco::FastMutex _mutex;
};


class JSServletFilterFactory: public Poco::OSP::Web::WebFilterFactory
	/// The factory for JSServletFilter.
{
public:
	Poco::OSP::Web::WebFilter* createFilter(const Poco::OSP::Web::WebFilter::Args& args)
	{
		return new JSServletFilter(context(), args);
	}
};


//
// inlines
//
inline Poco::OSP::BundleContext::Ptr JSServletFilter::context() const
{
	return _pContext;
}


} } } // namespace Poco::OSP::JS


#endif // OSP_JS_JSServletFilter_INCLUDED
