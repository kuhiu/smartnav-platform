#
# This file is the develop-smartnavlib recipe.
#

SUMMARY = "Simple develop-smartnavlib application"
SECTION = "PETALINUX/apps"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

# Package name
PN="develop-smartnavlib"
PN_LIB = "lib${PN}"

# Package version
PV = "0.0.67"

SRC_URI = "file://Makefile \
		 file://modules/capture-frame/* \
		 file://modules/frame-processor/* \
		 file://modules/fuzzy-control-system/* \
		 file://modules/hc-sr04/* \
		  "

DEPENDS += "tensorflowlite-lib" 
DEPENDS += "opencv"
DEPENDS += "jsonnlohmann"

S = "${WORKDIR}"

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
    'LIB_NAME=${PN_LIB}' \
    'LIB_VERSION=${PV}' \
    'TARGET_ARCH=${TUNE_ARCH}'"

do_compile() {
	     oe_runmake
}

do_install() {
    install -d ${D}${libdir}
		install -d ${D}${includedir}

    install -m 0644 ${S}/modules/*/*.hpp ${D}${includedir}
    ln -s -r ${S}/${PN_LIB}.so.${PV} ${D}/${libdir}/${PN_LIB}.so

    # install the prebuilt library in /usr/lib with default permissions
    oe_soinstall ${S}/${PN_LIB}.so.${PV} ${D}${libdir}
}

FILES_${PN} = "${libdir}/*.so.* ${libdir}/*.so ${includedir}/*"
FILES_${PN}-dev = "${libdir}/*.so"
ALLOW_EMPTY_${PN}="1"