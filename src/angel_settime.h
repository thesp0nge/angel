#ifndef _ANGEL_SETTIME_H
#include <linux/time.h>
#include "engine.h"
int angel_settime (struct timespec *ts, struct timezone *tz);
#endif
