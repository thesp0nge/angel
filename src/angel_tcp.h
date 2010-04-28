#ifndef _ANGEL_TCP_H
#define _ANGEL_TCP_H

#include <linux/tcp.h>
#include <linux/ip.h>

#include "engine.h"
int angel_tcp (struct tcphdr *tcphdr, struct sk_buff *skb);
#endif
