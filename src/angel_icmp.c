/*
 * $RCSfile: angel_icmp.c,v $
 * 
 * AngeL icmp protocol handler
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
* $Id: angel_icmp.c,v 1.2 2006/03/09 21:31:12 sp0nge Exp $
*/
#include <linux/socket.h>
#include "angel_icmp.h"
#include "angel_ip.h"
#include "angel_socket.h"

static inline int __angel_smurf(struct sk_buff *skb) {
return ((__angel_ip_spoofing(skb)) &&\
	(angel_is_a_broadcast(skb->sk)) && \
	((((struct icmphdr *) (((char *)skb->nh.iph) +\
			       skb->nh.iph->ihl * 4)))->type==ICMP_ECHO)) ? 1 : 0 ;
}

static inline int __angel_pingofdeath(struct sk_buff *skb) { 
	return ((skb->nh.iph->frag_off == htons(0x2000)) &&\
		(((struct icmphdr *) (((char *)skb->nh.iph) + \
				      skb->nh.iph->ihl * 4)))->type == ICMP_ECHO) ? 1 : 0;
}

int angel_icmp (struct icmphdr *icmphdr, struct sk_buff *skb) {
	struct iphdr *iphdr = skb->nh.iph;

	if (__angel_smurf(skb)) {
		printk (KERN_INFO "[%s] %s(): smurf attack detected against %d.%d.%d.%d\n",
				MY_NAME,
				__FUNCTION__,
				NIPQUAD(iphdr->daddr));
		return -1;
	}
	
	if (__angel_pingofdeath(skb)) {
		printk (KERN_INFO "[%s] %s(): ping of death attack detected against %d.%d.%d.%d\n",
				MY_NAME,
				__FUNCTION__,
				NIPQUAD(iphdr->daddr));
		return -1;
	}
	return 0;
}

