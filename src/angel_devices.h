#ifndef _ANGEL_DEVICES_H
#define _ANGEL_DEVICES_H

#include <linux/fs.h>
#include <linux/dcache.h>
#include <linux/namei.h>
#include <linux/sched.h>
#include <asm/current.h>

#include "engine.h"

int angel_sb_mount (char *dev_name, 
      struct nameidata *nd,
      char *type, 
      unsigned long flags, 
      void *data);
int angel_sb_statfs (struct super_block * sb);
int angel_sb_umount (struct vfsmount * mnt, int flags);
#endif
