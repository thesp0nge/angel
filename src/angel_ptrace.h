#ifndef _ANGEL_PTRACE_H
#define _ANGEL_PTRACE_H

#include <linux/sched.h>
#include "engine.h"
int angel_ptrace (struct task_struct * parent, struct task_struct * child);
#endif
