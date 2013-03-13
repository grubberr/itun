#!/bin/bash

# make default routing via icmp tun
# but icmp pkt route via real iface for tun working

iptables -t mangle -A OUTPUT -p icmp -j MARK --set-mark 5
iptables -t nat -A POSTROUTING -o eth0 -p icmp -j SNAT --to-source 10.20.2.16

ip rule add fwmark 5 lookup icmp
ip route add 10.95.1.1 dev tun0 scope link src 10.95.1.2 table icmp
ip route add default via 10.20.1.1 src 10.20.2.16 table icmp

# switch main default routing to Tun iface
ip route del default
ip route add default via 10.95.1.1

# swith mtu 1472 to avoid icmp fragmentation
ifconfig tun0 mtu 1472
