#
# This file is the smartnavsys recipe.
#

SUMMARY = "Simple smartnavsys application"
SECTION = "PETALINUX/apps"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

# Package name
PN = "smartnavsys-app"  

# Package version
PV = 0.0.1 

DEPENDS += "libtensorflowlite" 
DEPENDS += "opencv"

SRC_URI = "https://github.com/kuhiu/smartnavsys-app/archive/refs/tags/v0.0.1.zip;protocol=http"

SRC_URI[md5sum] = "ea1f88c4b692ad9f1deb7540cf93af1c"
SRC_URI[sha256sum] = "876534469957731d0b79653a19fd9117482340da363ee0518285759f55fce955"

S = "${WORKDIR}/${PN}-${PV}/files"

do_compile() {
	     oe_runmake
}

do_install() {
	     install -d ${D}${bindir}
	     install -m 0755 smartnavsys ${D}${bindir}
}
