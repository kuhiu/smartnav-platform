#
# This file is the smartnav-app recipe.
#

SUMMARY = "Simple smartnav-app application"
SECTION = "PETALINUX/apps"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

DEPENDS += "develop-smartnavlib"

SRC_URI = "	file://main.cpp \
						file://fuzzy_system_v0.json \
						file://fuzzy_system_v1.json \ 
						file://fuzzy_system_v2.json \ 
						file://fuzzy_system_v3.json \  
						file://fuzzy_system_v4.json " 

S = "${WORKDIR}"

EXTRA_OEMAKE = "\
    'LIBS=-lsmartnavsys'"

do_compile() {
	${CXX} ${CFLAGS} ${LDFLAGS} -o smartnav-app main.cpp -I${S} -li2c -ldevelop-smartnavlib -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_imgcodecs -ltensorflow-lite -ldl -lpthread  
}

do_install() {
		install -d ${D}${bindir}
		install -m 0755 smartnav-app ${D}${bindir}
		install -m 0755 fuzzy_system_v0.json ${D}${bindir}
		install -m 0755 fuzzy_system_v1.json ${D}${bindir}
		install -m 0755 fuzzy_system_v2.json ${D}${bindir}
		install -m 0755 fuzzy_system_v3.json ${D}${bindir}
		install -m 0755 fuzzy_system_v4.json ${D}${bindir}
}

FILES_${PN} += "smartnav-app"
