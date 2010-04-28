#ifndef _ANGEL_TASK_H
#define _ANGEL_TASK_H

#include <linux/sched.h>
#include <linux/time.h>
#include <linux/list.h>
#include <linux/syscalls.h>

#include "engine.h"
#include "angel_list.h"

#define ANGEL_MAX_CHILDREN_TO_SEC_RATIO	10

int angel_task_create(unsigned long clone_flags);
inline int angel_allow_task_create(int childs, int time);
#endif
