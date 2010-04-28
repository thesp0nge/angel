/*
 * $RCSfile: angel_tcp.c,v $
 *
 * AngeL TCP protocol handler
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
 * $Id: angel_tcp.c,v 1.2 2005/12/04 20:33:08 sp0nge Exp $
 */
#include "angel_tcp.h"
static inline int __angel_is_land (struct iphdr *iphdr, struct tcphdr *tcphdr) 
{
	return ((iphdr->saddr == iphdr->daddr) && (tcphdr->source == tcphdr->dest))? 1 : 0;
}

static inline int __angel_is_raw_socket (struct sk_buff *skb)
{
	return ((skb->sk->sk_type == SOCK_RAW) || (skb->sk->sk_type == SOCK_PACKET)) ? 1 : 0;
}


static inline int __angel_is_sane_packet(struct tcphdr *tcp)
{
	// Drop Xmas !! Ymax
	if (tcp->res1 != 0)
		return 0;
	// Drops SYN without ACK but with other flags set
	if ((tcp->syn && !tcp->ack)
			&& (tcp->fin || tcp->rst || tcp->psh || tcp->urg))
		return 0;
	// Drops SYN/ACK with RST and/or FIN set
	if ((tcp->syn && tcp->ack) && (tcp->fin || tcp->rst))
		return 0;
	// Drops TCP packet with no-sense flags ( or without flags at all )
	if (!tcp->fin && !tcp->syn && !tcp->rst && !tcp->ack)
		return 0;
	return 1;

}


int angel_tcp (struct tcphdr *tcphdr, struct sk_buff *skb)
{
	struct iphdr *iphdr = skb->nh.iph;
	if (!__angel_is_sane_packet(tcphdr)) {
		printk (KERN_INFO "[%s] %s(): tcp packet with non sense header against %d.%d.%d.%d (port %d)\n",
				MY_NAME,
				__FUNCTION__,
				NIPQUAD(iphdr->daddr),
				tcphdr->dest);
		return -1;
	}
				
	if (__angel_is_raw_socket(skb)) {
		printk (KERN_INFO "[%s] %s(): raw socket detected against %d.%d.%d.%d (port %d)\n",
				MY_NAME,
				__FUNCTION__,
				NIPQUAD(iphdr->daddr),
				tcphdr->dest);
		return -1;
	}
			
	if (__angel_is_land(iphdr, tcphdr)) {
		printk (KERN_INFO "[%s] %s(): land attack detected against %d.%d.%d.%d (port %d)\n",
				MY_NAME,
				__FUNCTION__,
				NIPQUAD(iphdr->daddr),
				tcphdr->dest);
		return -1;
	}

	return 0;

}


