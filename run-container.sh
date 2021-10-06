#!/bin/bash

#
# Проверим что имеем хотя бы один аргумент
#
if [[ $# < 1 ]]; then
    echo -en "usage: $(basename $0) <project working directory> "
    exit 1
fi

#
# Проверим что директория проекта существует
#
if [ ! -d $1 ]; then
    echo "Директория проекта не сущуствует!"
    exit 2
fi

docker run                                                  \
    -ti                                                     \
    --rm                                                    \
    --privileged -v /dev/bus/usb:/dev/bus/usb               \
    -e DISPLAY=$DISPLAY                                     \
    -v /tmp/.X11-unix:/tmp/.X11-unix                        \
    --net="host"                                            \
    -v $HOME/.Xauthority:/home/vivado/.Xauthority           \
    -v $1:/home/vivado/project                              \
    petalinux:2021.1

#   -ti
#   интерактивный режим запуска контейнера 

#   --rm
#   удалить контейнер после выхода из него

#   --privileged -v /dev/bus/usb:/dev/bus/usb
#   проброс USB устройств

#   -e DISPLAY=$DISPLAY
#   сообщаем системе контейнера о номере номере дисплея на котором надо
#   запускать прилояжения

#   -v /tmp/.X11-unix:/tmp/.X11-unix
#   монтирование директории содержащей Unix Domain Socket использующейся Xorg
#   для взаимодействия с клиентами

#   -v $HOME/.Xauthority:/home/vivado/.Xauthority
#   мотирование файла содержащего куки системы авторизации Xorg

#   --net="host"
#   ключ указывающий использовать сеть хоста вместо создания NAT подсети в
#   контейнере и сетевого моста

#   -v $1:/home/vivado/project
#   монтирование рабочей директории

#   petalinux:2021.1
#   имя образа


exit $?
