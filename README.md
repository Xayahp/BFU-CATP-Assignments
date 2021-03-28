# BFU-CATP Assignments Framework

[![MIT License](https://img.shields.io/badge/licence-MIT-brightgreen)]()[![Latest Release](https://img.shields.io/badge/Latest_Release-0.7.1-blue)]()

## Introduction

This is a dead simple rendering and physics framework for physically based modeling and animation.

This framework is designed as the course assignments of Computer Animation, Theory and Practice.

## Features

### Rendering Module

- support 2D and 3D rendering interface
- support programmable shader
- decoupled with physics module

### Physics Module

- physical bodies and shapes decoupled
- support particle system (2D/3D)
- support extendable solver
- support AABB rendering
- decoupled with rendering module

### Utilities

- support 2D/3D/user defined model parsing
- support shader loading
- support camera

### Dependency

- **UI:** [glfw](https://www.glfw.org), [imgui](https://github.com/ocornut/imgui)
- **OpenGL Loading:** [glad](https://glad.dav1d.de)(built in)
- **Math: **[Eigen](https://eigen.tuxfamily.org/index.php?title=Main_Page)(built in), [glm](https://github.com/g-truc/glm)(built in)
- **Texture Loading:** [stb](https://github.com/nothings/stb)(built in)
- **Model Loading: **[assimp](http://assimp.org)

## Build

First download [glfw](https://www.glfw.org), [imgui](https://github.com/ocornut/imgui) and [assimp](http://assimp.org) libraries, then unzip and put them under the **vendor** directory.

### Build on Linux

```
$ mkdir build && cd build
$ cmake ..
$ make -j5
$ ./AssignmentSample
```

### Build on MacOS Xcode

```
$ mkdir build && cd build
$ cmake .. -G "Xcode"
$ open ./AssignmentSample
// then build target AssignmentSample
```

### Build on Windows Visual Studio

```
$ md build && cd build
$ cmake .. -G "Visual Studio"
$ open ./AssignmentSample.sln
// then build target AssignmentSample
```

It's alternative to build by minGW/cygwin on windows yourself.

## Samples



## Reference

> [1]. Foundations of  Physcally Based Modeling and Animation, Donald H. House, John C. Keyser.

