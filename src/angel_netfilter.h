#ifndef _ANGEL_NETFILTER_H
#define _ANGEL_NETFILTER_H

#include <linux/netfilter.h>
#include <linux/netfilter_ipv4.h>
#include <linux/in.h>

#include <linux/tcp.h>
#include <linux/udp.h>
#include <linux/icmp.h>
#include "engine.h"

int angel_netfilter_hook(void);
int angel_netfilter_unhook(void);
#endif
