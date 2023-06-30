#
# This file is the crow recipe.
#

SUMMARY = "Simple crow application"
SECTION = "PETALINUX/apps"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

DEPENDS += "boost"

SRC_URI = "	git://github.com/CrowCpp/Crow.git;branch=v1.0;rev=v1.0;protocol=https \
	"

S = "${WORKDIR}/git"

do_install() {
	install -d ${D}${includedir}
	install -d ${D}${includedir}/crow
	install -d ${D}${includedir}/crow/middlewares

	install -m 0755 ${S}/include/crow.h ${D}${includedir}/

	install -m 0755 ${S}/include/crow/TinySHA1.hpp ${D}${includedir}/crow/TinySHA1.hpp
	install -m 0755 ${S}/include/crow/app.h ${D}${includedir}/crow/app.h
	install -m 0755 ${S}/include/crow/ci_map.h ${D}${includedir}/crow/ci_map.h
	install -m 0755 ${S}/include/crow/common.h ${D}${includedir}/crow/common.h
	install -m 0755 ${S}/include/crow/compression.h ${D}${includedir}/crow/compression.h
	install -m 0755 ${S}/include/crow/http_connection.h ${D}${includedir}/crow/http_connection.h
	install -m 0755 ${S}/include/crow/http_parser_merged.h ${D}${includedir}/crow/http_parser_merged.h
	install -m 0755 ${S}/include/crow/http_request.h ${D}${includedir}/crow/http_request.h
	install -m 0755 ${S}/include/crow/http_response.h ${D}${includedir}/crow/http_response.h
	install -m 0755 ${S}/include/crow/http_server.h ${D}${includedir}/crow/http_server.h
	install -m 0755 ${S}/include/crow/json.h ${D}${includedir}/crow/json.h
	install -m 0755 ${S}/include/crow/logging.h ${D}${includedir}/crow/logging.h
	install -m 0755 ${S}/include/crow/middleware.h ${D}${includedir}/crow/middleware.h
	install -m 0755 ${S}/include/crow/multipart.h ${D}${includedir}/crow/multipart.h
	install -m 0755 ${S}/include/crow/mime_types.h ${D}${includedir}/crow/mime_types.h
	install -m 0755 ${S}/include/crow/mustache.h ${D}${includedir}/crow/mustache.h
	install -m 0755 ${S}/include/crow/parser.h ${D}${includedir}/crow/parser.h
	install -m 0755 ${S}/include/crow/query_string.h ${D}${includedir}/crow/query_string.h
	install -m 0755 ${S}/include/crow/returnable.h ${D}${includedir}/crow/returnable.h
	install -m 0755 ${S}/include/crow/routing.h ${D}${includedir}/crow/routing.h
	install -m 0755 ${S}/include/crow/settings.h ${D}${includedir}/crow/settings.h
	install -m 0755 ${S}/include/crow/socket_adaptors.h ${D}${includedir}/crow/socket_adaptors.h
	install -m 0755 ${S}/include/crow/utility.h ${D}${includedir}/crow/utility.h
	install -m 0755 ${S}/include/crow/websocket.h ${D}${includedir}/crow/websocket.h
	install -m 0755 ${S}/include/crow/task_timer.h ${D}${includedir}/crow/task_timer.h
	install -m 0755 ${S}/include/crow/middleware_context.h ${D}${includedir}/crow/middleware_context.h
	install -m 0755 ${S}/include/crow/version.h ${D}${includedir}/crow/version.h

	install -m 0755 ${S}/include/crow/middlewares/cookie_parser.h ${D}${includedir}/crow/middlewares/cookie_parser.h
	install -m 0755 ${S}/include/crow/middlewares/cors.h ${D}${includedir}/crow/middlewares/cors.h
	install -m 0755 ${S}/include/crow/middlewares/utf-8.h ${D}${includedir}/crow/middlewares/utf-8.h
}

FILES_${PN} = "${libdir}/*.so.* ${includedir}/*"
FILES_${PN}-dev = "${libdir}/*.so"
ALLOW_EMPTY_${PN}="1"