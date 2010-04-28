#ifndef _ANGEL_LIST_H
#define _ANGEL_LIST_H

#include <linux/sched.h>
#include <linux/list.h>
#include <linux/types.h>

#include "engine.h"

#define	D0SER_TASK_CREATE	1
#define D0SER_BRK_CREATE	2

#define D0SER_ADD_ELEMENT(new_d0) \
	do { \
	new_d0= kmalloc(GFP_KERNEL, sizeof(d0ser_struct)); \
	if ( !new_d0 ) { \
		printk (KERN_ERR "[%s]: aiee, memory is running out. kmalloc() returned NULL in %s()\n", \
				ANGEL_NAME, \
				__FUNCTION__); \
		return -1; \
	} \
	memset (new_d0, 0, sizeof(d0ser_struct)); \
	INIT_LIST_HEAD(&new_d0->list); \
	new_d0->pid=(pid_t)daddy->pid; \
	memset(new_d0->comm, 0, TASK_COMM_LEN); \
	strncpy(new_d0->comm, daddy->comm, TASK_COMM_LEN - 1); \
	new_d0->created_at=CURRENT_TIME_SEC; \
	new_d0->last_fork_at=CURRENT_TIME_SEC; \
	new_d0->childs = 0; \
	list_add_tail(&new_d0->list, &(d0ser_head.list));	\
        } while (0)

	
typedef struct {
	struct list_head list;
	pid_t pid;
	char comm[TASK_COMM_LEN];
	unsigned int childs;
	unsigned int brks;
	struct timespec created_at;
	struct timespec last_fork_at;
	struct timespec last_brk_at;
} d0ser_struct;

inline int angel_d0ser_add_element(d0ser_struct d0ser_head, pid_t daddy_pid, int flags);

#endif
