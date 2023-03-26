cd ./smartscout/smartscout-platform && \
sh update_hds.sh && \
../../etc/petalin.sh "petalinux-build -x mrproper && \
                      petalinux-config --oldconfig --get-hw-description . && \
                      petalinux-config -c kernel --oldconfig && \
                      petalinux-config -c rootfs --oldconfig && \ 
                      petalinux-build && \ 
                      petalinux-package --boot --fsbl ./images/linux/zynq_fsbl.elf --fpga ./images/linux/system.bit --uboot"