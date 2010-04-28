/*
 * $RCSfile: angel_list.c,v $
 * AngeL - The power to protect
 *
 * Internal double list common routines
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
 * $Id: angel_list.c,v 1.1 2006/03/09 21:26:34 sp0nge Exp $
 */
#include "angel_list.h"
extern d0ser_struct d0ser_head;

inline int angel_d0ser_add_element(d0ser_struct list_head, pid_t daddy_pid, int flags) 
{
	d0ser_struct *new_d0 = kmalloc(GFP_KERNEL, sizeof(d0ser_struct));
	if ( !new_d0 ) {
		printk (KERN_ERR "[%s]: aiee, memory is running out. kmalloc() returned NULL in %s()\n",
				ANGEL_NAME,
				__FUNCTION__);
		return -1;
	}
	if ( &(d0ser_head.list) == NULL) {
		printk (KERN_ERR "[%s]: aiee, attempting to manage a NULL list in %s()\n",
				ANGEL_NAME,
				__FUNCTION__);
		return -1;
	}
	memset (new_d0, 0, sizeof(d0ser_struct));
	INIT_LIST_HEAD(&new_d0->list);
	new_d0->pid=(pid_t)daddy_pid;
	new_d0->created_at=CURRENT_TIME_SEC;
	
	if ( flags == D0SER_TASK_CREATE )
		new_d0->last_fork_at=CURRENT_TIME_SEC;
	else
		new_d0->last_fork_at=((struct timespec) { 0, 0});
	
	if ( flags == D0SER_BRK_CREATE )
		new_d0->last_brk_at=CURRENT_TIME_SEC;
	else
		new_d0->last_brk_at=((struct timespec) { 0, 0});
	
	new_d0->childs = 0;
	new_d0->brks = 0;

	list_add_tail(&new_d0->list, &(list_head.list));	

	return 0;
}
