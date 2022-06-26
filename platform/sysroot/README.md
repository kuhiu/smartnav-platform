# Sysroot link to download:

https://rcn-ee.com/rootfs/eewiki/minfs/ubuntu-18.04-minimal-armhf-2018-07-14.tar.xz

NOTE: Dont forget to unzip.

# Resolver el inicio de eth0 y ssh al iniciar el sistema

sudo vim /etc/netplan/netcfg.yaml 

# This file describes the network interfaces available on your system
# For more information, see netplan(5).
network:
  version: 2
  renderer: networkd
  ethernets:
    eno1:                       # Net name
      dhcp4: yes
      dhcp6: yes

Ref: https://askubuntu.com/questions/972429/how-to-bring-network-up-on-boot

# Note

I reduced the timeout in /lib/systemd/system/systemd-random-seed.service to reduce ssh login time. => FAILED] Failed to start Load/Save Random Seed.
