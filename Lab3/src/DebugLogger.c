#include "DebugLogger.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#define DEBUG_MODE 3

void debug_message(char* format, ...)
{
	if (DEBUG_MODE >= 3) {
		char buf[DEBUG_MSG_LENGTH];
		va_list vl;
		va_start(vl, format);
		vsnprintf(buf, sizeof(buf), format, vl);
		va_end(vl);
		printf("%s", buf);
	}
}

void debug_warning(char* format, ...)
{
	if (DEBUG_MODE >= 2) {
		char buf[DEBUG_MSG_LENGTH];
		va_list vl;
		va_start(vl, format);
		vsnprintf(buf, sizeof(buf), format, vl);
		va_end(vl);
		printf("(WARNING) %s", buf);
	}
}

void debug_error(char* format, ...)
{
	if (DEBUG_MODE >= 1) {
		char buf[DEBUG_MSG_LENGTH];
		va_list vl;
		va_start(vl, format);
		vsnprintf(buf, sizeof(buf), format, vl);
		va_end(vl);
		printf("(ERROR) %s", buf);
		abort();
	}
}

bool debug_is_enabled() {
	return (DEBUG_MODE > 1);
}