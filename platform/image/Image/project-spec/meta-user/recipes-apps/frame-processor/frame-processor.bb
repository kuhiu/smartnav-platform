#
# This file is the frame-processor recipe.
#

SUMMARY = "Simple frame-processor application"
SECTION = "PETALINUX/apps"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

SRC_URI = "	file://main.cpp \
						file://Detector.cpp \
						file://Detector.hpp \
						file://FrameProcessor.cpp \
						file://FrameProcessor.hpp \
						file://RecognitionResult.hpp \
						file://modules/capture-frame/VirtualImage.cpp \
						file://modules/capture-frame/VirtualImage.hpp \
						file://modules/capture-frame/ColorSpaces.hpp \
						file://modules/capture-frame/CaptureFrame.cpp \
						file://modules/capture-frame/CaptureFrame.hpp \
						file://modules/Logger/Logger.cpp \
						file://modules/Logger/Logger.hpp \
						file://modules/Logger/LogLevels.hpp \
						file://modules/Logger/LogStream.cpp \
						file://modules/Logger/LogStream.hpp \
           	file://Makefile \
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
