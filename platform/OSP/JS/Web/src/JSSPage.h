//
// JSSPage.h
//
// Copyright (c) 2013-2016, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef OSP_JS_Web_JSSPage_INCLUDED
#define OSP_JS_Web_JSSPage_INCLUDED


#include "Poco/Net/NameValueCollection.h"
#include <sstream>


namespace Poco {
namespace OSP {
namespace JS {
namespace Web {


class JSSPage: public Poco::Net::NameValueCollection
	/// This class represents a server page consisting of
	/// handler code and declarations, as well as page attributes.
{
public:
	JSSPage();
		/// Creates a JSSPage.
	
	~JSSPage();
		/// Destroys the JSSPage.

	std::stringstream& handler();
		/// Returns the request handler code.

	const std::stringstream& handler() const;
		/// Returns the request prehandler code.

	bool getBool(const std::string& property, bool deflt = false) const;
		/// Returns the boolean value of the given property.
		///
		/// The return value will be true if the property
		/// has one of the following values:
		///    - true
		///    - yes
		///    - on
		///
		/// Otherwise, the return value will be false.
		
	int getInt(const std::string& property, int deflt = 0) const;
		/// Returns the integer value of the given property.
		
private:
	JSSPage(const JSSPage&);
	JSSPage& operator = (const JSSPage&);

	std::stringstream _handler;
};


//
// inlines
//
inline std::stringstream& JSSPage::handler()
{
	return _handler;
}


inline const std::stringstream& JSSPage::handler() const
{
	return _handler;
}


} } } } // namespace Poco::OSP::JS::Web


#endif // OSP_JS_Web_JSSPage_INCLUDED
