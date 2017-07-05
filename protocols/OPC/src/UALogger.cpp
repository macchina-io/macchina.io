/* This work is licensed under a Creative Commons CCZero 1.0 Universal License.
 * See http://creativecommons.org/publicdomain/zero/1.0/ for more information. */

#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <errno.h>
#include "IoT/OPC/UALogger.h"
#include "Poco/Logger.h"


extern const char *LogLevelNames[6];// = {"trace", "debug", "info", "warning", "error", "fatal"};
extern const char *LogCategoryNames[6];// = {"network", "channel", "session", "server", "client", "userland"};


namespace IoT {
namespace OPC {

Poco::Logger* uaLogger = nullptr;

} } // namespace IoT::OPC


void UA_Log_POCO(UA_LogLevel level, UA_LogCategory category, const char *msg, ...)
{
	using namespace IoT::OPC;

	va_list args; va_start(args, msg);
	char c[2] = {0};
	int count = vsnprintf(c, 1, msg, args);
	va_end(args);
	if(count < 0)
	{
		fprintf(stderr, "%s", strerror(errno));
		fflush(stderr);
	}
	else
	{
		char* buf = (char*) calloc(count + 1, 1);
		if(uaLogger && buf)
		{
			va_list args; va_start(args, msg);
			vsnprintf(buf, count + 1, msg, args);
			//printf("logging=%d, %p, %d, %p, %s\n", count, uaLogger, category, buf, buf);
			switch(category)
			{
				case UA_LOGLEVEL_TRACE: 
					uaLogger->trace(buf);
					break;
				case UA_LOGLEVEL_DEBUG:
					uaLogger->debug(buf);
					break;
				case UA_LOGLEVEL_INFO:
					uaLogger->information(buf);
					break;
				case UA_LOGLEVEL_WARNING:
					uaLogger->warning(buf);
					break;
				case UA_LOGLEVEL_ERROR:
					uaLogger->error(buf);
					break;
				case UA_LOGLEVEL_FATAL:
					uaLogger->fatal(buf);
					break;
			}
			va_end(args);
		}
		free(buf);
	}
}
