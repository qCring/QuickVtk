QuickVtk
===

A **[VTK](http://www.vtk.org)** prototyping application based on **[QtQuick](http://qt-project.org)**/**[QML](http://doc.qt.io/qt-5/qtqml-index.html)**


###...More to come... 
until then there's a screenshot of the work-in-progress application at least!

<center>
	<img src="doc/img/screenshot.png" width="100%" />
</center>

Interact with **[VTK](http://www.vtk.org)** from **[QML](http://doc.qt.io/qt-5/qtqml-index.html)**. The code behind the above example:

	import QtQuick 2.5
	import Vtk 1.0

	Item {
		anchors.fill: parent;
		
		Viewer { 
			anchors.fill: parent;
			mouseEnabled: true;
			
			Actor {
				PolyDataMapper {
					OBJReader {
						fileName: "coffee.obj"
					}
				}
			}
		}
	}

Contact Me
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