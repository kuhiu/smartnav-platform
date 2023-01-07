Contenedor de compilación para Petalinux
El proyecto está diseñado para contenerizar el proceso de compilación de Petalinux. Se anuncia el soporte de Petalinux para RedHat, CentOS, Ubuntu. Versiones específicas
Las distribuciones admitidas dependen de la versión de petalinux. Para asegurar la portabilidad de compilación entre diferentes distribuciones, puede ser apropiado
mover el proceso de compilación a un contenedor.

Montaje de contenedores

Para compilar, debe copiar el archivo de configuración de petalinux en el directorio con este proyecto. El nombre del archivo de instalación se debe pasar en el archivo
build-image.sh al argumento PETA_RUN_FILE. También es necesario especificar el número de la versión instalada en la variable VERSIÓN.
El contenedor ensamblado ocupa alrededor de 20 Gb de espacio en el disco duro, pero puede requerir espacio adicional durante el proceso de construcción.

Ejecutar un contenedor

El contenedor se inicia mediante el script run-container.sh desde la terminal. Primero debe especificar el nombre correcto del contenedor en el script (por defecto
petalinux:2021.1).
El script toma un único argumento: la ruta del directorio con el proyecto petalinux en el host (el directorio puede estar vacío y el proyecto ya se puede crear en un contenedor en ejecución).
Porque el contenedor se inicia en modo interactivo, luego, después del lanzamiento, debería aparecer una terminal que se ejecuta dentro del contenedor.
Para su correcto funcionamiento, petalinux requiere la inicialización de las variables de entorno, pero en este caso esto no es necesario, porque. este paso se tiene en cuenta al construir la imagen del contenedor.
Para mayor comodidad, se han agregado alias para comandos básicos al shell del contenedor.

petalinux:

petalinux-build - plbuild
petalinux-create-plcreate
petalinux-config - plconfig


Cuando se inicia dentro del contenedor, se genera ssh (puede deshabilitarlo eliminando el comando de la última línea en el Dockerfile:

ENTRYPOINT sudo service ssh start && /bin/bash

personalización
Se han agregado comandos al script de inicio del contenedor que le permiten iniciar aplicaciones gráficas desde un contenedor. Petalinux no contiene una GUI, pero puede ser útil en algunos casos.
Es posible cambiar un contenedor de modo interactivo a modo por lotes. En este caso, puede ejecutar comandos o scripts desde la terminal del host, como si se estuvieran ejecutando en el host y no desde el contenedor (puede ser útil en caso de que
automatización del proceso de montaje). Para esto:


en Dockerfile elimine la línea con ENTRYPOINT:

ENTRYPOINT sudo service ssh start && /bin/bash


Si se necesita ssh, se puede iniciar con un comando separado:

EJECUTAR sudo service ssh start

En run-container.sh , modifique la parte que inicia el comando de ejecución de la ventana acoplable para
algo como esto":

PROJ_DIR=$1
turno

ventana acoplable ejecutar \
     -ti \
     --rm \
     --privilegiado -v /dev/bus/usb:/dev/bus/usb \
     -e PANTALLA=$PANTALLA \
     -v /tmp/.X11-unix:/tmp/.X11-unix \
     --net="host" \
     -v $HOME/.Xautoridad:/home/vivado/.Xautoridad\
     -v $PROJ_DIR:/home/vivado/proyecto \
     petalinux:2021.1 \
     ps




Se necesita el comando shift para que se necesite el argumento con el nombre del directorio de trabajo
solo que este script no entró en el contenedor en sí.
Ahora puede ejecutar comandos desde el host directamente en el contenedor. Por ejemplo:

gcc-v

imprime la versión del compilador en el contenedor a la terminal host.

Sin embargo, debido al hecho de que petalinux requiere que se inicialicen las variables de entorno
simplemente llamar a los comandos de petalinux no funcionará. Para esto necesitas un poco
modificar comando. Por ejemplo, creemos un proyecto petalinux para zynqMP en
directorio de host ~/petalinux_prj:

./run-container.sh /home/user/petalinux_prj /bin/bash -c \
     'fuente /opt/Xilinx/petalinux/settings.sh; \
     petalinux-create -t ​​proyecto --template zynqMP --force -n test'