---
layout: subpage
nav: docs
title: Part 1 - Basic Implementation
category: Implementing a VTK wrapper in QuickVtk
---

# Implementing a VTK Wrapper in QuickVtk
This series of articles discusses the process of implementing a [VTK](https://vtk.org/) wrapper in QuickVtk step by step based on the wrapper implementation for [vtkPointSource](https://vtk.org/doc/nightly/html/classvtkPointSource.html).

For a practical approach, you can delete the existing `quickVtkPointSource` **.cpp** and **.hpp** files, rebuild the project, and rewrite the wrapper from scratch along with the documentation.

## Adding a New Class
The first step of implementing a wrapper class for an existing [VTK](https://vtk.org/) type is to add new **.hpp** and **.cpp** files to the **QuickVtkLib** project under `src/Lib/Vtk/Wrapper/`. Since we want to wrap the [vtkPointSource](https://vtk.org/doc/nightly/html/classvtkPointSource.html) class, the files should be named `quickVtkPointSource.hpp` and `quickVtkPointSource.cpp`.

The `quickVtk` prefix indicates that the wrapper class named `PointSource` is inside the `quick::Vtk` namespace. This [naming convention]({{ site.baseurl }}/reference/naming-conventions) also allows to distinguish wrappers from [VTK](https://vtk.org/) types. `#include "quickVtkPointSource.hpp"` will include the QuickVtk class while `#include <vtkPointSource.h>` includes the type provided by the [VTK](https://vtk.org/) framework.

Let's start by declaring the `PointSource` class in the header file

>quickVtkPointSource.hpp
{: .hl-caption}

{% highlight cpp %}
#pragma once

namespace quick {
  namespace Vtk {

    class PointSource {

    };
  }
}
{% endhighlight %}

## The Base Class
The [vtkPointSource documentation](https://vtk.org/doc/nightly/html/classvtkPointSource.html) gives us all the information we need in order to implement the wrapper class. The inheritance diagram shows, that [vtkPointSource](https://vtk.org/doc/nightly/html/classvtkPointSource.html) is a subclass of [vtkPolyDataAlgorithm](https://vtk.org/doc/nightly/html/classvtkPolyDataAlgorithm.html). Since the wrapper class for [vtkPolyDataAlgorithm](https://vtk.org/doc/nightly/html/classvtkPolyDataAlgorithm.html) is already implemented in QuickVtk, we can simply inherit from [quick::Vtk::PolyDataAlgorithm]({{ site.baseurl }}/api/Vtk/PolyDataAlgorithm).

>quickVtkPointSource.hpp
{: .hl-caption}

{% highlight cpp %}
#pragma once

#include "quickVtkPolyDataAlgorithm.hpp"

namespace quick {
  namespace Vtk {

    class PointSource : public PolyDataAlgorithm {
    };
  }
}

{% endhighlight %}

All wrappers use the same class hierarchy as types in [VTK](https://vtk.org/) for obvious reasons. We inherit all base class methods and members and keep our wrappers consistent with the [VTK](https://vtk.org/) implementation.

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
    };
  }
}
{% endhighlight %}

The `Q_OBJECT` macro is used by the [Meta-Object Compiler (moc)](https://doc.qt.io/qt-5/moc.html) and is required for the signals and slot mechanism, the run-time type information, and the dynamic property system in [Qt](https://www.qt.io/).
