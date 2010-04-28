/*
 * $RCSfile: angel_inode.c,v $
 * AngeL - The power to protect
 *
 * VFS both soft and hard link handler
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
 * $Id: angel_inode.c,v 1.2 2005/11/02 11:40:54 sp0nge Exp $
 */

#include "angel_inode.h"

int __angel_escape_from_pwd (struct dentry *pwd, struct dentry *link)
{
	struct dentry *t;

	for (t=link; strcmp(t->d_name.name, "/") != 0; t=t->d_parent)
		if (pwd == t)
			return 0;
	return -1;
}

int angel_inode_link(struct dentry *old_dentry, 
      struct inode *dir, 
      struct dentry *new_dentry) 
{

#ifdef ANGEL_DENY_HARD_LINK
	// struct dentry *current_root = current->fs->root;
	struct dentry *current_pwd  = current->fs->pwd;

	if ( __angel_escape_from_pwd(current_pwd, new_dentry) == -1 ) {
		printk (KERN_INFO "[%s] creating hard link outside current working directory is denied... sorry.\n", MY_NAME);
		return -1;
	}
#endif
			
	return 0;
}

int angel_inode_symlink (struct inode *dir,
      struct dentry *dentry, 
      const char *old_name) {

#ifdef ANGEL_DENY_SOFT_LINK
	// struct dentry *current_root = current->fs->root;
	struct dentry *current_pwd  = current->fs->pwd;

	if ( __angel_escape_from_pwd(current_pwd, dentry) == -1 ) {

		printk(KERN_INFO "[%s] creating soft link outside current working directory is denied... sorry.\n", MY_NAME);
		return -1;
	}
#endif
	return 0;
}

int angel_inode_create (struct inode *dir,
      struct dentry *dentry, int mode) 
{

#ifdef ANGEL_DENY_ALLOW_DIR_BROWSING
	if (S_ISDIR(mode) && ((mode & S_IXUSR) || (mode & S_IXGRP) || (mode & S_IXOTH))) {
		printk(KERN_INFO "[%s] uid %d can't make browable flag for directory %s\n",
				MY_NAME,
				current->uid,
				dentry->d_name.iname);
		return -1;
	}
#endif

#ifdef ANGEL_DENY_CREATE_EXECUTABLES
	// if ((mode & S_IXUSR) || (mode & S_IXGRP) || (mode & S_IXOTH)) {
	if (S_ISREG(mode) && ((mode & S_IXUSR) || (mode & S_IXGRP) || (mode & S_IXOTH))) {
		printk(KERN_INFO "[%s] uid %d can't create files with execute permission (%s).\n", 
				MY_NAME, 
				current->uid,
				dentry->d_name.name);
		return -1;
	}
#endif
	return 0;

}

int angel_inode_setattr	(struct dentry *dentry, struct iattr *attr) 
{
	umode_t mode = attr->ia_mode;

#ifdef ANGEL_DENY_ALLOW_DIR_BROWSING
	if (S_ISDIR(mode) && ((mode & S_IXUSR) || (mode & S_IXGRP) || (mode & S_IXOTH))) {
		printk(KERN_INFO "[%s] uid %d can't make browable flag for directory %s\n",
				MY_NAME,
				current->uid,
				dentry->d_name.iname);
		return -1;
	}
#endif

#ifdef ANGEL_DENY_CREATE_EXECUTABLES
	if (S_ISREG(mode) && ((mode & S_IXUSR) || (mode & S_IXGRP) || (mode & S_IXOTH))) {
		printk(KERN_INFO "[%s] uid %d can't set execute flag for file %s.\n", 
				MY_NAME, 
				current->uid, 
				dentry->d_name.name);
		return -1;
	}
#endif
	return 0;
}
int angel_inode_unlink (struct inode *dir, struct dentry *dentry)
{
#ifdef CONFIG_ANGEL_DENY_UNLINK
	printk (KERN_INFO "[%s] uid %d is not allowed to unlink %s\n",
			MY_NAME,
			current->uid,
			dentry->d_name.name);
	return -1;
#else
	return 0;
#endif
}
int angel_inode_mkdir (struct inode *dir, struct dentry *dentry, int mode) 
{
#ifdef CONFIG_ANGEL_DIR
	printk(KERN_INFO "[%s] uid %d is not allowed to create directory %s\n",
			MY_NAME,
			current->uid,
			dentry->d_name.name);
	return -1;
#else
	return 0;
#endif
}

int angel_inode_rmdir (struct inode *dir, struct dentry *dentry)
{
#ifdef CONFIG_ANGEL_DIR
	printk(KERN_INFO "[%s] uid %d is not allowed to remove directory %s\n",
			MY_NAME,
			current->uid,
			dentry->d_name.name);
	return -1;
#else
	return 0;
#endif
}
int angel_inode_rename (struct inode *old_dir, 
		struct dentry *old_dentry,
		struct inode *new_dir, 
		struct dentry *new_dentry)
{
#ifdef CONFIG_ANGEL_DENY_RENAME
	printk(KERN_INFO "[%s] uid %d is not allowed to rename %s to %s\n",
			MY_NAME,
			current->uid,
			old_dentry->d_name.name,
			new_dentry->d_name.name);
	return -1;
#else
	return 0;
#endif
}

