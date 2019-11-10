---
layout: subpage
nav: docs
title: Part 3 - Constructor
category: Implementing a VTK wrapper in QuickVtk
---

## Adding the Q_OBJECT macro
Custom [QML](https://doc.qt.io/qt-5/qtqml-index.html) types must be derived from [QObject](https://doc.qt.io/qt-5/qobject.html) and contain the `Q_OBJECT` macro inside the class declaration. The [API Reference]({{ site.baseurl }}/api) reveals the class hierarchy for our direct base class [Vtk::PolyDataAlgorithm]({{ site.baseurl }}/api/Vtk/PolyDataAlgorithm):
- [Vtk::Algorithm]({{ site.baseurl }}/api/Vtk/Algorithm)
- [Vtk::Object]({{ site.baseurl }}/api/Vtk/Object)
- and finally [QObject](https://doc.qt.io/qt-5/qobject.html)

This means that any wrapper that subclasses [Vtk::Object]({{ site.baseurl }}/api/Vtk/Object) is also a [QObject](https://doc.qt.io/qt-5/qobject.html) and can be exposed to [QML](https://doc.qt.io/qt-5/qtqml-index.html). The only thing we have to do for all types individually is to add the `Q_OBJECT` macro

>quickVtkPointSource.hpp
{: .hl-caption}

{% highlight cpp %}
#pragma once

namespace quick {
  namespace Vtk {

    class PointSource : public PolyDataAlgorithm {
      Q_OBJECT
    private:
      static Qml::Register::Symbol::Class<PointSource> Register;
    };
  }
}
{% endhighlight %}

The `Q_OBJECT` macro is used by the [Meta-Object Compiler (moc)](https://doc.qt.io/qt-5/moc.html) and is required for the signals and slot mechanism, the run-time type information, and the dynamic property system in [Qt](https://www.qt.io/).

## Implementing the default Constructor
Let's declare the default constructor in our `PointSource` header which will be called every time a `PointSource` is created in [QML](https://doc.qt.io/qt-5/qtqml-index.html)

>quickVtkPointSource.hpp
{: .hl-caption}

{% highlight cpp %}
#pragma once

namespace quick {
  namespace Vtk {

    class PointSource : public PolyDataAlgorithm {
      Q_OBJECT
    private:
      static Qml::Register::Symbol::Class<PointSource> Register;
    public:
      PointSource();
    };
  }
}
{% endhighlight %}

Now we can add the implementation in the **.cpp** file

>quickVtkPointSource.cpp
{: .hl-caption}

{% highlight cpp %}
#include "quickVtkPointSource.hpp"
#include <vtkPointSource.h>

namespace quick {
  namespace Vtk {

    Qml::Register::Symbol::Class<PointSource> PointSource::Register(true);

    PointSource::PointSource() : PolyDataAlgorithm(vtkSmartPointer<vtkPointSource>::New()) {
      qDebug() << "a new instance of PointSource was created!";
    }
  }
}

{% endhighlight %}

Since the constructor of the [Vtk::PolyDataAlgorithm]({{ site.baseurl }}/api/Vtk/PolyDataAlgorithm) base expects a `vtkSmartPointer<vtkPolyDataAlgorithm>` argument, we have to provide an existing `vtkPolyDataAlgorithm` by calling `vtkSmartPointer<vtkPointSource>::New()`.

We want to pass the newly created [vtkPointSource](https://vtk.org/doc/nightly/html/classvtkPointSource.html) immediately to our base class and avoid `nullptr` references. This can be done by using the `delegating constructor` in the [member initializer list](https://en.cppreference.com/w/cpp/language/initializer_list). We will come back to this in a bit.

The `qDebug()` macro gives us some proof that an object of this type was actually constructed. Our implementation can now be compiled and the `PointSource` class can be accessed from [QML](https://doc.qt.io/qt-5/qtqml-index.html).

## Creating a PointSource in QML
If you encounter linker errors, try to rebuild the project in [CMake](https://cmake.org/). Some IDEs don't properly invoke the [Meta-Object Compiler](https://doc.qt.io/qt-5/moc.html) after adding new classes that contain the `Q_OBJECT` macro.

After successful compilation we can create a new `.qml` file and access the `PointSource` type. The `qDebug` output should be visible from the IDE's output window and the **Log** panel in QuickVtk.

>PointSource.qml
{: .hl-caption}

{% highlight qml %}
import Vtk 1.0 as Vtk

Vtk.PointSource {
}

{% endhighlight %}
