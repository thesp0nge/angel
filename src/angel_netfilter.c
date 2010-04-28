/*
 * $RCSfile: angel_netfilter.c,v $
 *
 * Netfilter hook engine
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
 * $Id: angel_netfilter.c,v 1.3 2006/03/09 21:33:59 sp0nge Exp $
 */
#include "angel_netfilter.h"
#include "angel_ip.h"
#include "angel_tcp.h"
#include "angel_icmp.h"

#ifdef CONFIG_ANGEL_NETFILTER
static unsigned int __angel_output_hook(unsigned int hooknum,
		struct sk_buff **pskb,
		const struct net_device *in,
		const struct net_device *out,
		int (*okfn)(struct sk_buff *));
#endif

/*
 * @return 0 if netfilter hook can be registered or -1 otherwise
 */
int angel_netfilter_hook(void) {
	
#ifdef CONFIG_ANGEL_NETFILTER

	struct nf_hook_ops angel_output_hook_ops;
	int ret;

	printk(KERN_INFO "[%s] setting up outgoing chain hook...\n", MY_NAME);

	angel_output_hook_ops.hook 	= __angel_output_hook;
	angel_output_hook_ops.pf 	= PF_INET;
	angel_output_hook_ops.hooknum 	= NF_IP_POST_ROUTING;
	angel_output_hook_ops.priority 	= NF_IP_PRI_FIRST;

	ret = nf_register_hook(&angel_output_hook_ops);
	
	return ret;
#else
	printk(KERN_INFO "[%s] netfilter firewall disabled at kernel compile time, can't hook it\n", MY_NAME);
	return 0;
#endif
}

int angel_netfilter_unhook(void) {
	
#ifdef CONFIG_ANGEL_NETFILTER

	struct nf_hook_ops angel_output_hook_ops;
	int ret;

	printk(KERN_INFO "[%s] removing outgoing chain hook...\n", MY_NAME);

	angel_output_hook_ops.hook 	= __angel_output_hook;
	angel_output_hook_ops.pf 	= PF_INET;
	angel_output_hook_ops.hooknum 	= NF_IP_POST_ROUTING;
	angel_output_hook_ops.priority 	= NF_IP_PRI_FIRST;

	ret = nf_unregister_hook(&angel_output_hook_ops);
	
	return ret;
#else
	return 0;
#endif
}

#ifdef CONFIG_ANGEL_NETFILTER
static unsigned int __angel_output_hook(unsigned int hooknum,
		struct sk_buff **pskb,
		const struct net_device *in,
		const struct net_device *out,
		int (*okfn)(struct sk_buff *)) {

	struct sk_buff *skb = *pskb;
	struct iphdr *iphdr = (*pskb)->nh.iph;
	struct tcphdr *tcphdr;
	struct udphdr *udphdr;
	struct icmphdr *icmphdr;
;
	//struct icmphdr *icmp;
	int    ip_ret, proto, ret;

	proto = skb->nh.iph->protocol;

	ip_ret = angel_ip(iphdr, skb);
	if (ip_ret == -1) 
		goto error;
	switch (proto) {
		case IPPROTO_TCP:
			tcphdr = ((struct tcphdr *) (((char *) skb->nh.iph) + skb->nh.iph->ihl * 4));
			ret = angel_tcp(tcphdr, skb);
			if (ret == -1)
				goto error;
			break;
		case IPPROTO_UDP:
			udphdr = ((struct udphdr *) (((char *) skb->nh.iph) + skb->nh.iph->ihl * 4));
			break;
		case IPPROTO_ICMP:
			icmphdr = ((struct icmphdr *) (((char *) skb->nh.iph) + skb->nh.iph->ihl * 4));
			ret = angel_icmp(icmphdr, skb);

			break;
		case IPPROTO_IGMP:
			goto out;
			break;
		case IPPROTO_IPV6:
			printk (KERN_INFO "[%s] %s(): IPv6 protocol not yet supported\n",
					MY_NAME,
					__FUNCTION__);
			goto out;
			break;
		default:
			printk (KERN_INFO "[%s] %s(): protocol %d not supported\n",
					MY_NAME,
					__FUNCTION__,
					proto);
			goto out;
			break;
	}
			
	

out:
	return NF_ACCEPT;
error:
	return NF_DROP;
}
#endif
