---
layout: page
nav: docs
title: Type Conversion
---

| VTK type | QuickVtk type |
|:--- |:--- |
| `bool` | `bool` |
| `int` | `int` |
| `float` | `qreal` |
| `double` | `qreal` |
| `const char*` | `QString` |
| `double [3]` (Color) | `QColor` |
| `double [3]` (Vector 3) | `Math::Vector3` |
| `double [2]` (Vector 2) | `Math::Vector2` |


## 1. Simple Types
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

> Color
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

## 2. Enums

## 3. Colors

## 4. Vectors
