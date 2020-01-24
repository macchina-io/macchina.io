//
// LogLevelCommand.cpp
//
// Copyright (c) 2013, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// This is unpublished proprietary source code of Applied Informatics.
// The contents of this file may not be disclosed to third parties, 
// copied or duplicated in any form, in whole or in part.
//


#include "Poco/ClassLibrary.h"
#include "Poco/OSP/Shell/Command.h"
#include "Poco/OSP/Shell/CommandFactory.h"
#include "Poco/OSP/Shell/Session.h"
#include "Poco/OSP/ServiceFinder.h"
#include "Poco/Logger.h"
#include <iostream>


class LogLevelCommand: public Poco::OSP::Shell::Command
	/// This class implements the "loglevel" command
	/// for querying or changing log levels.
{
public:
	int execute(Poco::OSP::Shell::Session& session, const std::vector<std::string>& args, std::ostream& ostr)
	{
		if (args.size() > 1 && (args[1] == "--help" || args[1] == "-h"))
		{
			help(ostr);
			return Poco::OSP::Shell::Command::STATUS_OK; 
		}
		
		if (args.size() == 1)
		{
			std::vector<std::string> loggers;
			Poco::Logger::names(loggers);
			for (std::vector<std::string>::const_iterator it = loggers.begin(); it != loggers.end(); ++it)
			{
				const Poco::Logger& logger = Poco::Logger::get(*it);
				std::string level = levelToString(logger.getLevel());
				std::string name(*it);
				if (name.empty()) name = "(root)";
				level.resize(14, ' ');
				ostr << level << name << std::endl;
			}
			return Poco::OSP::Shell::Command::STATUS_OK; 
		}
		else if (args.size() == 2)
		{
			Poco::Logger* pLogger = Poco::Logger::has(args[1]);
			if (pLogger)
			{
				ostr << levelToString(pLogger->getLevel());
				return Poco::OSP::Shell::Command::STATUS_OK; 
			}
			else
			{
				ostr << "Not found: " << args[1] << std::endl;
				return Poco::OSP::Shell::Command::STATUS_ERROR;
			}
		}
		else if (args.size() == 3)
		{
			std::string logger(args[1]);
			std::string level(args[2]);
			if (logger == "*") logger.clear();
			Poco::Logger::setLevel(logger, Poco::Logger::parseLevel(level));
			return Poco::OSP::Shell::Command::STATUS_OK; 
		}
		else
		{
			ostr << "Error: Too many arguments." << std::endl;
			return Poco::OSP::Shell::Command::STATUS_USAGE;
		}
	}

protected:
	void help(std::ostream& ostr)
	{
		ostr 
			<< "usage: loglevel [<logger> [<level>]]\n"
			<< "Show or modify log levels.\n"
			<< "To show the levels of all loggers, invoke without arguments.\n"
			<< "To show the level of a specific logger, invoke with the name\n"
			<< "of the logger as only argument.\n"
			<< "To change the level of a logger, specify both the name of the logger\n"
			<< "and the log level as argument.\n"
			<< "To change the level of all loggers, specify an asterisk (*) as first\n"
			<< "argument.\n"
			<< "Valid log levels are:\n"
			<< "  - none\n"
			<< "  - fatal\n"
			<< "  - critical\n"
			<< "  - error\n"
			<< "  - warning\n"
			<< "  - notice\n"
			<< "  - information\n"
			<< "  - debug\n"
			<< "  - trace\n"
			<< std::endl;
	}

	static std::string levelToString(int level)
	{
		switch (level)
		{
		case 0: return "none";
		case 1: return "fatal";
		case 2: return "critical";
		case 3: return "error";
		case 4: return "warning";
		case 5: return "notice";
		case 6: return "information";
		case 7: return "debug";
		case 8: return "trace";
		default: return "unknown";
		}
	}
};


class LogLevelCommandFactory: public Poco::OSP::Shell::CommandFactory
{
public:
	Poco::OSP::Shell::Command* createCommand()
	{
		return new LogLevelCommand;
	}
};


POCO_BEGIN_NAMED_MANIFEST(Shell, Poco::OSP::Shell::CommandFactory)
	POCO_EXPORT_CLASS(LogLevelCommandFactory)
POCO_END_MANIFEST
