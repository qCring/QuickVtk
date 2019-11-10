---
layout: page
nav: docs
title: Part 1 - Basic Implementation
category: Implementing a VTK wrapper in QuickVtk
number: 1
---

# Implementing a new VTK wrapper in QuickVtk
This series of articles discusses the process of implementing a [VTK](https://vtk.org/) wrapper in QuickVtk based on the [vtkPointSource](https://vtk.org/doc/nightly/html/classvtkPointSource.html) implementation.

For a practical approach, you can delete the existing [PointSource]({{ site.baseurl }}/api/Vtk/PointSource) implementation, rebuild the project, and rewrite the wrapper from scratch along with this article.

## Adding a new class
The first step of implementing a wrapper class for an existing [VTK](https://vtk.org/) type is to add new **.hpp** and **.cpp** files to the **QuickVtkLib** project under `src/Lib/Vtk/Wrapper/`. Since we want to wrap the [vtkPointSource](https://vtk.org/doc/nightly/html/classvtkPointSource.html) class, we will name the files `quickVtkPointSource.hpp` and `quickVtkPointSource.cpp`.

The `quickVtk` prefix is used to indicate that our wrapper class `PointSource` will be inside the `quick::Vtk` namespace. Additionally, this [naming convention]({{ site.baseurl }}/docs/reference/naming-conventions) allows us to distinguish QuickVtk wrappers from [VTK](https://vtk.org/) types. `#include "quickVtkPointSource.hpp"` will include the wrapper while `#include <vtkPointSource.h>` includes the type provided by [VTK](https://vtk.org/).

## Basic implementation
Let's start with the class declaration in the header file

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

### Identifying the base class
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
