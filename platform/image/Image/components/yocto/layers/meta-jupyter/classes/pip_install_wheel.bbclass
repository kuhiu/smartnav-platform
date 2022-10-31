DEPENDS:append = " python3-installer-native"

# The directory where wheels should be written too. Build classes
# will ideally [cleandirs] this but we don't do that here in case
# a recipe wants to install prebuilt wheels.
PIP_INSTALL_DIST_PATH ?= "${WORKDIR}/dist"

PIP_INSTALL_PYTHON = "python3"
PIP_INSTALL_PYTHON:class-native = "nativepython3"

INSTALL_WHEEL_COMPILE_BYTECODE ?= "--compile-bytecode=0"

pip_install_wheel_do_install () {
    COUNT=$(find ${PIP_INSTALL_DIST_PATH} -name '*.whl' | wc -l)
    if test $COUNT -eq 0; then
        bbfatal No wheels found in ${PIP_INSTALL_DIST_PATH}
    elif test $COUNT -gt 1; then
        bbfatal More than one wheel found in ${PIP_INSTALL_DIST_PATH}, this should not happen
    fi

    nativepython3 -m installer ${INSTALL_WHEEL_COMPILE_BYTECODE} --destdir=${D} ${PIP_INSTALL_DIST_PATH}/*.whl

    cd ${D}
    for i in ${D}${bindir}/* ${D}${sbindir}/*; do
        if [ -f "$i" ]; then
            sed -i -e "1s,#!.*nativepython3,#!${USRBINPATH}/env ${PIP_INSTALL_PYTHON}," $i
            sed -i -e "s:${PYTHON}:${USRBINPATH}/env\ ${PIP_INSTALL_PYTHON}:g" $i
            sed -i -e "s:${STAGING_BINDIR_NATIVE}:${bindir}:g" $i
            # Not everything we find may be Python, so ignore errors
            nativepython3 -mpy_compile $(realpath --relative-to=${D} $i) || true
        fi
    done
}

# A manual do_install that just uses unzip for bootstrapping purposes. Callers should DEPEND on unzip-native.
pip_install_wheel_do_bootstrap_install () {
    install -d ${D}${PYTHON_SITEPACKAGES_DIR}
    unzip -d ${D}${PYTHON_SITEPACKAGES_DIR} ${PIP_INSTALL_DIST_PATH}/*.whl
}

EXPORT_FUNCTIONS do_install
