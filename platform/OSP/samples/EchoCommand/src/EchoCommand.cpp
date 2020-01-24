//
// EchoCommand.cpp
//
// Copyright (c) 2009, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// This is unpublished proprietary source code of Applied Informatics.
// The contents of this file may not be disclosed to third parties, 
// copied or duplicated in any form, in whole or in part.
//


#include "Poco/ClassLibrary.h"
#include "Poco/OSP/Shell/Command.h"
#include "Poco/OSP/Shell/CommandFactory.h"
#include "Poco/Util/Application.h"
#include "Poco/Util/AbstractConfiguration.h"


class EchoCommand: public Poco::OSP::Shell::Command
	/// Output a space-separated list of all given
	/// command line arguments.
	///
	/// References to application configuration properties
	/// in the form of ${<property>} are expanded.
{
public:
	int execute(Poco::OSP::Shell::Session& session, const std::vector<std::string>& args, std::ostream& ostr)
	{
		Poco::Util::Application& app = Poco::Util::Application::instance();

		if (args.size() == 2 && args[1] == "--help")
		{
			ostr << "usage: " << args[0] << " [<arg>...]\n"
			     << "Echo arguments to output.\n"
			     << "References to application configuration properties in the form of\n"
			     << "${<property>} are expanded." << std::endl;
		}
		else
		{
			for (int i = 1; i < args.size(); ++i)
			{
				if (i > 1) ostr << ' ';
				ostr << app.config().expand(args[i]);
			}
			ostr << std::endl;
		}		
		return Command::STATUS_OK;
	}
};


class EchoCommandFactory: public Poco::OSP::Shell::CommandFactory
{
public:
	Poco::OSP::Shell::Command* createCommand()
	{
		return new EchoCommand;
	}
};


POCO_BEGIN_NAMED_MANIFEST(Shell, Poco::OSP::Shell::CommandFactory)
	POCO_EXPORT_CLASS(EchoCommandFactory)
POCO_END_MANIFEST
