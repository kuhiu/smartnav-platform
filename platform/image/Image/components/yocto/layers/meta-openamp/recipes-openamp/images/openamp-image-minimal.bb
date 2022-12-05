DESCRIPTION = "A minimal OpenAMP image"

INITRD_IMAGE = "core-image-minimal-initramfs"
LICENSE = "MIT"

inherit core-image

IMAGE_INSTALL += " \
    packagegroup-core-boot \
    ${CORE_IMAGE_EXTRA_INSTALL} \
    kernel-module-uio-pdrv-genirq \
    kernel-module-virtio-rpmsg-bus \
    libmetal \
    open-amp \
    "

IMAGE_INSTALL:append:zynqmp = " kernel-module-zynqmp-r5-remoteproc \
                                packagegroup-petalinux-openamp "
IMAGE_INSTALL:append:versal = " kernel-module-zynqmp-r5-remoteproc \
                                packagegroup-petalinux-openamp "
IMAGE_INSTALL:append:zynq = " kernel-module-zynq-remoteproc"

IMAGE_INSTALL:append = " openssh openssh-sshd openssh-sftp openssh-sftp-server"
IMAGE_LINGUAS=""
