#
# This file is the jsonnlohmann recipe.
#

SUMMARY = "Simple jsonnlohmann application"
SECTION = "PETALINUX/apps"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

SRC_URI = "git://github.com/nlohmann/json.git;nobranch=1 \
           "

SRCREV = "bc889afb4c5bf1c0d8ee29ef35eaaf4c8bef8a5d"

PN = "jsonnlohmann"
S = "${WORKDIR}/git"

inherit cmake

EXTRA_OECMAKE += "-DJSON_BuildTests=OFF"

# nlohmann-json is a header only C++ library, so the main package will be empty.

BBCLASSEXTEND = "native nativesdk"

# other packages commonly reference the file directly as "json.hpp"
# create symlink to allow this usage
do_install() {
		install -d ${D}${includedir}/nlohmann
    install -m 0644 ${S}/single_include/nlohmann/json.hpp ${D}${includedir}/nlohmann
}

FILES_${PN} = "${libdir}/*.so.* ${includedir}/*"
FILES_${PN}-dev = "${libdir}/*.so"
ALLOW_EMPTY_${PN}="1"
