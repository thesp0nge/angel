/*
 * $RCSfile: angel_devices.c,v $
 * AngeL - The power to protect
 * 
 * Security handlers for filesystem operations
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
 * $Id: angel_devices.c,v 1.3 2006/03/09 21:30:39 sp0nge Exp $
 */
#include <linux/dcache.h>
#include "angel_devices.h"

int angel_sb_mount (char *dev_name, 
      struct nameidata *nd,
      char *type, 
      unsigned long flags, 
      void *data) {


#ifdef CONFIG_ANGEL_DENY_MOUNT
   struct dentry *d = nd->dentry;

   if (flags & MS_REMOUNT)
	   printk(KERN_INFO "[%s] uid %d can't remount devices at %s\n",
			   MY_NAME, 
			   current->uid, 
			   d->d_name.name);
   else {
	   if (flags & MS_BIND)
		   printk(KERN_INFO "[%s] uid %d can't do a loopback/bind mount to %s\n",
				   MY_NAME, current->uid, dev_name);
	   else
		   printk(KERN_INFO "[%s] uid %d can't mount device %s\n",
				   MY_NAME, current->uid, dev_name);
   }
   return -1;
#else
   return 0;
#endif
}

int angel_sb_statfs (struct super_block * sb) 
{
#ifdef CONFIG_ANGEL_DENY_STAT
	// angel_debug("%d\n", sb->s_root->d_inode->i_uid);
	printk (KERN_INFO "[%s] uid %d can't retrieve filesystem informations using statfs()\n",
			MY_NAME,
			current->uid);
	return -1;
#else
	return 0;
#endif
}

int angel_sb_umount (struct vfsmount * mnt, int flags) 
{
#ifdef CONFIG_ANGEL_DENY_MOUNT
	printk(KERN_INFO "[%s] uid %d is not allowed to unmount devices\n",
			MY_NAME,
			current->uid);
	return -1;
#else
	return 0;
#endif
}

