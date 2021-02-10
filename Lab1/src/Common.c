#include "Common.h"
#include <stdio.h>
#include <stdlib.h>
#include "DebugLogger.h"

void malloc_assert(bool is_null, char *name)
{
	if (is_null)
	{
		debug_error("Malloc failed in %s\n", name);
		getchar();
		exit(1);
	}
}
