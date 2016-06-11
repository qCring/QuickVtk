QuickVtk
===
A live **[QML](http://doc.qt.io/qt-5/qtqml-index.html)** interpreter with embedded **[VTK](http://www.vtk.org)** support

<center>
	<img src="doc/img/screenshot1.png" width="100%" />
</center>

##Overview
###QML Prototyping
Use QuickVtk to quickly prototype **[QML](http://doc.qt.io/qt-5/qtqml-index.html)** code. Load a *.qml* file, edit the code in an external editor and save the file (an embedded editor will also be available, but until now that's just another item on the to-do list). QuickVtk then automatically reloads and compiles the modified file, informs you about eventual errors during compilation and finally shows the result in an embedded content view.

###Declarative VTK
You can simply declare **[VTK](http://www.vtk.org)** objects and their attributes just like it's done with built-in **[QML](http://doc.qt.io/qt-5/qtqml-index.html)** types. Internally, the underlying **[VTK](http://www.vtk.org)** pipeline handles data propagation or updating the renderer. Also, the source code is pretty much straightforward:
 
	import QtQuick 2.5
	import QtQuick.Controls 1.4
	import Vtk 1.0 as Vtk

	Item {
		anchors.fill: parent;
		
		Vtk.Viewer { 
			anchors.fill: parent;
			mouseEnabled: true;
			
			Vtk.Actor {
				Vtk.PolyDataMapper {
					Vtk.ShrinkPolyData {
						shrinkFactor: slider.value;
						
						Vtk.OBJReader {
							fileName: "car.obj"
						}
					}
				}
			}
		}
		
		Slider {
			id: slider;
			
			anchors.left: parent.left;
			anchors.right: parent.right;
			anchors.bottom: parent.bottom;
			
			miminumValue: 0.01;
			maximumValue: 1;
			value: 0.5;
		}
	}

###Reactive Programming For VTK
Probably the coolest thing about bringing **[VTK](http://www.vtk.org)** to **[QML](http://doc.qt.io/qt-5/qtqml-index.html)**. You can bind **[VTK](http://www.vtk.org)** class attributes to pretty much anything using **[Property Bindings](http://doc.qt.io/qt-5/qtqml-syntax-propertybinding.html)** which allow you to control variables directly or indirectly by:

- other properties
- user interaction with UI elements
- inline or included **[JavaScript](http://doc.qt.io/qt-5/qtqml-javascript-expressions.html)** code
- **[QML Animations](http://doc.qt.io/qt-5/qml-qtquick-animation.html)**
- **[QML Behaviors](http://doc.qt.io/qt-5/qml-qtquick-behavior.html)**

<center>
	<img src="doc/img/screenshot3.png" width="100%" />
</center>
*A slider's value is updated by user interaction and controls the 'lineThickness' property of an underlying vtkProperty object. All changes are applied and rendered immediately.*

###Type Information
In order to become available in QuickVtk, types from **[VTK](http://www.vtk.org)** have to be wrapped manually in **[QObject](http://doc.qt.io/qt-5/qobject.html)** derived classes. All the type information is stored in an associated static **[QMetaObject](http://doc.qt.io/qt-5/qmetaobject.html)** instance and used to create an entry in QuickVtk's embedded type browser. Information of wrapper classes is generated automatically, reflecting the API as is.

###Performance
QuickVtk is written in C++. Rendering of **[VTK](http://www.vtk.org)** in **[QML](http://doc.qt.io/qt-5/qtqml-index.html)** is not perfect (also not well documented) but does okay performance-wise. It's possible to have multiple Viewer items, each with an own interactor and an own set of scene actors. Eventually, I'll make some sort of benchmark or even compare the rendering performance to **[VTK](http://www.vtk.org)** in a **[QtGUI](http://doc.qt.io/qt-5/qtgui-module.html)** application, but that's another to-do thing for later...

<center>
	<img src="doc/img/screenshot2.png" width="100%" />
</center>

Building QuickVtk
----
QuickVtk can be built for Mac OS X and Windows via **[CMake](https://cmake.org)**

1. Download and install **[CMake](https://cmake.org)**
2. Download and install **[Qt](https://www.qt.io/download/)**
3. Get the **[VTK sources](https://github.com/Kitware/VTK)**
4. Build VTK via CMake
5. Build QuickVtk via CMake

**Important Notes:**

- When building VTK, make sure to use  **OpenGL** as **VTK\_RENDERING\_BACKEND** since things seem to have changed with **OpenGL2**
- **On Windows**, the renderWindowInteractor has an issue with the offscreen rendering setup and therefore is currently disabled. Which is sad but at least prevents the app from crashing.
- When building for **Windows** use **[Qt 5.6.1](https://www.qt.io/)** which is now capable of scaling the UI properly on high resolution displays.

Contact
----

Write me an <a href="mailto:a.e.szalo@gmail.com">e-mail</a>!

License
----
[![License](https://img.shields.io/badge/license-BSD--3--Clause-blue.svg)](https://opensource.org/licenses/BSD-3-Clause)

Copyright (c) 2016, Alexander Eduard Szalo
All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.

3. Neither the name of the copyright holder nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.