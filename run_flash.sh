#!/bin/sh

sudo rm -rf /media/kuhiu/66E8-BA73/*
sudo rm -rf /media/kuhiu/5addf18c-5fdf-457c-ba4d-1343c6dece0d/*

cp ./smartscout/smartscout-platform/images/linux/BOOT.BIN /media/kuhiu/66E8-BA73
cp ./smartscout/smartscout-platform/images/linux/image.ub /media/kuhiu/66E8-BA73

sudo tar xvf ./smartscout/smartscout-platform/images/linux/rootfs.tar.gz -C /media/kuhiu/5addf18c-5fdf-457c-ba4d-1343c6dece0d/