#
# This file is the smartnav-app-init recipe.
#

SUMMARY = "Simple smartnav-app-init application"
SECTION = "PETALINUX/apps"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

SRC_URI = "file://smartnav-app-init \
	"

S = "${WORKDIR}"

DEPENDS += "develop-smartnavlib"

FILESEXTRAPATHS_prepend := "${THISDIR}/files:"

inherit update-rc.d

INITSCRIPT_NAME = "smartnav-app-init"
INITSCRIPT_PARAMS = "start 99 S ."

do_install() {
        install -d ${D}${sysconfdir}/init.d
        install -m 0755 ${S}/smartnav-app-init ${D}${sysconfdir}/init.d/smartnav-app-init
}
FILES_${PN} += "${sysconfdir}/*"