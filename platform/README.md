# Platform

Here you can find the platform used.

# Sysroot

* https://rcn-ee.com/rootfs/eewiki/minfs/

# How to build Linux imagen and FPGA config (BOOT.BIN and image.ub)

## Pre-requirements

* Vivavdo 2019.1
* Linux 16.04 LTS 
* Petalinux toolchain

# system-user.dtsi location

* <Petalinux_Projects>/project-spec/meta-user/recipes-bsp/device-tree/

## Run Vivado in terminal 

* source /tools/Xilinx/Vivado/2019.1/settings64.sh
* run vivado
* Generate Bitstream.
* File->Export Hardware (include bitstream)->ok (.HDF generated)
* File->Export Bitstream File (.BIT generated)

## Petalinux
 
* petalinux-create --type project --template zynq --name Image 
* cd Image
* petalinux-config --get-hw-description "dir path to dir where .HDF was generated" AND go to "Select Image Packaging Configuration" > "Root File System Type" and select micro SD card.
* petalinux-config -c kernel
* petalinux-config -c rootfs and enable i2c-tools
* petalinux-build (check pl.dtsi, freq of axi timer error)
* petalinux-package --boot --fsbl ./images/linux/zynq_fsbl.elf --fpga ./images/linux/system.bit --uboot
* BOOT.BIN and image.ub was generated in images folder.

## Format an SD card with two partitions: 

* The first should be at least 500 MB and be FAT formatted. 
* The second needs to be at least 1.5 GB (3 GB is preferred) and formatted as ext4.
* Copy images/linux/BOOT.BIN and images/linux/image.ub to the first partition of your SD card.
* Copy sysroot folder into the second partition of your SD card.

# How to build TCL project

In vivado: 

* File->Project->Write_TCL
* Tick Recreate Block Designs using TCL.


