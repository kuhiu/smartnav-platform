#
# This file is the CaptureFrame recipe.
#

SUMMARY = "Simple CaptureFrame application"
SECTION = "PETALINUX/apps"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

SRC_URI = "	file://main.cpp \
						file://CaptureFrame.cpp \
						file://CaptureFrame.hpp \
						file://VirtualImage.cpp \
						file://VirtualImage.hpp \
						file://ColorSpaces.hpp \
						file://modules/Logger/Logger.cpp \
						file://modules/Logger/Logger.hpp \
						file://modules/Logger/LogLevels.hpp \
						file://modules/Logger/LogStream.cpp \
						file://modules/Logger/LogStream.hpp \
           	file://Makefile \
		  		"

S = "${WORKDIR}"
DEPENDS += "opencv"
DEPENDS += "libtensorflowlite" 

do_compile() {
	     oe_runmake INCLUDE=${S}
}

do_install() {
	     install -d ${D}${bindir}
	     install -m 0755 CaptureFrame ${D}${bindir}
}
