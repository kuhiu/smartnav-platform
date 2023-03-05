#
# This file is the smartnavsys-lib recipe.
#

SUMMARY = "Simple smartnavsys-lib application"
SECTION = "PETALINUX/apps"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

# Package name
PN="smartnavsys-lib"

# Package version
PV = "0.0.35"

DEPENDS += "tensorflowlite-lib" 
DEPENDS += "opencv"
DEPENDS += "jsonnlohmann"

SRC_URI = "https://github.com/kuhiu/smartnavsys-app/archive/refs/tags/v${PV}.zip;protocol=http"

SRC_URI[md5sum] = "0cad94e444883a6d91e0fb6e46ddbd7f"
SRC_URI[sha256sum] = "6f6c4858f8a39b01da2e98f2258908303b2b111c6b0cd94bedf14f7b5f19d2f1"

S = "${WORKDIR}/smartnav-lib-${PV}/files"

EXTRA_OEMAKE = "\
    'CC=${CC}' \
    'CXX=${CXX}' \
    'CPP=${CPP}' \
    'CFLAGS=${CFLAGS}' \
    'CPPFLAGS=${CFLAGS}' \
    'CXXFLAGS=${CXXFLAGS}' \
    'AR=${AR}' \
    'LD=${LD}' \
    'LDFLAGS=${LDFLAGS}' \
    'TARGET=${TARGET_OS}' \
    'TARGET_ARCH=${TUNE_ARCH}'"

do_compile() {
	     oe_runmak
}

do_install() {
    install -d ${D}${libdir}
		install -d ${D}${includedir}

    install -m 0644 ${S}/modules/*/*.hpp ${D}${includedir}
    ln -s -r ${S}/libsmartnavsys.so.0.0.23 ${D}/${libdir}/libsmartnavsys.so

    # install the prebuilt library in /usr/lib with default permissions
    oe_soinstall ${S}/libsmartnavsys.so.0.0.23 ${D}${libdir}
}

FILES_${PN} = "${libdir}/*.so.* ${libdir}/*.so ${includedir}/*"
FILES_${PN}-dev = "${libdir}/*.so"
ALLOW_EMPTY_${PN}="1"