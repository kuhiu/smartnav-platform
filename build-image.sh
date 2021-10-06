#!/bin/bash

VERSION=2021.1
docker build --build-arg PETA_VERSION=$VERSION                               \
             --build-arg PETA_RUN_FILE=petalinux-v2021.1-final-installer.run \
             -t petalinux:$VERSION                                           \
             .
