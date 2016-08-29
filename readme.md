QuickVtk
===
![Version](https://img.shields.io/badge/version-0.5.0-blue.svg)
![VTK](https://img.shields.io/badge/VTK-tag 8e6245e-red.svg)

A live **[QML](http://doc.qt.io/qt-5/qtqml-index.html)** interpreter with embedded **[VTK](http://www.vtk.org)** support

<center>
	<img src="doc/img/screenshot1.png" width="100%" />
</center>

##1. Overview
QuickVtk is a live **[QML](http://doc.qt.io/qt-5/qtqml-index.html)** interpeter with built-in support for functionality provided by **[VTK](http://www.vtk.org)**. You can simply learn or test *qml* code and develop prototypes in the domain of 2D/3D visualization by accessing **[VTK](http://www.vtk.org)** in a declarative way. In one sentence: QuickVtk enables reactive programming for **[VTK](http://www.vtk.org)** by using mechanics of the **[QML](http://doc.qt.io/qt-5/qtqml-index.html)** engine.

The workflow is simple. An embedded editor on the left allows you to load, edit and compile **[QML](http://doc.qt.io/qt-5/qtqml-index.html)** code which will be shown in the content view on the right. Eventual compilation errors are forwarded to the UI, telling you where and why something went wrong. And there's also a type browser available to quickly get an overview of all properties, methods and other useful meta information for a given type available in QuickVtk.

##2. Documentation
- check out the **[user docs](doc/userdoc.md)** for some guides / notes / tutorials on how to use  QuickVtk
- or if you're interested in under-the-hood stuff, check out the **[nerd section](doc/devdoc.md)** where some topics will be discussed from a more technical perspective

##3. Random Screenshots
I'm lazy and use screenshots to show some of QuickVtk's visualization features. They showcase volume rendering and some basic mesh and image operations. 

<center>
	<img src="doc/img/screenshot2.png" width="100%" />
</center>

##4. Building
Since the project is in an early stage of development, there are no binaries provided. If you're interested in the application, go ahead and check out the **[build instructions](doc/build.md)** to compile QuickVtk from source!

##5. Sample Data Sources
In order to provide working code examples, I redistribute some sample data files. Here's a list of all files located at **res/examples/data/** together with their individual origins:

- `suzanne`: low-poly mesh *(exported to .obj and .stl)* from [Blender](https://www.blender.org)
- `lena`: testing image *(exported to .png, .jpg and .tiff)* from [Wikipedia](https://en.wikipedia.org/wiki/File:Lenna.png)
- `imageA` and `imageB`: self-made test images
- `brain1` and `brain2`: DICOM data from [idoimaging.com](http://idoimaging.com) (special thanks to Andrew Crabb)

##6. Contact
If you're interested in the project, want to give some feedback or just have some questions or suggestions

feel free to write a <a href="mailto:qCring@gmail.com">mail</a> :)

##7. License
[![License](https://img.shields.io/badge/license-BSD--3--Clause-blue.svg)](https://opensource.org/licenses/BSD-3-Clause)

Copyright (c) 2016, Alexander Eduard Szalo
All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.

3. Neither the name of the copyright holder nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.