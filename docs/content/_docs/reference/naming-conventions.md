---
layout: page
nav: docs
title: Naming Conventions
category: Reference
number: 1
---

## Namespaces

All classes in QuickVtk reside in the top-level `quick` namespace.

### Public API namespaces
- The `Vtk`namespace holds all [VTK](https://vtk.org/) wrapper classes
- The `Math` namespace holds [QML](https://doc.qt.io/qt-5/qtqml-index.html) types for math-related types
- The `SampleData` namespace holds [QML](https://doc.qt.io/qt-5/qtqml-index.html) types to access built-in resources like 2D/3D image data, models, etc.

### Private API namespace
- The `App` namespace holds [QML](https://doc.qt.io/qt-5/qtqml-index.html) types to access application data
- The `TypeInfo` namespace holds [QML](https://doc.qt.io/qt-5/qtqml-index.html) types for the built-in type browser
- The `Editor` namespace holds [QML](https://doc.qt.io/qt-5/qtqml-index.html) types responsible for runtime [QML](https://doc.qt.io/qt-5/qtqml-index.html) compilation
- The `IO` namespace holds utility file I/O functionality
- The `Qml::Register` namespace handles static collection of type information to populate the type browser

## Classes
- **PascalCase** (`MyClass`)
- Header (.hpp) and implementation (.cpp) files should always have the same name
- Full namespace should be used to build a unique identifier by convention:
  - `MyClass` located in the `quick::Vtk` namespace should be defined in `quickVtkMyClass.hpp` and implemented in `quickVtkMyClass.cpp`

While this is the convention for now, this might [change in the future]({{ site.baseurl }}/research/open/include-headers).

## Enums
- **PascalCase** (`MyEnum`)
- Internal enum definitions should use scoped enums (`enum class`) to ensure strongly typed enums
- Enums in the context of wrapper classes should use regular enums (`enum`). Plain enums allow direct assignment to and from enums used in [VTK](https://vtk.org/) without specific conversion.
- Enums should always be defined within a class without any suffix or prefix to indicate the enumeration type (like `EMyType` or `MyTypeEnum`)

## Properties
- **camelCase** (`myProperty`)
- Properties (`Q_PROPERTY`) that wrap [VTK](https://vtk.org/) members should use the same name consistently:

## Class Members
- **camelCase**  (`myMember`)
- `m_`-prefix for non-static class members (`m_myMember`)

## Methods
- **camelCase** if non-static (`myMethod`)
- **PascalCase** if static (`MyMethod`)
- Use trailing return types (`auto MyClass::myMethod() -> int`)
