#ifndef _ANGEL_ICMP_H
#define _ANGEL_ICMP_H

#include <linux/icmp.h>
#include <linux/ip.h>

#include "engine.h"
int angel_icmp (struct icmphdr *icmphdr, struct sk_buff *skb);
#endif
