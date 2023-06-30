SUMMARY = "Recipe for  build an external mt7601u-ap Linux kernel module"
SECTION = "PETALINUX/modules"
LICENSE = "GPLv2"
LIC_FILES_CHKSUM = "file://COPYING;md5=12f884d2ae1ff87c09e5b7ccc2c4ca7e"

inherit module

KERNEL_MODULE_AUTOLOAD += "mt7601u-ap"

SRC_URI = "file://COPYING \
           file://Makefile \
           file://ap/* \
           file://ate/* \
           file://chips/* \
           file://common/* \
           file://include/* \
           file://mac/* \
           file://mcu/* \
           file://mgmt/* \
           file://os/* \
           file://phy/* \
           file://rate_ctrl/* \
           file://tools/* \
           file://RT2870AP.txt \
           "

do_install_append() {
    install -d ${D}/etc/wifi/RT2870AP
    install -m 644 ${S}/RT2870AP.txt ${D}/etc/wifi/RT2870AP/RT2870AP.txt
}

S = "${WORKDIR}"

EXTRA_OEMAKE = "\
		'ARCH=${TUNE_ARCH}' \
		'LINUX_SRC=${KERNEL_SRC}' \
		'CROSS_COMPILE=${CC}'"

FILES_${PN} += "/etc/wifi/RT2870AP"

# The inherit of module.bbclass will automatically name module packages with
# "kernel-module-" prefix as required by the oe-core build environment.





