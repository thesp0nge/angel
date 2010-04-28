/*
 * $RCSfile: engine.c,v $
 * AngeL - the power to protect
 * Copyright (C) 2005 thesp0nge
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
 * $Id: engine.c,v 1.6 2006/03/09 21:36:06 sp0nge Exp $
 */

//#ifdef CONFIG_MODVERSIONS
//#define MODVERSIONS
//#include <linux/modversions.h>
//#endif

#include <linux/config.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/version.h>
#include <linux/init.h>

#include <linux/security.h>


#include "engine.h"
#include "angel_version.h"
#include "angel_sysctl.h"
#include "angel_sniffing.h"
#include "angel_inode.h"
#include "angel_devices.h"
#include "angel_settime.h"
#include "angel_capable.h"
#include "angel_ptrace.h"
#include "angel_syslog.h"
#include "angel_netfilter.h"
#include "angel_task.h"
#include "angel_list.h"

#ifndef CONFIG_SECURITY
#error "Please rebuild your kernel with Linux Security Module support"
#endif

static int secondary;
static char banner[]="$Id: engine.c,v 1.6 2006/03/09 21:36:06 sp0nge Exp $";

int sysctl_loaded = 0;
d0ser_struct d0ser_head = {
	.list = LIST_HEAD_INIT(d0ser_head.list),
	.pid=0,
	.created_at = {0, 0},
	.last_fork_at = {0, 0},
	.last_brk_at = {0, 0},
};
extern struct ctl_table_header *angel_sysctl_hdr;


static struct security_operations angel_sec_ops = {
	.sb_mount 	= angel_sb_mount,
	.sb_umount 	= angel_sb_umount,
	.sb_statfs 	= angel_sb_statfs,
	.inode_link 	= angel_inode_link,
	.inode_unlink 	= angel_inode_unlink,
	.inode_symlink 	= angel_inode_symlink,
	.inode_mkdir 	= angel_inode_mkdir,
	.inode_rmdir 	= angel_inode_rmdir,
	.inode_rename 	= angel_inode_rename,
	.file_ioctl 	= angel_file_ioctl,
	.inode_create 	= angel_inode_create,
	.inode_setattr 	= angel_inode_setattr,
	.settime 	= angel_settime,
	.capable 	= angel_capable,
	.ptrace		= angel_ptrace,
	.syslog		= angel_syslog,

	.task_create	= angel_task_create,
};

static int angel_init (void)
{
	int retval = 0;
	
	printk (KERN_INFO "[%s]: AngeL v%s %s (\"%s\") is starting up...\n", 
			ANGEL_NAME,
			ANGEL_VERSION,
			ANGEL_BUILD,
			ANGEL_CODENAME);
	printk (KERN_INFO "[%s]: %s\n",
			ANGEL_NAME,
			banner);
	// d0ser_head = kmalloc(GFP_KERNEL, sizeof(d0ser_struct));
	// if (d0ser_head == NULL) {
// 		printk(KERN_INFO "[%s]: aiee, kmalloc returned NULL, there is something wrong inside %s()\n",
// 				ANGEL_NAME,
// 				__FUNCTION__);
// 		return -1;
// 	}
//	retval = angel_d0ser_init();

			
//	if (retval == -1) {
//		printk(KERN_INFO "[%s] failure while initialize internal structures. Giving up...\n",
//				ANGEL_NAME);
//		retval = -EPERM;
//		goto out;
//	}
		
	sysctl_loaded = angel_sysctl_create();
	if (!sysctl_loaded == -1)
		printk(KERN_INFO "[%s] register_sysctl_table() failed\n", ANGEL_NAME);
	retval = register_security(&angel_sec_ops);
	if (retval) {
		printk (KERN_INFO "[%s] failing registering with kernel\n", ANGEL_NAME);
		retval = mod_reg_security(THIS_MODULE->name, &angel_sec_ops);
		if (retval) {
			printk( KERN_INFO "[%s] failure registering in module stack\n", ANGEL_NAME);
			retval = -EPERM;
			goto out;
		}
		secondary = 1;
	}
	retval = angel_netfilter_hook();
	if ( retval == -1 ) {
 		printk (KERN_INFO "[%s] failure registering netfilter hook\n", ANGEL_NAME);
 		retval = -EPERM;
 	}
	printk (KERN_INFO "[%s] startup complete. Host disarmed.\n", ANGEL_NAME);
out:
	return retval;
}

static void angel_exit (void)
{
	int retval;

	if (secondary) {
		if (mod_unreg_security(THIS_MODULE->name, &angel_sec_ops)) 
			printk("[%s] failure unregistering in module stack",ANGEL_NAME);
	} else {
		if (unregister_security(&angel_sec_ops)) 
			printk("[%s] failure unregistering with kernel", ANGEL_NAME);
	}

	if (sysctl_loaded == 0)
		angel_sysctl_destroy();

	retval = angel_netfilter_unhook();
	if ( retval == -1 ) {
 		printk (KERN_INFO "[%s] failure unregistering netfilter hook\n", ANGEL_NAME);
 		retval = -EPERM;
 	}

	printk (KERN_INFO "[%s] shutdown complete.\n", 
			ANGEL_NAME);
	return ;
}

module_init(angel_init);
module_exit(angel_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("thesp0nge <sponge@sikurezza.org>");
