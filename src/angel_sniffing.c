/*
 * $RCSfile: angel_sniffing.c,v $
 * Creation date: 20.09.2005
 * Author: Paolo Perego - sponge@sikurezza.org
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
 * $Id: angel_sniffing.c,v 1.1.1.1 2005/10/06 21:47:21 sp0nge Exp $
 */

#include "angel_sniffing.h"
	   
/*
 * Checks if the requested family and type socket parameters could lead to a
 * packet socket creation or not.
 * @family socket family code
 * @type socket type code
 * Return 0 if the requested operation is valid or -1 if this could be a
 * sniffing attempt.  
 */
int angel_is_sniffing_via_socket(int family, int type) {
   if ((family==PF_INET) && (type==SOCK_PACKET))
      return -1;
   if (family==PF_PACKET) 
      return -1;
   return 0;
}

/*
 * Checks if we are trying to put the network interface into promiscous mode
 * via ioctl call.
 * @ifr the parameters that we want to bind to network interface using ioctl()
 * Return 0 if the requested operation is valid or -1 if this could be a
 * sniffing attempt.
 */
int angel_is_sniffing_via_ioctl(struct ifreq *ifr) {
   return (ifr->ifr_flags & IFF_PROMISC)? -1:0;
}

int angel_file_ioctl(struct file *file, unsigned int command, unsigned long arg) 
{
	struct ifreq *ifr;
	if (command == SIOCSIFFLAGS) {
		ifr = (struct ifreq *)arg;
		if (angel_is_sniffing_via_ioctl(ifr) == -1) 
			return -1;
	}
	return 0;
}

