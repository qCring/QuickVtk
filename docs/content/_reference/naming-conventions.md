---
layout: subpage
nav: reference
title: Naming Conventions
number: 1
---

## Namespaces

All classes in QuickVtk reside in the top-level `quick` namespace.

### Public API namespaces
- The `Vtk`namespace holds all [VTK](https://vtk.org/) wrapper classes
- The `Math` namespace holds [QML](https://doc.qt.io/qt-5/qtqml-index.html) types for math-related types
- The `SampleData` namespace holds [QML](https://doc.qt.io/qt-5/qtqml-index.html) types to access built-in resources like 2D/3D image data, models, etc.

### Private API namespaces
- The `App` namespace holds [QML](https://doc.qt.io/qt-5/qtqml-index.html) types to access application data
- The `TypeInfo` namespace holds [QML](https://doc.qt.io/qt-5/qtqml-index.html) types for the built-in type browser
- The `Editor` namespace holds [QML](https://doc.qt.io/qt-5/qtqml-index.html) types responsible for runtime [QML](https://doc.qt.io/qt-5/qtqml-index.html) compilation
- The `IO` namespace holds utility file I/O functionality
- The `Qml::Register` namespace handles static collection of type information to populate the type browser and register custom C++ types to [QML](https://doc.qt.io/qt-5/qtqml-index.html)

## Classes
- **PascalCase** (`MyClass`)
- Header (.hpp) and implementation (.cpp) files should always have the same name
- Full namespace should be used to provide a unique file identifier by convention:
  - `MyClass` located in the `quick::Vtk` namespace should be defined in `quickVtkMyClass.hpp` and implemented in `quickVtkMyClass.cpp`

## Enums
- **PascalCase** (`MyEnum`)
- Internal enum definitions should use scoped enums (`enum class`) to ensure strongly typed enums
- Enums in the context of wrapper classes should use regular enums (`enum`). Plain enums allow direct assignment to [VTK](https://vtk.org/) types without specific conversion.
- Enums should always be defined within a class without any suffix or prefix

## Properties
- **camelCase** (`myProperty`)
- Properties (`Q_PROPERTY`) that wrap [VTK](https://vtk.org/) members should use the same name consistently. Usually the attribute name from [VTK](https://vtk.org/) can be used (only in **camelCase**) for all property names

## Class Members
- **camelCase**  (`myMember`)
- `m_`-prefix for non-static class members (`m_myMember`)

## Methods
- **camelCase** if non-static (`myMethod`)
- **PascalCase** if static (`MyMethod`)
- Trailing return types (`auto MyClass::myMethod() -> int`) by default
- Only `signal` declarations use the classic return style notation
