# PictureToModel
From the 12th IPP projects of SJTU

## Install
* OS: Ubuntu14.04.4 LTS (or other linux core system)
* Hardware: Kinect 1/2
also, you should install some integrant lib such as `opencv`, `pcl` and `g2o`.   
`sudo apt-get install git cmake`
1. install `opencv` 2.4
then download source of [opencv](http://opencv.org/). It seems that opencv3.0 hasn't good compability so please download the 2.4 version.
`cd opencv2.4`   
`mkdir build`  
`cd build`  
`cmake ..`  
`make`  
`sudo make install`  
 now `opencv` has sucessfully install on your system
2. install `pcl`
please follow this guide to install [pcl](http://pointclouds.org/downloads/linux.html)
3. install `g2o`
[g2o](https://github.com/RainerKuemmerle/g2o) is a useful tool to optimize graph. You can go to it's github to download it.  
before install it, you should install QT. I strongly recommend you to install complete [QT](http://www.qt.io/download/) but use `apt-get install libqt4-dev`.  
`g2o` installation is similar to `opencv`.
