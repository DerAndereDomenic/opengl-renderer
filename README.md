OpenGL Renderer
===============
A basic Renderer wrapping OpenGL functions. Comes with different demos using the framework

Building:
============
The framework is build using CMake.

**Windows:** <br>
The library comes with all needed dependencies compiled for MSVC 2019.

**Linux/Ubuntu** <br>
The following libraries and its dependencies have to be installed
* GLFW
* GLEW
* ASSIMP
* FREETYPE

After cloning/installing the necessary libraries run the script <br>
```sh build.sh```
to build the project. When executing the script for the first time the setup routine is called, creating the <samp>build</samp> and <samp>bin</samp> folder containing build files and the executables. The project uses [DLogger](https://gitlab.com/DerAndereDomenic/dlogger) for logging. The repository is cloned and configured when running the script for the first time.
Calling
```sh build.sh --setup```
will call the setup routine again.
