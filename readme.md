QuickVtk
===
![Version](https://img.shields.io/badge/version-0.5.3-blue.svg)
![VTK](https://img.shields.io/badge/VTK--git-24289b3%20Jan%2012%202017-red.svg)

A live **[QML](http://doc.qt.io/qt-5/qtqml-index.html)** interpreter with embedded **[VTK](http://www.vtk.org)** support

<center>
	<img src="doc/img/screenshot1.png" width="100%" />
</center>

##1. Overview
QuickVtk is a live **[QML](http://doc.qt.io/qt-5/qtqml-index.html)** interpeter with built-in support for functionality provided by **[VTK](http://www.vtk.org)**. You can simply learn or test **[QML](http://doc.qt.io/qt-5/qtqml-index.html)** code and develop prototypes in the domain of 2D/3D visualization by accessing **[VTK](http://www.vtk.org)** in a declarative way. To put it in one sentence: QuickVtk's main purpose is to enable reactive programming for **[VTK](http://www.vtk.org)** by using mechanics of the **[QML](http://doc.qt.io/qt-5/qtqml-index.html)** engine.

An embedded editor on one side of the screen allows you to load, edit *(you're best off using an external text editor since code formatting is not supported yet)* and compile **[QML](http://doc.qt.io/qt-5/qtqml-index.html)** code which will be shown in a preview container. Compilation errors are forwarded to the UI, telling you where and why something went wrong. A type browser is also available to get a quick overview of all properties, methods and other useful meta information for a given type available in QuickVtk.

##2. Documentation
**Spoiler:** There's not much documentation going on right now, but still better than nothing :)

- **For Users**   
 	Check out the **[user section](doc/user/doc.md)** for some guides / notes / tutorials on how to use  QuickVtk

- **For Developers**    
 	If you're interested in under-the-hood stuff, check out the **[developer section](doc/dev/doc.md)** where some topics will be discussed from a more technical perspective

##3. Building QuickVtk
Binaries are not available yet *(this won't change anytime soon I guess)*. If you're interested in the project, go ahead and check out the **[build instructions](doc/build.md)** and take a look at how to compile QuickVtk from source!

##4. Screenshots

<center>
	<img src="doc/img/screenshot2.png" width="100%" />
</center>

##5. Sample Data Sources
In order to provide working code examples, I redistribute some sample data files. Here's a list of all files located at `res/examples/data/` together with their individual origins:

- **Suzanne**:   
   low-poly mesh *(exported to .obj and .stl)* from [Blender](https://www.blender.org)
   
- **Stanford Bunny**:   
   high-poly mesh from the [Stanford 3D Scanning Repository](http://graphics.stanford.edu/data/3Dscanrep/) *(.ply, .obj and .stl)*
- **Utah Teapot**:   
   low-poly mesh *(currently only .off to demonstrate [OFF format](http://segeval.cs.princeton.edu/public/off_format.html) support)*
- **Brain1** and **Brain2**:   
   DICOM data from [idoimaging.com](http://idoimaging.com) (special thanks to Andrew Crabb)
- **Lena**:   
   famous testing image *(exported to .png, .jpg and .tiff)* from [Wikipedia](https://en.wikipedia.org/wiki/File:Lenna.png)
- **ImageA** and **ImageB**:   
   self-made test images

##6. Development
QuickVtk is in an early stage of development. And so is the development roadmap (which is basically nonexistent and plain random to be honest). I'd like to focus on documentation next to make development more transparent. Work out a proper roadmap, write down some lessons learned maybe and communicate what's going on with this project.

**So here's the plan:** I'll set up a proper project website and try to figure out how this whole **[GitHub Pages](https://pages.github.com)** thing works... 

Stay tuned!

##7. Contributing
Any contribution is helpful and awesome! There are basically three forms of how you can contribute to this project and get involved with development: 

- **Report Bugs**   
Open an issue on GithHub, tag it with the **bug** label and provide a simple description and the steps to reproduce the problem if possible.

- **Request Features/Enhancements**   
Open an issue on GitHub, tag it with the **enhancement** label and provide a simple description of what and why should be done. My resources are limited but I'll try my best to make it work.

- **Contribute Code**    
If you want to patch a bug or add a feature yourself: awesome! Just clone QuickVtk, add your changes and provide a pull request. To keep things clean, create a new branch and prefix it with either **fix** or **feature** like this:    
	- **fix/**\<some_bug\>
	- **feature/**\<some_feature\>

	There are no real rules in terms of coding style and such. Taking a look at some lines of code from QuickVtk should be enough to discover some recurring patterns which keep the code (more or less) consistent.
	
##8. Contact
If you're interested in the project, want to give some feedback or just have some questions or suggestions

feel free to write a <a href="mailto:qCring@gmail.com">mail!</a>

##9. License
![License](https://img.shields.io/badge/license-BSD--3--Clause-blue.svg)

Copyright (c) 2016, Alexander Eduard Szalo
All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.

3. Neither the name of the copyright holder nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.