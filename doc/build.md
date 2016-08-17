QuickVtk
===
Build Instructions
----

QuickVtk can be built for Mac OS X and Windows via **[CMake](https://cmake.org)**. Building the project takes three steps:

### Step 1 - Install the Qt binaries

Download and launch the installer from the **[Qt download section](https://www.qt.io/download/)**.

### Step 2 - Build VTK

**[VTK](http://www.vtk.org)** can be built as a separate project from the **libs** folder located in the project directory. Launch **[CMake](https://cmake.org)** and set the paths to src and bin:

- **src**: QuickVtk/libs/src
- **bin**: QuickVtk/libs/bin

<center>
	<img src="img/cmake2.png"/>
</center>
You can specify a git tag to build a certain version of **[VTK](http://www.vtk.org)**. Configure, generate and build the project.

Alternatively, you can build **[VTK](http://www.vtk.org)** manually or use already built binaries from your system if available. Just make sure to use  **OpenGL** for the **VTK\_RENDERING\_BACKEND** option since QuickVtk's offscreen rendering setup does not yet support OpenGL2 which is the default rendering backend for **[VTK](http://www.vtk.org)** since version 7.

###Step 3 - Build QuickVtk
After successfully installing **[Qt](http://www.qt.io)** and building **[VTK](http://www.vtk.org)**, launch **[CMake](https://cmake.org)** and set the paths to src and bin:

- **src**: QuickVtk
- **bin**: QuickVtk/bin

<center>
	<img src="img/cmake1.png"/>
</center>

Specify the version and path attributes for **[Qt](http://www.qt.io)** and **[VTK](http://www.vtk.org)** and finally configure, generate and build the project. Tested project generators are:

- Unix Makefile (recommended for building VTK on Mac OS X)
- XCode (recommended for building QuickVtk on Mac OS X)
- Microsoft Visual Studio 2015 (for Windows)

**Note when building with Visual Studio:**
Make sure to set the environment in the IDE. Add the paths for **[Qt](http://www.qt.io)** and **[VTK](http://www.vtk.org)** to the *Environment* field found in the project properties view under *Debugging*:

<center>
	<img src="img/vs1.png"/>
</center>
