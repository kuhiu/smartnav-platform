#
# This file is the wireless recipe.
#

SUMMARY = "Simple wireless application"
SECTION = "PETALINUX/apps"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

SRC_URI = " file://mt7601u.bin \
            file://udhcpd.conf \
            file://setup \
            "

S = "${WORKDIR}"

FILESEXTRAPATHS_prepend := "${THISDIR}/files:"

inherit update-rc.d

INITSCRIPT_NAME = "setup"
INITSCRIPT_PARAMS = "start 99 S ."

do_install() {
    install -d ${D}/lib/firmware
    install -d ${D}${sysconfdir}
    install -d ${D}${sysconfdir}/smartnav
    install -d ${D}${sysconfdir}/init.d
    
    install -m 0755 ${S}/setup ${D}${sysconfdir}/init.d/setup
    install -m 0755 ${S}/udhcpd.conf ${D}${sysconfdir}/smartnav/udhcpd.conf
    install -m 0755 ${S}/mt7601u.bin ${D}/lib/firmware/mt7601u.bin
}

FILES_${PN} += "/lib/firmware/mt7601u.bin"
FILES_${PN} += "${sysconfdir}/*"
