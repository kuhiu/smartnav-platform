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
PV = "0.1.314"

SRC_URI = "file://Makefile \
		 file://modules/capture-frame/* \
		 file://modules/fuzzy-control-system/* \
		 file://modules/hc-sr04/* \
     file://modules/driver/* \
     file://modules/headlights/* \
     file://modules/compass/* \
     file://modules/mailbox/* \
     file://modules/position-estimator/* \
     file://modules/utilities/* \
     file://modules/decayGraph/* \
     file://modules/obstacle/* \
     file://SmartNav.hpp \
     file://SmartNav.cpp \
		  "
DEPENDS += "mailbox"
DEPENDS += "tensorflowlite-lib" 
DEPENDS += "opencv"
DEPENDS += "jsonnlohmann"
DEPENDS += "i2c-tools"

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
    install -m 0644 ${S}/SmartNav.hpp ${D}${includedir}
    ln -s -r ${S}/${PN_LIB}.so.${PV} ${D}/${libdir}/${PN_LIB}.so

    install -d ${D}${bindir}
    install -m 0755 ${S}/modules/capture-frame/lite-model_efficientdet_lite0_detection_default_1.tflite ${D}${bindir}

    # install the prebuilt library in /usr/lib with default permissions
    oe_soinstall ${S}/${PN_LIB}.so.${PV} ${D}${libdir}
}

FILES_${PN} = "${libdir}/*.so.* ${libdir}/*.so ${includedir}/* ${bindir}/*"
FILES_${PN}-dev = "${libdir}/*.so"
ALLOW_EMPTY_${PN}="1"