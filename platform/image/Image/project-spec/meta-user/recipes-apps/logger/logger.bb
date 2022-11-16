#
# This file is the Logger recipe.
#

SUMMARY = "Simple Logger application"
SECTION = "PETALINUX/apps"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

SRC_URI = "	file://main.cpp \
						file://Logger.cpp \
						file://Logger.hpp \
						file://LogStream.cpp \
						file://LogStream.hpp \
						file://LogLevels.hpp \
           	file://Makefile \
		  		"

S = "${WORKDIR}"

do_compile() {
	     oe_runmake INCLUDE=${S}
}

do_install() {
	     install -d ${D}${bindir}
	     install -m 0755 Logger ${D}${bindir}
}
