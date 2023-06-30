#
# This file is the hostapd recipe.
#

SUMMARY = "Simple hostapd application"
SECTION = "PETALINUX/apps"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"
DEPENDS = "libnl openssl"

inherit update-rc.d systemd
INITSCRIPT_NAME = "hostapd"

SYSTEMD_SERVICE_${PN} = "hostapd.service"
SYSTEMD_AUTO_ENABLE_${PN} = "disable"

SRC_URI = " \
    http://w1.fi/releases/hostapd-${PV}.tar.gz \
    file://defconfig \
    file://init \
    file://hostapd.service \
    file://0001-hostapd-Avoid-key-reinstallation-in-FT-handshake.patch \
    file://0002-Prevent-reinstallation-of-an-already-in-use-group-ke.patch \
    file://0003-Extend-protection-of-GTK-IGTK-reinstallation-of-WNM-.patch \
    file://0004-Prevent-installation-of-an-all-zero-TK.patch \
    file://0005-Fix-PTK-rekeying-to-generate-a-new-ANonce.patch \
    file://0006-TDLS-Reject-TPK-TK-reconfiguration.patch \
    file://0008-FT-Do-not-allow-multiple-Reassociation-Response-fram.patch \
"

S = "${WORKDIR}/hostapd-${PV}"
B = "${WORKDIR}/hostapd-${PV}/hostapd"

do_configure() {
    install -m 0644 ${WORKDIR}/defconfig ${B}/.config
}

do_compile() {
    export CFLAGS="-MMD -O2 -Wall -g -I${STAGING_INCDIR}/libnl3"
    make
}

do_install() {
    install -d ${D}${sbindir} ${D}${sysconfdir}/init.d ${D}${systemd_unitdir}/system/
    install -m 0644 ${B}/hostapd.conf ${D}${sysconfdir}
    install -m 0755 ${B}/hostapd ${D}${sbindir}
    install -m 0755 ${B}/hostapd_cli ${D}${sbindir}
    install -m 755 ${WORKDIR}/init ${D}${sysconfdir}/init.d/hostapd
    install -m 0644 ${WORKDIR}/hostapd.service ${D}${systemd_unitdir}/system/
    sed -i -e 's,@SBINDIR@,${sbindir},g' -e 's,@SYSCONFDIR@,${sysconfdir},g' ${D}${systemd_unitdir}/system/hostapd.service
}

CONFFILES_${PN} += "${sysconfdir}/hostapd.conf"

SRC_URI[md5sum] = "236247a7bbd4f60d5fa3e99849d1ffc9"
SRC_URI[sha256sum] = "002e9dcb7e46cf82b5900a2fcf92b30fc8cdfd32a72d7fd4488588f1c013dfcc"