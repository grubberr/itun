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

#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <linux/if.h>
#include <linux/if_tun.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netinet/ip_icmp.h>
#include <arpa/inet.h>

#include "config.h"

int get_icmp(int,unsigned char *,int,struct sockaddr_in *,socklen_t *);
int send_icmp(int,unsigned char *,int,struct sockaddr_in *,socklen_t);
int tun_open(char *dev);

int main()
{

unsigned char buff[4096];
fd_set rset;
struct sockaddr_in addr;
struct sockaddr_in addr_recv;
int sock;
int ret;
socklen_t len = sizeof(struct sockaddr_in);
socklen_t len_recv = sizeof(struct sockaddr_in);

unsigned char dev[] = IFACE;
int tunfd;

if ((tunfd = tun_open(dev)) < 0)
{
   perror("error: tun_open");
   exit(1);
}
sprintf(buff,"%s %s %s pointopoint %s",IFCFG,IFACE,VPN_LOCAL_IP,VPN_REMOTE_IP);
if (system(buff) < 0)
{
   perror("error: fork");
   exit(1);
}
if ((sock = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP)) < 0)
{
   perror("error: socket\n");
   exit(1);
}
memset(&addr,0,sizeof(struct sockaddr_in));
addr.sin_family = AF_INET;
addr.sin_port = 0;
addr.sin_addr.s_addr = inet_addr(PEER_IP);

while(1)
{ 
  FD_ZERO(&rset);
  FD_SET(sock,&rset);
  FD_SET(tunfd,&rset);
  while ((ret = select(sock+1,&rset,NULL,NULL,NULL)) < 0 && errno == EINTR);
  if (ret < 0)
  {
     perror("error: select");
     exit(1);
  }
  if (FD_ISSET(sock,&rset))
  {
    if ((ret = get_icmp(sock,buff,sizeof(buff),&addr_recv,&len_recv)) > 0)
    {
       //printf("get icmp pkt ret = %d ip = %s\n",ret,inet_ntoa(addr_recv.sin_addr));
       //print_DUMP(buff,ret);
       write(tunfd,buff,ret);
    }
  }
  if (FD_ISSET(tunfd,&rset))
  {
    ret = read(tunfd,buff,sizeof(buff));
    send_icmp(sock,buff,ret,&addr,len);
    //printf("send icmp pkt ret = %d ip = %s\n",ret,inet_ntoa(addr.sin_addr));
    //print_DUMP(buff,ret);
  }
}

return(0);
}
