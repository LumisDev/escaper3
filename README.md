# ESCAPER 3

Is a little game made with CMake, C++, SFML and Box2D.

## How to build from source

First you need to have:
 1. CMake (>= 3.16)
 1. And a C++ build system (*i. e.* Ninja, Make) or Visual Studio
 > *****NOTE*****: For IDEs, CMake generates a project file.

To build, download the source code (through the zip file or with ```git clone```) and run:
 
```bash
    mkdir -p build && cd build
    cmake ..
    # Run your prefered build method
    # NOTE: "-p"(in mkdir) is not on Windows, for powershell, use a semicolon instead of &&
```
