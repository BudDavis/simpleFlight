# simpleFlight
 
 Simple flight simulator using jsbsim, websocketpp and cesium js.
 
 A browswer window running Cesium JS for the out the window.
 
 a linux program running jsbsim and additional models.

 ```pre
                               |------------------|
                               |   jsbsim         |
aircraft config files  -----> |   + websockets   |
                               |   = simpleFLight |
                               |------------------|
                                     |     / \
                       AC position   |      |   Height of Terrain                       
                                     |      |   Joystick events
                                     |      |    (port 4000)
                                    \ /     |
                               |---------------------|
                               |  Browser            |
     joystick ---------------> |   running cesium js |
                               |   + joystick        |
                               |---------------------|
                                      / \
                                       |
                                       |
                                       |
                                       |
                                      \ /
                                Cesium Terrain service
 ```
 
 
 
 
 
 
 
 
 =======================================================
 
https://github.com/JSBSim-Team/jsbsim/releases/download/v1.1.13/JSBSim-devel_1.1.13-986.focal.amd64.deb
wget https://github.com/JSBSim-Team/jsbsim/releases/download/v1.1.13/JSBSim_1.1.13-986.focal.amd64.deb

 
sudo apt install ./JSBSim-devel_1.1.13-986.focal.amd64.deb 

git clone https://git.code.sf.net/p/flightgear/simgear flightgear-simgear


sudo apt install ./JSBSim_1.1.13-986.focal.amd64.deb


sudo apt-get install libboost-all-dev
sudo apt-get install libgl1-mesa-dev
sudo apt-get install libopenal-dev

git clone http://github.com/zaphoyd/websocketpp.git


https://github.com/ExperimentalAvionics/GlassPanel/tree/master/js

https://github.com/draw2soon/Flight-Instruments

https://github.com/pmatigakis/avionics.js/blob/master/demo/js/demo_app.js





git clone https://github.com/JSBSim-Team/jsbsim.git
