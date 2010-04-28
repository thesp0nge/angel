#ifndef _ANGEL_LINK_H
#define _ANGEL_LINK_H

#include <linux/sched.h>
#include <linux/dcache.h>
#include <linux/fs.h>
#include <asm/current.h>

#include "engine.h"
int angel_inode_link(struct dentry *old_dentry, 
      struct inode *dir, 
      struct dentry *new_dentry);
int angel_inode_symlink (struct inode *dir,
      struct dentry *dentry, 
      const char *old_name);
int angel_inode_create (struct inode *dir,
      struct dentry *dentry, int mode);
int angel_inode_setattr	(struct dentry *dentry, struct iattr *attr);
int angel_inode_unlink (struct inode *dir, struct dentry *dentry);
int angel_inode_mkdir (struct inode *dir, struct dentry *dentry, int mode);
int angel_inode_rmdir (struct inode *dir, struct dentry *dentry);
int angel_inode_rename (struct inode *old_dir, 
		struct dentry *old_dentry,
		struct inode *new_dir, 
		struct dentry *new_dentry);
#endif

