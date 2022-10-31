#
# This file is the persondetector recipe.
#

SUMMARY = "Simple persondetector application"
LICENSE = "MIT"
SECTION = "PETALINUX/apps"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

SRC_URI = "file://Makefile \
           file://main.cpp \
           file://Detector.cpp \
           file://Detector.hpp \
           file://RecognitionResult.hpp \
           file://VirtualImage.cpp \
           file://VirtualImage.hpp \
           file://PhyImage.cpp \
           file://PhyImage.hpp \
          "
 
S = "${WORKDIR}"
DEPENDS += "libtensorflowlite" 
DEPENDS += "opencv"

#TARGET_CC_ARCH \+= "${LDFLAGS}"
 
do_compile () {
	oe_runmake INCLUDE=${S}
}
 
do_install () {
	install -d ${D}${bindir}
	oe_runmake install DESTDIR=${D}
}