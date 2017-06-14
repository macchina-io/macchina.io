#ifndef UA_LOG_POCO_H_
#define UA_LOG_POCO_H_


#include "open62541.h"


void UA_Log_POCO(UA_LogLevel level, UA_LogCategory category, const char *msg, ...);


#endif /* UA_LOG_POCO_H_ */
