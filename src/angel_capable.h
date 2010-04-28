#ifndef _ANGEL_CAPABLE_H
#define _ANGEL_CAPABLE_H

#include <linux/sched.h>
#include <linux/capability.h>

#include "engine.h"
int angel_capable (struct task_struct * tsk, int cap);
#endif
