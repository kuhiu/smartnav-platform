SUMMARY = "Recipe for  build an external mailbox Linux kernel module"
SECTION = "PETALINUX/modules"
LICENSE = "GPLv2"
LIC_FILES_CHKSUM = "file://COPYING;md5=12f884d2ae1ff87c09e5b7ccc2c4ca7e"

inherit module

KERNEL_MODULE_AUTOLOAD += "mailbox"

SRC_URI = "file://Makefile \
           file://mailbox.c \
           file://mailbox.h \
	   file://COPYING \
          "

S = "${WORKDIR}"

do_install_append() {
    install -d ${D}${includedir}/
    install -m 644 ${S}/mailbox.h ${D}${includedir}/mailbox.h
}
FILES_${PN} += "${includedir}"

# The inherit of module.bbclass will automatically name module packages with
# "kernel-module-" prefix as required by the oe-core build environment.
