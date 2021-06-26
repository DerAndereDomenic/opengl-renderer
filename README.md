OpenGL Renderer
===============
This is a hobby project, testing different real time rendering algorithms. I mostly followed the Tutorial of https://learnopengl.com and implemented the different algorithms into a framework. It is not meant to build actual 3D graphics applications with it.

Building
============
If you are still interested in building the project, all necessary libraries are included as git submodules. Running the build script should do the job. While, in principle, this should also work for Linux systems, I only tested it on Windows.

TODO
============
Here, I list some things I'd like to implement in the future.
* [ ] - A forward renderer class that handles all steps to create forward renderings. For this an update of the Material system is probably useful:
    * [ ] - Update Materials system
* [ ] - A deferred renderer class, similar to the forward renderer
* [ ] - Bloom Pipeline
* [ ] - SSAO
* [ ] - Scene Loading, until now only models can be loaded but no materials
