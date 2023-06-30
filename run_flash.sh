#!/bin/sh

sudo rm -rf /media/kuhiu/5623-FB79/*
sudo rm -rf /media/kuhiu/f41dda77-6f0a-4d31-bbce-d3d6fe82e09e/*

cp ./smartscout/smartscout-platform/images/linux/BOOT.BIN /media/kuhiu/5623-FB79
cp ./smartscout/smartscout-platform/images/linux/image.ub /media/kuhiu/5623-FB79

sudo tar xvf ./smartscout/smartscout-platform/images/linux/rootfs.tar.gz -C /media/kuhiu/f41dda77-6f0a-4d31-bbce-d3d6fe82e09e/
