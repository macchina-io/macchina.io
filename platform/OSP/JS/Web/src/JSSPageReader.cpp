//
// JSSPageReader.cpp
//
// Copyright (c) 2013-2016, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#include "JSSPageReader.h"
#include "JSSPage.h"
#include "Poco/URIStreamOpener.h"
#include "Poco/CountingStream.h"
#include "Poco/URI.h"
#include "Poco/Exception.h"
#include "Poco/Ascii.h"
#include "Poco/SharedPtr.h"


namespace Poco {
namespace OSP {
namespace JS {
namespace Web {


const std::string JSSPageReader::MARKUP_BEGIN("response.write(\"");
const std::string JSSPageReader::MARKUP_END("\");\n");
const std::string JSSPageReader::EXPR_BEGIN("response.write(");
const std::string JSSPageReader::EXPR_HTML_BEGIN("response.writeHTML(");
const std::string JSSPageReader::EXPR_END(");\n");


JSSPageReader::JSSPageReader(JSSPage& page, const std::string& uri):
	_page(page),
	_pParent(0),
	_uri(uri),
	_line(0)
{
	_attrs.reserve(4096);
}


JSSPageReader::JSSPageReader(const JSSPageReader& parent, const std::string& uri):
	_page(parent._page),
	_pParent(&parent),
	_uri(uri),
	_line(0)
{
	_attrs.reserve(4096);
}


JSSPageReader::~JSSPageReader()
{
}


void JSSPageReader::parse(std::istream& pageStream)
{
	ParsingState state = STATE_MARKUP;

	_page.handler() << MARKUP_BEGIN;

	Poco::CountingInputStream countingJSSPageStream(pageStream);
	std::string token;
	nextToken(countingJSSPageStream, token);
	while (!token.empty())
	{
		_line = countingJSSPageStream.getCurrentLineNumber();
		if (token == "<%")
		{
			if (state == STATE_MARKUP)
			{
				_page.handler() << MARKUP_END;
				state = STATE_BLOCK;
			}
			else _page.handler() << token;
		}
		else if (token == "<%--")
		{
			if (state == STATE_MARKUP)
			{
				_page.handler() << MARKUP_END;
				state = STATE_COMMENT;
			}
			else _page.handler() << token;
		}
		else if (token == "<%@")
		{
			if (state == STATE_MARKUP)
			{
				_page.handler() << MARKUP_END;
				state = STATE_ATTR;
				_attrs.clear();
			}
			else _page.handler() << token;
		}
		else if (token == "<%=")
		{
			if (state == STATE_MARKUP)
			{
				_page.handler() << MARKUP_END;
				_page.handler() << EXPR_HTML_BEGIN;
				state = STATE_EXPR;
			}
			else _page.handler() << token;
		}
		else if (token == "<%-")
		{
			if (state == STATE_MARKUP)
			{
				_page.handler() << MARKUP_END;
				_page.handler() << EXPR_BEGIN;
				state = STATE_EXPR;
			}
			else _page.handler() << token;
		}
		else if (token == "%>")
		{
			if (state == STATE_EXPR)
			{
				_page.handler() << EXPR_END;
				_page.handler() << MARKUP_BEGIN;
				state = STATE_MARKUP;
			}
			else if (state == STATE_ATTR)
			{
				parseAttributes();
				_attrs.clear();
				_page.handler() << MARKUP_BEGIN;
				state = STATE_MARKUP;
			}
			else if (state != STATE_MARKUP)
			{
				_page.handler() << MARKUP_BEGIN;
				state = STATE_MARKUP;
			}
			else _page.handler() << token;
		}
		else
		{
			switch (state)
			{
			case STATE_MARKUP:
				if (token == "\n")
				{
					_page.handler() << "\\n";
					_page.handler() << MARKUP_END;
					_page.handler() << MARKUP_BEGIN;
				}
				else if (token == "\t")
				{
					_page.handler() << "\\t";
				}
				else if (token == "\"")
				{
					_page.handler() << "\\\"";
				}
				else if (token != "\r")
				{
					_page.handler() << token;
				}
				break;
			case STATE_BLOCK:
				_page.handler() << token;
				break;
			case STATE_EXPR:
				_page.handler() << token;
				break;
			case STATE_COMMENT:
				break;
			case STATE_ATTR:
				_attrs += token;
				break;
			}
		}
		nextToken(countingJSSPageStream, token);
	}

	if (state == STATE_MARKUP)
	{
		_page.handler() << MARKUP_END;
	}
	else throw Poco::SyntaxException("Unclosed meta or code block", where());
}


void JSSPageReader::parseAttributes()
{
	static const int eof = std::char_traits<char>::eof();

	std::string basename;
	std::istringstream istr(_attrs);
	int ch = istr.get();
	while (ch != eof && Poco::Ascii::isSpace(ch)) ch = istr.get();
	while (ch != eof && Poco::Ascii::isAlphaNumeric(ch)) { basename += (char) ch; ch = istr.get(); }
	while (ch != eof && Poco::Ascii::isSpace(ch)) ch = istr.get();
	while (ch != eof)
	{
		std::string name(basename + ".");
		std::string value;
		while (ch != eof && Poco::Ascii::isAlphaNumeric(ch)) { name += (char) ch; ch = istr.get(); }
		while (ch != eof && Poco::Ascii::isSpace(ch)) ch = istr.get();
		if (ch != '=') throw Poco::SyntaxException("Bad attribute syntax: '=' expected", where());
		ch = istr.get();
		while (ch != eof && Poco::Ascii::isSpace(ch)) ch = istr.get();
		if (ch == '"')
		{
			ch = istr.get();
			while (ch != eof && ch != '"') { value += (char) ch; ch = istr.get(); }
			if (ch != '"') throw Poco::SyntaxException("Bad attribute syntax: '\"' expected", where());
		}
		else if (ch == '\'')
		{
			ch = istr.get();
			while (ch != eof && ch != '\'') { value += (char) ch; ch = istr.get(); }
			if (ch != '\'') throw Poco::SyntaxException("Bad attribute syntax: ''' expected", where());
		}
		else throw Poco::SyntaxException("Bad attribute syntax: '\"' or ''' expected", where());
		ch = istr.get();
		handleAttribute(name, value);
		while (ch != eof && Poco::Ascii::isSpace(ch)) ch = istr.get();
	}
}


void JSSPageReader::nextToken(std::istream& istr, std::string& token)
{
	token.clear();
	int ch = istr.get();
	if (ch != -1)
	{
		if (ch == '<' && istr.peek() == '%')
		{
			token += "<%";
			istr.get();
			ch = istr.peek();
			switch (ch)
			{
			case '%':
			case '@':
			case '=':
				ch = istr.get();
				token += (char) ch;
				break;
			case '!':
				ch = istr.get();
				token += (char) ch;
				if (istr.peek() == '!')
				{
					ch = istr.get();
					token += (char) ch;
				}
				break;
			case '-':
				ch = istr.get();
				token += (char) ch;
				if (istr.peek() == '-')
				{
					ch = istr.get();
					token += (char) ch;
				}
				break;
			}
		}
		else if (ch == '%' && istr.peek() == '>')
		{
			token += "%>";
			ch = istr.get();
		}
		else token += (char) ch;
	}
}


void JSSPageReader::handleAttribute(const std::string& name, const std::string& value)
{
	if (name == "include.page" || name == "include.file")
	{
		include(value);
	}
	else
	{
		_page.set(name, value);
	}
}


void JSSPageReader::include(const std::string& uri)
{
	Poco::URI includeURI(_uri);
	includeURI.resolve(uri);
	
	_page.handler() << "// begin include " << includeURI.toString() << "\n";
	
	Poco::SharedPtr<std::istream> pIncludeStream = Poco::URIStreamOpener::defaultOpener().open(includeURI);
	JSSPageReader includeReader(*this, includeURI.toString());
	includeReader.parse(*pIncludeStream);
	
	_page.handler() << "// end include " << includeURI.toString() << "\n";
}


std::string JSSPageReader::where() const
{
	std::stringstream result;
	result << "in resource '" << _uri << "', line " << _line;
	const JSSPageReader* pParent = _pParent;
	while (pParent)
	{
		result << "\nincluded from resource '"<<  pParent->_uri << "', line " << pParent->_line;
		pParent = pParent->_pParent;
	}
	return result.str();
}


} } } } // namespace Poco::OSP::JS::Web
