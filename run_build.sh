cd ./smartscout/smartscout-platform
../../etc/petalin.sh "petalinux-build && \ 
                      petalinux-package --boot --fsbl ./images/linux/zynq_fsbl.elf --fpga ./images/linux/system.bit --uboot --force"
