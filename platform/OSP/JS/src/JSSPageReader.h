//
// JSSPageReader.h
//
// $Id: //poco/1.4/OSP/JS/src/JSSPageReader.h#2 $
//
// Copyright (c) 2013-2014, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef OSP_JS_JSSPageReader_INCLUDED
#define OSP_JS_JSSPageReader_INCLUDED


#include "Poco/Poco.h"
#include <istream>
#include <ostream>
#include <sstream>


namespace Poco {
namespace OSP {
namespace JS {


class JSSPage;


class JSSPageReader
	/// This class implements the parser for reading page files
	/// containing JSP-style tags for embedding JavaScript code.
{
public:
	JSSPageReader(JSSPage& page, const std::string& path);
		/// Creates the JSSPageReader, using the given JSSPage.

	JSSPageReader(const JSSPageReader& parent, const std::string& path);
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
	static const std::string EXPR_END;

	void include(const std::string& path);
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
	std::string _path;
	std::string _attrs;
	int _line;
};


} } } // namespace Poco::OSP::JS


#endif // OSP_JS_JSSPageReader_INCLUDED
