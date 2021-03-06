---
layout: page
nav: build
toplevel: true
---

# Build Instructions
QuickVtk can be built for Windows, macOS, and Linux via [CMake](https://cmake.org/)

## Prerequisites
- [CMake](https://cmake.org/)
- [Qt](https://www.qt.io/)
- C++14 compiler
- git
- The cloned repository from `https://github.com/qCring/QuickVtk.git`

## Build VTK
- [VTK](https://vtk.org/) can be built from the `dependencies` folder
- Launch [CMake](https://cmake.org/) and set the paths to
  - src: `QuickVtk/dependencies/src`
  - bin: `QuickVtk/dependencies/bin`

- Press **Configure** and specify a project generator
- Use the **VTK_GIT_TAG** attribute to specify a commit hash which will be used to download and build a specific [VTK](https://vtk.org/) version from the remote repository
- Press **Configure** and then **Generate**
- Make sure you are connected to the internet before starting the build process since [VTK](https://vtk.org/) has to be cloned first

### on macOS and Linux via Make
- Open the terminal
- Navigate to `/dependencies/bin` from the project directory
- Run `make` (or `make -jN` where `N` = number of parallel threads for faster builds)

### on Windows via Visual Studio
- Navigate to `/dependencies/bin` from the project directory
- Open the `QuickVtkDependencies` solution file in Visual Studio
- Start the build process from the IDE

## Build QuickVtk
- Launch [CMake](https://cmake.org/) and set the paths accordingly
  - src: `QuickVtk`
  - bin: `QuickVtk/bin`
- Press **Configure** and specify a project generator
- Set the path to `Qt5Config.cmake`
  - Depends on your [Qt](https://www.qt.io/) installation but should look something like this
  - on macOS: `/Qt/5.13.0/clang_64/lib/cmake/Qt5/`
  - on Windows: `/Qt/5.13/msvc2017/lib/cmake/Qt5/`
- Press **Configure** to apply changes
- Set the path to [VTK](https://vtk.org/)
  - `dependencies/bin/VTK/bin` if you are using the VTK build from the `dependencies` folder
  - alternatively you can use an existing external build
- Press **Configure** and specify a project generator
- Press **Generate**

### on macOS via Xcode
- Navigate to the project's `/bin` directory
- Open the generated `.xcodeproj` file
- Change the target from **ALL_BUILD** to **QuickVtk**
- Hit <kbd>⌘</kbd> + <kbd>R</kbd> to build and run QuickVtk

### on Windows via Visual Studio
- Navigate to the project's `/bin` directory
- Open the generated `QuickVtk.sln` file
- In the solution explorer, right click on **QuickVtk** and select **Set as StartUp project**
- Open the project properties from the menu via **Project** / **Properties** or <kbd>Alt</kbd> + <kbd>F7</kbd>
  - Select **Debugging** from the **Configuration Properties**
  - Edit the value for **Environment**
  - Add the paths to `Qt\bin` and `Vtk\bin` which should look something like   
    `PATH=C:\Qt\5.13.0\msvc2017\bin;E:\GitHub\QuickVtk\dependencies\bin\VTK\bin\bin\Debug;%PATH%;`   
    depending on your [Qt](https://www.qt.io/) installation and the location of your [VTK](https://vtk.org/) binaries
- Build and run the application
