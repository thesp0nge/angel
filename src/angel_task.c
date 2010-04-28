/*
 * $RCSfile: angel_task.c,v $
 *
 * Users tasks handling routines
 *
 * Copyright (C) 2005 sp0nge
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA  02111-1307  USA
 *
 * $Id: angel_task.c,v 1.1 2006/03/09 21:27:47 sp0nge Exp $
 */
#include "angel_task.h"

extern d0ser_struct d0ser_head;
inline int angel_allow_task_create(int childs, int time) 
{
	if (time == 0) {
#ifdef ANGEL_TASK_DEBUG
		printk (KERN_INFO "%s() trying to divide per 0... allow this fork().\n", __FUNCTION__);
#endif
		return 0;
	}
	// printk (KERN_INFO "%s(): %d %d -> %d %d\n", __FUNCTION__, childs, time, childs/time, ANGEL_MAX_CHILDREN_TO_SEC_RATIO);
	return ((childs/time) > ANGEL_MAX_CHILDREN_TO_SEC_RATIO) ? -1 : 0;
}
	

int angel_task_create(unsigned long clone_flags)
{
	struct task_struct *daddy;
	struct list_head *p;
	struct timespec now;
	d0ser_struct *entry;
	d0ser_struct *new_d0;
	int found=0;

	if (current == NULL) {
		printk (KERN_ERR "[%s]: aiee current process address is NULL. What's going on?\n", 
				ANGEL_NAME);
		return -1;
	}

	if (&d0ser_head.list == NULL) {
		printk (KERN_ERR "[%s]: aiee d0ser linked list is not initialized, go and fix the code!!!\n", 
				ANGEL_NAME);
		return -1;
	}
	daddy = current->group_leader;
	now = current->start_time;

	list_for_each(p, &d0ser_head.list) {
		entry = list_entry(p, d0ser_struct, list);
		if (entry->pid == daddy->pid) {
		 	found=1;
			entry->childs++;
			entry->last_fork_at = CURRENT_TIME_SEC;
			//	printk(KERN_INFO "pid %d has %d childs in %ld secs\n", entry->pid,
			//		entry->childs,
			//		entry->last_fork_at.tv_sec - entry->created_at.tv_sec);
			if (angel_allow_task_create(entry->childs, entry->last_fork_at.tv_sec - entry->created_at.tv_sec) == -1) {
				printk(KERN_INFO "[%s] aiee: a possible fork bombing detected (%s, pid: %d spawned %d childs in %ld secs).\n",
						ANGEL_NAME,
						entry->comm,
						entry->pid,
						entry->childs,
						entry->last_fork_at.tv_sec - entry->created_at.tv_sec);
				
				kill_proc(entry->pid, SIGKILL, 1);
				return -1;
			}
		} else {
		 	found =0;
		}
	}
	if (found == 0) 
		D0SER_ADD_ELEMENT(new_d0);

	return 0;
}
	
