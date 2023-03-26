# Smartnav-platform

This is the platform of the smartnav project.

# Architecture 

<img src="./doc/arch_full.png"  width="800" height="400">

# HDF 

Hardware description software

<img src="./smartscout-vivado/smartnav-vivado/design_1.png"  width="800" height="400">
<img src="./smartscout-vivado/smartnav-vivado/design_2.png"  width="800" height="400">

# Pictures

<p float="left">
    <img src="./doc/state0.jpeg" width="225" />
    <img src="./doc/state1.jpeg" width="150" />
    <img src="./doc/state2.jpeg" width="266" />
    <img src="./doc/state3.jpeg" width="150" /> 
    <img src="./doc/state4.jpeg" width="150" />
    <img src="./doc/state5.jpeg" width="150" />
    <img src="./doc/state6.jpeg" width="266" />
    <img src="./doc/state7.jpeg" width="227" />
    <img src="./doc/state8.jpeg" width="150" />
    <img src="./doc/state9.jpeg" width="190" />
</p>

# Docker: 

From the root of this repository:

+ Running Vivado: 
  ```
  sh run_vivado.sh
  ```
+ Basic build process (check Petalinux Documentation): 
  ```
  sh run_build.sh
  ```
+ Fully build process: 
  ```
  sh run_build_from_scratch.sh
  ```
+ Any command: 
  ```
  ./etc/petalin.sh "cd ./smartscout/smartscout-platform && petalinux-create -t apps --template install -n smartnav-app-init --enable"
  ```

# Acknowledgment

The base docker image was taken from this site: https://github.com/carlesfernandez/docker-petalinux (MIT LICENSE). I am fully grateful.