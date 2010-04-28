#ifndef _ANGEL_IP_H
#define _ANGEL_IP_H

#include <linux/ip.h>
#include <linux/netdevice.h>
#include <linux/inetdevice.h>

#include "angel_netfilter.h"
#include "engine.h"
int angel_ip (struct iphdr *ip, struct sk_buff *skb);
int __angel_ip_spoofing (const struct sk_buff *skb);
#endif
