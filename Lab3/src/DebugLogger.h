#ifndef DEBUGLOGGER_H
#define DEBUGLOGGER_H
#include <stdbool.h>
#include <stdio.h>
#define DEBUG_MSG_LENGTH 256
void debug_message(char* format, ...);
void debug_warning(char* format, ...);
void debug_error(char* format, ...);
bool debug_is_enabled();
#endif