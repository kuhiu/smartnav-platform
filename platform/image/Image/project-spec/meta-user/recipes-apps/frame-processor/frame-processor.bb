#
# This file is the frame-processor recipe.
#

SUMMARY = "Simple frame-processor application"
SECTION = "PETALINUX/apps"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

SRC_URI ="file://Makefile \
					file://frame-processor.cpp \
					file://FrameProcessor.cpp \
					file://FrameProcessor.hpp \
					file://Detector.cpp \
					file://Detector.hpp \
					file://RecognitionResult.hpp \
					file://VirtualImage.cpp \
					file://VirtualImage.hpp \
					file://PhyImage.cpp \
					file://PhyImage.hpp \
					file://captureFrame.cpp \
					file://captureFrame.hpp \
					file://ColorSpaces.hpp \
		  		"

S = "${WORKDIR}"
DEPENDS += "libtensorflowlite" 
DEPENDS += "opencv"

do_compile() {
	     oe_runmake INCLUDE=${S}
}

do_install() {
	     install -d ${D}${bindir}
	     install -m 0755 frame-processor ${D}${bindir}
}
