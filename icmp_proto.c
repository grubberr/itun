/*
 *  Copyright (c) 2005 Sergey Chvalyuk <ant@unity.net>
 *  All Rights Reserved.
 *
 *  This file is part of the Icmp Tunnel - ITun.
 *
 *  ITun is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  ITun is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with Foobar; if not, write to the
 *  Free Software Foundation, Inc., 59 Temple Place, Suite 330,
 *  Boston, MA  02111-1307 USA.
 */
 
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip_icmp.h>
#include <stdlib.h>

#include "config.h"

int 
get_icmp(int sock,
         unsigned char * buff,
	 int buff_len,
	 struct sockaddr_in * addr,
	 socklen_t * len)
{
struct ip * ip;
struct icmp * icmp;
int ret,iphl;

ret = recvfrom(sock,buff,buff_len,0,(struct sockaddr *)addr,len);
if (ret)
{
   ip = (struct ip *) buff;
   iphl = ip->ip_hl << 2;
   icmp = (struct icmp *) (buff + iphl);
   if ((icmp->icmp_type == RECV_PKT)&&(icmp->icmp_id == ID))
   {
      memmove(buff,buff+(iphl+8),ret-(iphl+8));
      return(ret-(iphl+8));
   }
}
return(-1);
}

int 
send_icmp(int sock, 
	  unsigned char * buff,
	  int buff_len,
	  struct sockaddr_in * addr,
	  socklen_t len)
{
  int ret,cc;
  static u_char outpack[4096];
  struct icmp * icmp = (struct icmp *) outpack;
  
  icmp->icmp_type = SEND_PKT;
  icmp->icmp_code = 0;
  icmp->icmp_cksum = 0;
  icmp->icmp_seq = 0;
  icmp->icmp_id = ID;
  cc = 8 + buff_len;
  memcpy(&outpack[8],buff,buff_len);
  if ((ret = sendto(sock, outpack, cc, 0,(struct sockaddr *) addr, len)) < 0)
  {
     perror("icmp sendto");
     exit(1);
  }
  return(ret);
}
