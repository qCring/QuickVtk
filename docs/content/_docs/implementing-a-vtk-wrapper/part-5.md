---
layout: subpage
nav: docs
title: Part 5 - Adding a Vector Property
category: Implementing a VTK wrapper in QuickVtk
---

## Adding a Vector property
Next we are going to implement the `Center` property. [VTK](https://vtk.org/) uses native arrays for data types like vectors and colors. QuickVtk provides the [Math::Vector3]({{ site.baseurl }}/api/Math/Vector3) type which we are using to implement the new `center` property.

>quickVtkPointSource.hpp
{: .hl-caption}

{% highlight cpp %}
#pragma once

#include "quickVtkPolyDataAlgorithm.hpp"
#include "quickMathVector3.hpp"

#include <vtkPointSource.h>

namespace quick {
  namespace Vtk {

    class PointSource : public PolyDataAlgorithm {
      Q_OBJECT
      Q_PROPERTY(int numberOfPoints READ getNumberOfPoints WRITE setNumberOfPoints NOTIFY numberOfPointsChanged);
      Q_PROPERTY(Math::Vector3* center READ getCenter CONSTANT);
    private:
      static Qml::Register::Symbol::Class<PointSource2> Register;
      vtkSmartPointer<vtkPointSource> m_vtkObject;
      Math::Vector3* m_center;
    public:
      PointSource();
      auto setNumberOfPoints(int) -> void;
      auto getNumberOfPoints() -> int;
      auto getCenter() -> Math::Vector3*;
    signals:
      void numberOfPointsChanged();
    };
  }
}

{% endhighlight %}

Note that the property definition for `center` uses a pointer and doesn't provide `WRITE` and `NOTIFY` methods but instead uses the `CONSTANT` macro. This means that our `PointSource` uses a constant [Vector3]({{ site.baseurl }}/api/Math/Vector3) reference and can only be assigned component-wise. Let's implement the `getCenter` method and initialize the `m_center` member variable in the constructor in the **.cpp** file next

>quickVtkPointSource.cpp
{: .hl-caption}

{% highlight cpp %}
#include "quickVtkPointSource.hpp"

namespace quick {
  namespace Vtk {

    Qml::Register::Symbol::Class<PointSource> PointSource::Register(true);

    PointSource::PointSource() : PolyDataAlgorithm(vtkSmartPointer<vtkPointSource>::New()) {
        this->m_vtkObject = vtkPointSource::SafeDownCast(Algorithm::getVtkObject());

        this->m_center = new Math::Vector3([this](){
            this->m_vtkObject->SetCenter(this->m_center->getValues().data());
            this->update();
        });
    }

    auto PointSource::setNumberOfPoints(int numberOfPoints) -> void {
        this->m_vtkObject->SetNumberOfPoints(numberOfPoints);
        emit this->numberOfPointsChanged();
        this->update();
    }

    auto PointSource::getNumberOfPoints() -> int {
        return this->m_vtkObject->GetNumberOfPoints();
    }

    auto PointSource::getCenter() -> Math::Vector3* {
        return this->m_center;
    }
  }
}

{% endhighlight %}

The `get-` method is fairly simple and just returns the private member variable `m_center`. Instead of providing a `set-` method, every `PointSource` creates an individual [Vector3]({{ site.baseurl }}/api/Math/Vector3) instance. The [Vector3]({{ site.baseurl }}/api/Math/Vector3) constructor expects a [lambda expression](https://en.cppreference.com/w/cpp/language/lambda) where a reference to the `PointSource` instance is captured via `[this]`. This allows the [Vector3]({{ site.baseurl }}/api/Math/Vector3) to access the `m_vtkObject` to assign vector data to the `vtkPointSource` object and also invoke the `update` method from within an unnamed function which is executed if a vector component (x,y, or z) changes.
