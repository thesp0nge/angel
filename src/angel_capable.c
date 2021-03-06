/*
 * $RCSfile: angel_capable.c,v $
 * Project - Brief project description
 *
 * capable() security handler
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
 * $Id: angel_capable.c,v 1.1 2005/11/02 11:29:48 sp0nge Exp $
 */
#include "angel_capable.h"
int angel_capable (struct task_struct * tsk, int cap)
{
#ifdef CONFIG_ANGEL_CAPABLE
	switch (cap) {
		case CAP_SYS_CHROOT:
			printk (KERN_INFO "[%s]: CAP_SYS_CHROOT capability denied for uid %d\n",
					MY_NAME,
					current->uid);
			return -1;
			break;
		default:
			return 0;
			break;
	}
#else
	return 0;
#endif
}
