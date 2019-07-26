QuickVtk
===
![Version](https://img.shields.io/badge/version-0.5.6-blue.svg)
![VTK](https://img.shields.io/badge/VTK-8.2.0-red.svg)
![Qt](https://img.shields.io/badge/Qt-5.13.0-green.svg)

A live [**QML**](http://doc.qt.io/qt-5/qtqml-index.html) interpreter with embedded [**VTK**](http://www.vtk.org) support

<center>
	<img src="doc/img/screenshot1.png" width="100%" />
</center>

## 1. Overview
QuickVtk is a live [**QML**](http://doc.qt.io/qt-5/qtqml-index.html) interpeter with built-in support for the [**VTK**](http://www.vtk.org)-Framework. You can simply learn or test [**QML**](http://doc.qt.io/qt-5/qtqml-index.html) code and develop prototypes in the domain of 2D/3D visualization by accessing [**VTK**](http://www.vtk.org) in a declarative way. To put it in one sentence: QuickVtk's main purpose is to enable reactive programming for [**VTK**](http://www.vtk.org) by utilizing the [**QML**](http://doc.qt.io/qt-5/qtqml-index.html) engine.

An embedded editor allows you to load, edit and compile [**QML**](http://doc.qt.io/qt-5/qtqml-index.html) code. Errors are shown directly in the UI and an embedded type browser gives a quick overview of all the different properties, methods and other information for a given type available in QuickVtk.

## 2. Screenshots
Different screenshots demonstrate some of QuickVtk's main features like 3D volume rendering, 2D image processing operations and mesh filters from [**VTK**](http://www.vtk.org)

<center>
	<img src="doc/img/screenshot2.png" width="100%" />
</center>

## 3. Build Instruction

The 'old' build instructions are [**available here**](./doc/build/old.md) but will be replaced in order to provide specific documentation for the different platforms:

- [**Windows**](./doc/build/windows.md)
- [**macOS**](./doc/build/macos.md)
- [**Linux**](./doc/build/linux.md)

## 4. Current Development
Check out the [**Issues section**](https://github.com/qCring/QuickVtk/issues) which basically serves the purpose of tracking the next steps along the development roadmap. 

The documentation needs better structuring and I'll spend some time to clean up and rearrange different contents. Stay tuned!

## 5. Contributing
Any contribution is helpful and welcome! There are different ways of how you can contribute to this project and get involved with development: 

- **Report an Issue** simply by [**opening an issue**](https://github.com/qCring/QuickVtk/issues/new) here on GitHub with a detailed description if possible
- **Request Features/Enhancements** also by opening an issue (tag it with an **enhancement** label) and provide a brief explanation of the requested feature
- **Open a Pull Request** with your changes. Just make sure to create a new branch and reference the related issue to keep things organized

There are no hard rules in terms of coding style and such. Just take a look at some lines of code and that should be enough to discover some recurring patterns which keep the code more or less consistent.

## 6. Contact
If you're interested in the project, want to give some feedback or simply get in touch feel free to write a <a href="mailto:qCring@gmail.com">**mail!**</a>

## 7. License
![License](https://img.shields.io/badge/license-BSD--3--Clause-blue.svg)

Copyright (c) 2016-2019, Alexander Eduard Szalo
All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.

3. Neither the name of the copyright holder nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.