SUMMARY = "Recipe for  build an external hmc5883l Linux kernel module"
SECTION = "PETALINUX/modules"
LICENSE = "GPLv2"
LIC_FILES_CHKSUM = "file://COPYING;md5=12f884d2ae1ff87c09e5b7ccc2c4ca7e"

inherit module

# KERNEL_MODULE_AUTOLOAD += "hmc5883l"

SRC_URI = "file://Makefile \
           file://hmc5883l.c \
	   file://COPYING \
          "

S = "${WORKDIR}"

# The inherit of module.bbclass will automatically name module packages with
# "kernel-module-" prefix as required by the oe-core build environment.