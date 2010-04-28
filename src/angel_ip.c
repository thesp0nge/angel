/*
 * $RCSfile: angel_ip.c,v $
 *
 * AngeL IP protocol handler
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
 * $Id: angel_ip.c,v 1.2 2005/12/04 20:31:31 sp0nge Exp $
 */
#include "angel_ip.h"

static inline int __angel_is_fragmented(struct sk_buff *skb) {
	return (skb->nh.iph->frag_off != 0) ? 1 : 0;
}

static inline int __angel_have_id_set(struct sk_buff *skb) { 
	return (skb->nh.iph->id != 0) ? 1 : 0;
}

int angel_ip (struct iphdr *ip, struct sk_buff *skb) {
	if (__angel_ip_spoofing(skb)) {
		printk (KERN_INFO "[%s] %s(): spoofing detected against %d.%d.%d.%d\n",
				MY_NAME,
				__FUNCTION__,
				NIPQUAD(ip->daddr));
		return -1;
	}
				
	if ( ip->version != 4 )
		printk (KERN_INFO "[%s] %s(): warning no IPv4 traffic\n", 
				MY_NAME,
				__FUNCTION__);
	if ( ip->ihl != 5 ) {
		printk (KERN_INFO "[%s] IP options has been set. Dropping packet with IP header length %d\n",
				MY_NAME,
				ip->ihl);
		return -1;
	}
	return 0;
}

int __angel_ip_spoofing (const struct sk_buff *skb) 
{
	struct net_device *dev = dev_base;
	struct in_device *in_dev;
	struct in_ifaddr *ifap;

	spin_lock(&dev->queue_lock);
	for (dev = dev_base; dev; dev = dev->next) {
		/*
		 * dev->ip_ptr è un puntatore (void *) a dati riguardanti il
		 * protocollo IPv4.
		 *
		 * Quando, in futuro, si dovrà passare a IPv6 il puntatore da
		 * usare sarà dev->ip6_ptr.
		 */
		/*
		 * Il test qui sotto ha il seguente valore semantico:
		 * 	"se questo netdevice *NON* ha un puntatore valido a
		 * 	dati IP, allora passa al dispositivo successivo."
		 * La <continue> fa si che il codice successivo non venga
		 * eseguito ma si passi subito al passo successivo del ciclo
		 * for.
		 */
		if (!(in_dev = dev->ip_ptr))
			continue;
		/*
		 * in_dev->ifa_list è un puntatore (struct in_ifaddr *) che
		 * punta alla catena IP ifaddr.
		 */
		for (ifap = in_dev->ifa_list; ifap;ifap = ifap->ifa_next)
			if (skb->nh.iph->saddr == ifap->ifa_local) {
				/*
				 * Ho trovato un net device che ha come
				 * indirizzo IP quello specificato dalla
				 * skbuff, quindi non si tratta di uno
				 * spoofing.
				 */
				spin_unlock(&dev->queue_lock);
				return 0;
			}
	}
	/* 
	 * Spoofing in corso
	 */	 
	return 1;
}

