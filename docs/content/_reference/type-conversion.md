---
layout: subpage
nav: reference
title: Type Conversion
number: 2
---

## Overview

| native VTK type | QuickVtk type |
|:--- |:--- |
| `bool` | `bool` |
| `int` | `int` |
| `float` | `qreal` |
| `double` | `qreal` |
| `const char*` | `QString` |
| Color (`double [3]`) | `QColor` |
| Vector2 (`double [2]`) | `Math::Vector2` |
| Vector3 (`double [3]`) | `Math::Vector3` |

## Simple Types
Most of the basic types can be used in QML and C++ without specific type conversion

> Bool
{:.hl-caption}

{%- highlight cpp -%}

auto VtkWrapper::setBool (bool value) -> void {
  this->m_vtkObject->SetBool (value);
}

auto VtkWrapper::getBool () -> bool {
  return this->m_vtkObject->GetBool ();
}
{%- endhighlight -%}

> Int
{:.hl-caption}

{%- highlight cpp -%}
auto VtkWrapper::setInt (int value) -> void {
  this->m_vtkObject->SetInt (value);
}

auto VtkWrapper::getInt () -> int {
  return this->m_vtkObject->GetInt ();
}
{%- endhighlight -%}

## Floating-Point Numbers
While VTK uses `float` and `double` types explicitly, wrappers can rely on the [qreal type](https://doc.qt.io/qt-5/qml-real.html) which stores floating-point numbers in double precision by default.

> Float
{:.hl-caption}

{%- highlight cpp -%}
auto VtkWrapper::setFloat (qreal value) -> void {
  this->m_vtkObject->SetFloat (value);
}

auto VtkWrapper::getFloat () -> qreal {
  return this->m_vtkObject->GetFloat ();
}
{%- endhighlight -%}

> Double
{:.hl-caption}

{%- highlight cpp -%}
auto VtkWrapper::setDouble (qreal value) -> void {
  this->m_vtkObject->SetDouble (value);
}

auto VtkWrapper::getDouble () -> qreal {
  return this->m_vtkObject->GetDouble ();
}
{%- endhighlight -%}

## Strings
Strings have to be converted from `const char*` (VTK) to `QString` (QML) and vice versa. As shown below, only the conversion from `QString` to `const char*` is explicit (`toStdString().c_str()`). `QStrings` can implicitly be constructed from `const char*`.

Wrappers should always use a `const` reference type for `Set`-method arguments. This indicates the immutability of passed `QString` arguments and also uses the memory address of an already existing `QString` instance instead of invoking the copy-constructor.

> String
{:.hl-caption}

{%- highlight cpp -%}
auto VtkWrapper::setString (const QString& value) -> void {
    this->m_vtkObject->SetString (value.toStdString().c_str());
}

auto VtkWrapper::getString () -> QString {
    return this->m_vtkObject->GetString ();
}
{%- endhighlight -%}

## Colors
VTK stores color data as `double [3]` for the individual RGB values. QML uses [QColor](https://doc.qt.io/qt-5/qcolor.html) and provides many different ways to specify color values including HEX, RGB, HSV, and CMYK.

> Color (1)
{:.hl-caption}

{%- highlight cpp -%}
auto VtkWrapper::setColor (const QColor& value) -> void {
  this->m_vtkObject->SetColor (color.redF(), color.greenF(), color.blueF());
}

auto VtkWrapper::getColor () -> QColor {
  auto red = 0.0;
  auto green = 0.0;
  auto blue = 0.0;

  this->m_vtkObject->GetColor(red, green, blue);
  return QColor(red, green, blue);
}
{%- endhighlight -%}

Since constructing `QColor` from `double [3]` can be a bit awkward, most wrappers store color data in a private member as shown in the following sample.

> Color (2)
{:.hl-caption}

{%- highlight cpp -%}
auto VtkWrapper::setColor (const QColor& value) -> void {
  this->m_color = value; // store value
  this->m_vtkObject->SetColor (color.redF(), color.greenF(), color.blueF());
}

auto VtkWrapper::getColor () -> QColor {
  return this->m_color; // bypass m_vtkObject and use stored QColor instead
}
{%- endhighlight -%}

Wrappers should always use a `const` reference type for `Set`-method arguments (as mentioned for `QStrings`).

## Vectors
Vector data is stored component-wise in arrays (`double [2]` and `double [3]` respectively). QuickVtk provides the classes [Math::Vector2]({{site.baseurl}}/api/Math/Vector2) and [Math::Vector3]({{site.baseurl}}/api/Math/Vector3) in order to access vectors from QML.

> Vector2
{:.hl-caption}

{%- highlight cpp -%}
auto VtkWrapper::setVector2 (Math::Vector2* vector) -> void {
  this->m_vector = vector;
  this->m_vtkObject->SetVector2 (vector->getValues()->data());
}

auto VtkWrapper::getVector2 () -> Math::Vector2* {
  return this->m_vector; // bypass m_vtkObject and use Vector2 member instead
}
{%- endhighlight -%}


> Vector3
{:.hl-caption}

{%- highlight cpp -%}
auto VtkWrapper::setVector3 (Math::Vector3* vector) -> void {
  this->m_vector = vector;
  this->m_vtkObject->SetVector3 (vector->getValues()->data());
}

auto VtkWrapper::getVector3 () -> Math::Vector3* {
  return this->m_vector; // bypass m_vtkObject and use Vector3 member instead
}
{%- endhighlight -%}

Both vector implementations are based on the generic `std::array` container type and provide access to underlying data via `getValues().data()`. This makes it possible to assign all components in one single call.


## Enums
