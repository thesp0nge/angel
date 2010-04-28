/*
 * $RCSfile: angel_ptrace.c,v $
 * Project - Brief project description
 *
 * Security handler to the ability to trace child processes from parent
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
 * $Id: angel_ptrace.c,v 1.1 2005/11/02 11:33:44 sp0nge Exp $
 */
#include "angel_ptrace.h"
int angel_ptrace (struct task_struct * parent, struct task_struct * child)
{
#ifdef CONFIG_ANGEL_DENY_PTRACE
	printk(KERN_INFO "[%s]: uid %d is not allowed to ptrace %s from %s\n",
			MY_NAME,
			current->uid,
			child->comm,
			parent->comm);
	return -1;
#else
	return 0;
#endif
}
