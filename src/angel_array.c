/*
 * $RCSfile: angel_array.c,v $
 *
 * Copyright (C) 2005 thesp0nge - <sponge@sikurezza.org>
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
 * $Id: angel_array.c,v 1.1.1.1 2005/10/06 21:47:21 sp0nge Exp $ 
 */ 
#include <linux/kernel.h>
#include <linux/string.h>
#include "angel_init_monitor.h"

int angel_char_array_lookup(char *v[], char *tofind)
{
	int ret = -1;
	int i;
	for ( i=0; ((v[i] != NULL) && (ret == -1)); i++) {
		if (strcmp(v[i], tofind) == 0)
			ret = 0;
	}
	return ret;
}

int angel_int_array_lookup (int v[], int tofind)
{
	int ret = -1;
	int i;
	for ( i = 0; ((v[i] != -1) && (ret == -1)); i++) {
		if (v[i] == tofind)
			ret = 0;
	}
	return ret;
}

int angel_default_dirs_lookup (char *tofind)
{
	return angel_char_array_lookup(default_monitored_dirs, tofind);
}
int angel_default_files_lookup (char *tofind)
{
	return angel_char_array_lookup(default_monitored_files, tofind);
}
