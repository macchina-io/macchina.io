//
// JSSPageReader.h
//
// Copyright (c) 2013-2016, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef OSP_JS_Web_JSSPageReader_INCLUDED
#define OSP_JS_Web_JSSPageReader_INCLUDED


#include "Poco/Poco.h"
#include <istream>
#include <ostream>
#include <sstream>


namespace Poco {
namespace OSP {
namespace JS {
namespace Web {


class JSSPage;


class JSSPageReader
	/// This class implements the parser for reading page files
	/// containing JSP-style tags for embedding JavaScript code.
{
public:
	JSSPageReader(JSSPage& page, const std::string& uri);
		/// Creates the JSSPageReader, using the given JSSPage.

	JSSPageReader(const JSSPageReader& parent, const std::string& uri);
		/// Creates the JSSPageReader, using the given JSSPageReader as parent.

	~JSSPageReader();
		/// Destroys the JSSPageReader.

	void parse(std::istream& pageStream);	
		/// Parses a HTML file containing server page directives,
		/// converts the file into JavaScript code and adds the code
		/// to the reader's JSSPage object. Also parses page
		/// attributes and include directives.

protected:
	enum ParsingState
	{
		STATE_MARKUP,
		STATE_BLOCK,
		STATE_EXPR,
		STATE_COMMENT,
		STATE_ATTR
	};

	static const std::string MARKUP_BEGIN;
	static const std::string MARKUP_END;
	static const std::string EXPR_BEGIN;
	static const std::string EXPR_HTML_BEGIN;
	static const std::string EXPR_END;

	void include(const std::string& uri);
	void parseAttributes();
	void nextToken(std::istream& istr, std::string& token);
	void handleAttribute(const std::string& name, const std::string& value);
	std::string where() const;

private:
	JSSPageReader();
	JSSPageReader(const JSSPageReader&);
	JSSPageReader& operator = (const JSSPageReader&);

	JSSPage& _page;
	const JSSPageReader* _pParent;
	std::string _uri;
	std::string _attrs;
	int _line;
};


} } } } // namespace Poco::OSP::JS::Web


#endif // OSP_JS_Web_JSSPageReader_INCLUDED
