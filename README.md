# qt5-cmake-conan-example
qt5.12  with conan package in cmake project, you can play qt with c++ conan packages

## why we do it 

* we use qt5.12 just now, so we could not use conan package of qt6.
* we use cmake project ,not qtcreator ide.
* we want use other conan packages

## dependence
* conan,look office web
* taoquick examples
* cmake 3.21
* gcc 10.2
* qt5.12.12, offline installed.
## conan package
* spdlog
fast and powerful log for c++ and other langueages
* asio tcp client
* cocoyaxi tcp client , go like coroutine c++17 
## note
:warning:
if you want to add quickcontrol2 modules ,
you need add your qt path in cmakelists.txt file,look 
 <CMakeLists-add-quick-control.txt> file 

## tested  

tested OK on ubuntu 20.04

Please learn conan ,cmake ,qt ,before do it .
good luck.

## example function 
numcpp, xtensor,
tcpclient with asio lib,
tcp client with cocoyaxi.
qt3d,display .obj 
![](images/plane-obj.png)
## TODO

http plot
## end