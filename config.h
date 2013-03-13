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

// IP address of remote peer
#define PEER_IP "195.24.141.97"

// Name of local tunnel interface
#define IFACE "tun0"

// Local IP address for tunnel
#define VPN_LOCAL_IP "10.95.1.2"

// Remote IP address for tunnel
#define VPN_REMOTE_IP "10.95.1.1"

// Full path to ifconfig 
#define IFCFG "/sbin/ifconfig"

/*
 * Connection schemes - type of ICMP packets
 * which will be used for connection
 */

// Connection scheme 1 (ICMP client)
#define SEND_PKT ICMP_ECHO
#define RECV_PKT ICMP_ECHOREPLY

// Connection scheme 2 (ICMP server)
//#define SEND_PKT ICMP_ECHOREPLY
//#define RECV_PKT ICMP_ECHO

// Connection scheme 3
//#define SEND_PKT ICMP_ECHOREPLY
//#define RECV_PKT ICMP_ECHOREPLY

// ID mast be equal on both peers 
#define ID 65534

#define HAVE_LINUX_IF_TUN_H 1
