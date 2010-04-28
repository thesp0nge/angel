#ifndef _ANGEL_ENGINE_H
#define _ANGEL_ENGINE_H

#include <linux/module.h>
#include <linux/types.h>
#define MY_NAME THIS_MODULE->name
#define ANGEL_NAME THIS_MODULE->name

#ifdef ANGEL_DEBUG
#define angel_debug(f, a...) \
	do {\
		printk(KERN_DEBUG "[%s] DEBUG in %s() (%s:%d): ", ANGEL_NAME, __FUNCTION__, __FILE__, __LINE__);\
		printk(f, ## a); \
	} while (0)
#else
#define angel_debug(f, a...) \
	do {\
	} while (0)
#endif // #ifdef ANGEL_DEBUG

#define angel_bug(f, a...) \
	do {\
		printk(KERN_ERR "[%s] BUG in %s() (%s:%d): ", ANGEL_NAME, __FUNCTION__, __FILE__, __LINE__); \
		printk(f, ## a); \
	} while (0)


#endif // #ifndef _ANGEL_ENGINE_H
