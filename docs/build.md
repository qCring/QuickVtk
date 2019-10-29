---
layout: page
nav: build
toplevel: true
---

# Build Instructions
QuickVtk can be built for Windows, macOS, and Linux via [CMake](https://cmake.org/)

## Prerequisites
- Download and install [CMake](https://cmake.org/)
- Download and install [Qt](https://www.qt.io/)

## Build VTK
- [VTK](https://vtk.org/) can be built from the `libs` folder
- Launch [CMake](https://cmake.org/) and set the paths to
  - src: `QuickVtk/libs/src`
  - bin: `QuickVtk/libs/bin`

- Press **Configure** and specify a project generator
- Use the **VTK_GIT_TAG** attribute to specify a commit hash which will be used to download and build a specific [VTK](https://vtk.org/) version from the remote repository
- Press **Configure** and then **Generate**
- Make sure you are connected to the internet before starting the build process since [VTK](https://vtk.org/) has to be cloned first

### on macOS and Linux via Make
- Open the terminal
- Navigate to `/libs/bin` from the project directory
- Run `make` (or `make -jN` where `N` = number of parallel threads for faster builds)

### on Windows via Visual Studio
- Navigate to `/libs/bin` from the project directory
- Open the generated solution in Visual Studio
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
  - `libs/bin/VTK/bin` if you are using the VTK build from the `libs` folder
  - alternatively you can use an existing, external build
- Press **Configure** and specify a project generator
- Press **Generate**

### on macOS via Xcode
- Navigate to the project's `/bin` directory
- Open the generated `.xcodeproj` file
- Change the target from **ALL_BUILD** to **QuickVtk**
- Hit <kbd>⌘</kbd> + <kbd>R</kbd> to build and run QuickVtk

### on Windows via Visual Studio
- Navigate to the project `/bin` directory
- Open the generated `.sln` file
- In the solution explorer, right click on **QuickVtk** and select **Set as StartUp project**
- Build and run the application
