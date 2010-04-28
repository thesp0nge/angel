#ifndef _ANGEL_SNIFFING_H
#define _ANGEL_SNIFFING_H

#include <linux/if.h>
#include <linux/net.h>
int angel_is_sniffing_via_socket(int family, int type);
int angel_is_sniffing_via_ioctl(struct ifreq *ifr);
int angel_file_ioctl(struct file *file, unsigned int command, unsigned long arg);
#endif
