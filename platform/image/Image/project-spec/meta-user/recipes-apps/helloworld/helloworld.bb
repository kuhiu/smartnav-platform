SUMMARY = "helloworld application"
LICENSE = "MIT"
SECTION = "PETALINUX/apps"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"
 
SRC_URI = "file://Makefile \
           file://helloworld.cpp \
           file://inc/ \
          "
 
S = "${WORKDIR}"
 
#TARGET_CC_ARCH \+= "${LDFLAGS}"
 
do_compile () {
	oe_runmake INCLUDE=${S}/inc
}
 
do_install () {
	install -d ${D}${bindir}
	oe_runmake install DESTDIR=${D}
}