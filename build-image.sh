#!/bin/bash

VERSION=2021.1
docker build --build-arg PETA_VERSION=$VERSION                               \
             --build-arg PETA_RUN_FILE=petalinux-v2019.1-final-installer.run \
             -t petalinux:2019.1                                             \
             .
