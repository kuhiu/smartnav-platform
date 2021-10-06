FROM ubuntu:18.04

# Project was forked from github.com/z4yx/petalinux-docker
MAINTAINER Bolshevikov <bolshevikov.igor@gmail.com>

RUN apt-get update &&  DEBIAN_FRONTEND=noninteractive apt-get install -y -q \
    apt-utils           \
    autoconf            \
    automake            \
    bc                  \
    bison               \
    build-essential     \
    chrpath             \
    cpio                \
    default-jre         \
    diffstat            \
    expect              \
    flex                \
    gawk                \
    gcc-multilib        \
    git                 \
    git-gui             \
    glib2.0             \
    gnupg               \
    gzip                \
    iproute2            \
    kmod                \
    lib32z1             \
    lib32z1-dev         \
    libglib2.0-dev      \
    libgtk2.0-0         \
    libncurses5-dev     \
    libsdl1.2-dev       \
    libsdl-dev          \
    libselinux1         \
    libssl-dev          \
    libtool             \
    libtool-bin         \
    locales             \
    lsb-release         \
    make                \
    mc                  \
    net-tools           \
    pax                 \
    python3             \
    rsync               \
    screen              \
    socat               \
    sudo                \
    tar                 \
    texinfo             \
    tftpd               \
    tofrodos            \
    u-boot-tools        \
    unzip               \
    update-inetd        \
    vim                 \
    wget                \
    x11-utils           \
    xterm               \
    xvfb                \
    zlib1g-dev          \
    cmake               \
    gcc-8               \
    gdb                 \
    cgdb                \
    qtcreator           \
    ssh                 \
    iputils-ping        \
    parted              \
    xfonts-terminus     \
 && apt-get clean \
 && rm -rf /var/lib/apt/lists/*

RUN    dpkg --add-architecture i386                                         \
    && apt-get update                                                       \
    && DEBIAN_FRONTEND=noninteractive apt-get install -y -q zlib1g:i386     \
    && apt-get clean                                                        \
    && rm -rf /var/lib/apt/lists/*


RUN locale-gen en_US.UTF-8 && update-locale

# Создаем пользователя
RUN adduser --disabled-password --gecos '' user   && \
    usermod -aG sudo user                         && \
    echo "user ALL=(ALL) NOPASSWD: ALL" >> /etc/sudoers

# Пароль пользователя
RUN sudo usermod -p $(openssl passwd 1) user

#
# Установка Petalinux
#
ARG PETA_VERSION
ARG PETA_RUN_FILE
COPY .accept-eula.sh ${PETA_RUN_FILE} /

# run the install
RUN chmod a+rx /${PETA_RUN_FILE} && \
    chmod a+rx /.accept-eula.sh  && \
    mkdir -p /opt/Xilinx         && \
    chmod 777 /tmp /opt/Xilinx   && \
    cd /tmp                      && \
    sudo -u user -i /.accept-eula.sh /${PETA_RUN_FILE} /opt/Xilinx/petalinux && \
    rm -f /${PETA_RUN_FILE} /.accept-eula.sh

# Petalinux хочет bash, поэтому сделаем симлинки
RUN echo "dash dash/sh boolean false" | debconf-set-selections
RUN DEBIAN_FRONTEND=noninteractive dpkg-reconfigure dash
RUN sudo ln -fs /bin/bash /bin/sh

USER user
ENV HOME /home/uer
ENV LANG en_US.UTF-8

#
# Установка дополнительного софта и конфигурационных файлов
#
WORKDIR ${HOME}
COPY ./soft_for_container ./soft_for_container
# конфигурация mc
RUN  cat ./soft_for_container/bash/bashrc_extend >> ~/.bashrc
# конфигурация mc
RUN  mkdir -p ~/.config/; cp -r ./soft_for_container/mc ~/.config/
RUN  sudo mkdir -p /root/.config/; sudo cp -r ./soft_for_container/mc /root/.config/
# почистим за собой
RUN  sudo rm -rf ./soft_for_container

# создадим директорию в которую будем монтировать проект
RUN mkdir /home/user/project

WORKDIR   /home/user/project


#
# Настройка bashrc
#
# добавим конфиги Petalinux в bashrc
RUN echo 'echo "Run petaLinux SDK"'                 >> ~/.bashrc
RUN echo "source /opt/Xilinx/petalinux/settings.sh" >> /home/user/.bashrc

# Установим python3 дефолтным питоном (required by petalinux)
RUN echo 'alias python=python3' >> ~/.bashrc
RUN echo 'export LANG=en_US.UTF-8' >> ~/.bashrc
# копируем bashrc в root, чтоб оттуда тоже можно было работать
RUN sudo cp ~/.bashrc /root/

#
# Доп настройки
#

# какая-то магия которую я нашел в сети Интернет
RUN sudo ln -fs /usr/lib/x86_64-linux-gnu/libpcre16.so.3 /usr/lib/x86_64-linux-gnu/libpcre16.so.0 # neded by QT5 uuic ...

# установим московский часовой пояс
RUN if [[ -f /etc/localtime ]]; then sudo rm /etc/localtime; fi
RUN sudo ln -s /usr/share/zoneinfo/Europe/Moscow /etc/localtime

# запустим демон ssh
ENTRYPOINT sudo service ssh start && /bin/bash

