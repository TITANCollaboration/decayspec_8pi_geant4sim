# decayspec_8pi_geant4sim
Geant4 sim for 8pi decay spec, code originally written by Alex Grossheim

##Evnrionment needed:

##OS

OS : Ubuntu 18+? (really any unix variant that you can compile GEANT & ROOT on)

###GEANT4

version : 10.05

CMAKE Agruments :

```
cmake -DCMAKE_INSTALL_PREFIX=/usr/local/geant4.10.05 -DGEANT4_USE_GDML=ON -DCMAKE_BUILD_TYPE=Debug -DGEANT4_INSTALL_DATA=ON -DGEANT4_USE_OPENGL_X11=ON -DGEANT4_USE_XM=ON -DGEANT4_USE_QT=ON -DGEANT4_BUILD_MULTITHREADED=ON
```
###ROOT

version : 6.14.06

CMAKE Agruments :

```cmake -DCMAKE_INSTALL_PREFIX=/usr/local/root/root-6.14.06 -Dminuit2=ON -Dxml=ON -Dmathmore=ON

###Vagrant VM

I'm also making available the [Vagrant](https://www.vagrantup.com/) VM built for VirtualBox and soon KVM that is used to run this with the above stuff included.  You can find the latest copy at : https://app.vagrantup.com/jonr667/boxes/geant4_ubuntu . It's reasonably easy to install and will save you an afternoon of compiling Geant4 and ROOT...

##How to Build
After you have the proper environment and you have run git clone just make a build directory and run cmake

```
git clone https://github.com/TITANCollaboration/decayspec_8pi_geant4sim.git
mkdir build
cd build
cmake ../decayspec_8pi_geant4sim
```