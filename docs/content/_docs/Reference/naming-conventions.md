---
layout: page
nav: docs
title: Naming Conventions
category: Reference
---

## Namespaces

All classes in QuickVtk reside in the top-level `quick` namespace.

### Public API namespaces
- The `Vtk`namespace holds all [VTK](https://vtk.org/) wrapper classes
- The `Math` namespace holds [QML](https://doc.qt.io/qt-5/qtqml-index.html) types for math-related types
- The `SampleData` namespace holds [QML](https://doc.qt.io/qt-5/qtqml-index.html) types to access built-in ressources like 2D/3D image data, models, etc.

### Private API namespace
- The `App` namespace holds [QML](https://doc.qt.io/qt-5/qtqml-index.html) types to access application data
- The `TypeInfo` namespace holds [QML](https://doc.qt.io/qt-5/qtqml-index.html) types for the built-in type browser
- The `Editor` namespace holds [QML](https://doc.qt.io/qt-5/qtqml-index.html) types responsible for runtime [QML](https://doc.qt.io/qt-5/qtqml-index.html) compilation
- The `IO` namespace holds utility file I/O functionality
- The `Qml::Register` namespace handles static collection of type information to populate the type browser

## Classes
Header (.hpp) and implementation (.cpp) pairs for an individual class should always have the same name. Also, the full namespace should be used to build a unique identifier by convention. For example, the class `MyClass` located in the `quick::Vtk` namespace should be defined in `quickVtkMyClass.hpp` and implemented in `quickVtkMyClass.cpp` while the classname should be `MyClass`.

While this is the convention for now, this might [change in the future]({{ site.baseurl }}/research/open/include-headers).

## Enums

## Properties

## Methods
