/*
 * $RCSfile: angel_settime.c,v $
 * Project - Brief project description
 *
 * Some more words about it...
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
 * $Id: angel_settime.c,v 1.1 2005/10/25 21:17:53 sp0nge Exp $
 */
#include "angel_settime.h"
int angel_settime (struct timespec *ts, struct timezone *tz)
{
#ifdef ANGEL_DENY_SETTIME
	printk (KERN_INFO "[%s]: denying %s to set system time\n", 
			MY_NAME,
			current->comm);
	return -1;
#else
	return 0;
#endif
}

