# Kindle Engine Monitor

## **Note: this is not intended to be built and used on other systems**

## Prerequisites

* Windows
* Visual Studio
* mingw-w64
* CMake
* [X-Plane SDK](https://developer.x-plane.com/sdk/plugin-sdk-downloads/)

## Cloning
Make sure to add the ```--recurse-submodules``` flag
Example: ```git clone --recurse-submodules https://github.com/Bobbyt1500/kindle-edm.git```

## Building Plugin

1. Place the XPLM "SDK" folder in the "plugin" directory
2. Create build directory ```mkdir build;cd build```
3. Use CMake to generate Visual Studio files  ```cmake ../```
4. Open the "KindleEDM.vcxproj" and build using Visual Studio

## Building Application

1. Create build directory ```mkdir build;cd build```
2. Use CMake to generate makefiles ```cmake ../ -G "MinGW Makefiles```
3. Build with mingw-w64 ```ming32-make```
