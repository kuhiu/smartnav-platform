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
PV = "0.2.106"

SRC_URI = "file://Makefile \
		 file://modules/capture-frame/* \
		 file://modules/fuzzy-control-system/* \
		 file://modules/distance-sensors/* \
     file://modules/driver/* \
     file://modules/headlights/* \
     file://modules/compass/* \
     file://modules/mailbox/* \
     file://modules/position-estimator/* \
     file://modules/utilities/* \
     file://modules/decayGraph/* \
     file://modules/obstacle/* \
     file://modules/buttons/* \
     file://modules/tracker/* \
     file://modules/reporter/* \
     file://modules/webserver/* \
     file://modules/frame-processor/* \
     file://modules/camera-sender/* \
     file://modules/pixel-magic/* \
     file://SmartEvasion/* \
     file://SmartLights/* \
     file://SmartNav.hpp \
     file://SmartNav.cpp \
		  "
DEPENDS += "mailbox"
DEPENDS += "buttons"
DEPENDS += "tensorflowlite-lib" 
DEPENDS += "opencv"
DEPENDS += "jsonnlohmann"
DEPENDS += "i2c-tools"
DEPENDS += "crow"

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
    oe_runmake clean
    oe_runmake
}

do_install() {
    install -d ${D}${libdir}
		install -d ${D}${includedir}
    install -d ${D}${bindir}
    install -d ${D}${sysconfdir}
    install -d ${D}${sysconfdir}/webserver/templates

    install -m 0644 ${S}/modules/*/*.hpp ${D}${includedir}
    install -m 0644 ${S}/SmartEvasion/*.hpp ${D}${includedir}
    install -m 0644 ${S}/SmartLights/*.hpp ${D}${includedir}
    install -m 0644 ${S}/SmartNav.hpp ${D}${includedir}
    ln -s -r ${S}/${PN_LIB}.so.${PV} ${D}/${libdir}/${PN_LIB}.so

    install -m 0755 ${S}/modules/frame-processor/lite-model_efficientdet_lite0_detection_default_1.tflite ${D}${bindir}
    install -m 0755 ${S}/modules/webserver/templates/* ${D}${sysconfdir}/webserver/templates
		install -m 0755 ${S}/SmartEvasion/SmartEvasion-stage-1.json ${D}${bindir}
    install -m 0755 ${S}/SmartEvasion/SmartEvasion-stage-2.json ${D}${bindir}
    install -m 0755 ${S}/SmartLights/SmartLights-stage-1.json ${D}${bindir}

    # install the prebuilt library in /usr/lib with default permissions
    oe_soinstall ${S}/${PN_LIB}.so.${PV} ${D}${libdir}
}

FILES_${PN} = "${libdir}/*.so.* ${libdir}/*.so ${includedir}/* ${bindir}/* ${sysconfdir}/*"
FILES_${PN}-dev = "${libdir}/*.so"
ALLOW_EMPTY_${PN}="1"