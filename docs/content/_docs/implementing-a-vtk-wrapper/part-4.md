---
layout: page
nav: docs
title: Part 4 - Properties
category: Implementing a VTK wrapper in QuickVtk
number: 4
---

## Identifying Properties
Now that we are able to instantiate our `PointSource` in [QML](https://doc.qt.io/qt-5/qtqml-index.html), we want to access some properties. Based on the [vtkPointSource documentation](https://vtk.org/doc/nightly/html/classvtkPointSource.html) we will first identify all available class attributes


VTK attribute | VTK type
:--- | :---
NumberOfPoints | vtkIdType
Center | double [3]
Radius | double
Distribution | int
OutputPointsPrecision | int
RandomSequence | vtkRandomSequence

## Adding a Property
In order to define a new property for `NumberOfPoints` we have to know which [QML](https://doc.qt.io/qt-5/qtqml-index.html) type to use for `vtkIdType`. This type is defined in [vtkType.h](https://vtk.org/doc/nightly/html/vtkType_8h_source.html) and is simply a typedef for `long long`, `long` or `int` depending on the [VTK](https://vtk.org/) build configuration. The important fact is that `NumberOfPoints` is an integer number. We don't really care about different precisions since [QML](https://doc.qt.io/qt-5/qtqml-index.html) uses the built-in `int` type for any integer number. You can read more about C++/[QML](https://doc.qt.io/qt-5/qtqml-index.html) type conversion on [this article from the Qt docs](https://doc.qt.io/qt-5/qtqml-cppintegration-data.html). Additionally, the [type conversion reference]({{ site.baseurl }}/docs/referenccec/type-conversion) provides an overview for basic [VTK](https://vtk.org/)/[QML](https://doc.qt.io/qt-5/qtqml-index.html) type conversion.

Now we can use the `Q_PROPERTY` macro to define a new `numberOfPoints` property together with the associated `get-`, `set-`, and `-changed` method declarations.

>quickVtkPointSource.hpp
{: .hl-caption}

{% highlight cpp %}
#pragma once

#include "quickVtkPolyDataAlgorithm.hpp"
#include <vtkPointSource.h>

namespace quick {
  namespace Vtk {

    class PointSource : public PolyDataAlgorithm {
      Q_OBJECT
      Q_PROPERTY(int numberOfPoints READ getNumberOfPoints WRITE setNumberOfPoints NOTIFY numberOfPointsChanged);
    private:
      static Qml::Register::Symbol::Class<PointSource> Register;
      vtkSmartPointer<vtkPointSource> m_vtkObject;
    public:
      PointSource();
      auto setNumberOfPoints(int) -> void;
      auto getNumberOfPoints() -> int;
    signals:
      void numberOfPointsChanged();
    };
  }
}
{% endhighlight %}

The `READ`, `WRITE`, and `NOTIFY` macros are used to link the property to specific methods. Also note that the `#include` for `vtkPointSource.h` moved to the header file. We have to store a reference to [vtkPointSource](https://vtk.org/doc/nightly/html/classvtkPointSource.html) in order to access it when the `numberOfPoints` (or any other) property changes. For this we will use the private member `m_vtkObject` of type `vtkSmartPointer<vtkPointSource>`.

Let's take a look at the implementation. The constructor initializes the member variable and we have access to the [vtkPointSource](https://vtk.org/doc/nightly/html/classvtkPointSource.html) object through `m_vtkObject` from the `get-` and `set-` methods.

>quickVtkPointSource.cpp
{: .hl-caption}

{% highlight cpp %}
#include "quickVtkPointSource.hpp"

namespace quick {
  namespace Vtk {

    Qml::Register::Symbol::Class<PointSource> PointSource::Register(true);

    PointSource::PointSource() : PolyDataAlgorithm(vtkSmartPointer<vtkPointSource>::New()) {
      this->m_vtkObject = vtkPointSource::SafeDownCast(Algorithm::getVtkObject());
    }

    auto PointSource::setNumberOfPoints(int numberOfPoints) -> void {
      this->m_vtkObject->SetNumberOfPoints(numberOfPoints);
      emit this->numberOfPointsChanged();
      this->update();
    }

    auto PointSource::getNumberOfPoints() -> int {
      return this->m_vtkObject->GetNumberOfPoints();
    }
  }
}

{% endhighlight %}

In case you want to read more on wrapper constructors, take a look at [this article]({{ site.baseurl }}/docs/reference/wrapper-constructors). You will find some information on why `SafeDownCast` is used to assign the `m_vtkObject` member variable from the [Vtk::Algorithm]({{ site.baseurl }}/api/Vtk/Algorithm) base and other implementation details.

## Property Methods
The [property system](https://doc.qt.io/qt-5/properties.html) uses `get-` and `set-` methods to read/write values from/to our C++ instance when interacting with the object in [QML](https://doc.qt.io/qt-5/qtqml-index.html). We will forward new values to the underlying [vtkPointSource](https://vtk.org/doc/nightly/html/classvtkPointSource.html) object using the `m_vtkObject` member, inform the [QML](https://doc.qt.io/qt-5/qtqml-index.html) engine that a value changed by emitting a `-notified` signal, and update the visualization pipeline in order to render a new frame using an `update` method which is available for all [Vtk::Algorithm]({{ site.baseurl }}/api/Vtk/Algorithm)-derived classes.

### getNumberOfPoints
This method will be called from [QML](https://doc.qt.io/qt-5/qtqml-index.html) to retrieve the value for the `numberOfPoints` property. We will return the value from `m_vtkObject->GetNumberOfPoints()` to make sure that our wrapper always returns the same value that our [vtkPointSource](https://vtk.org/doc/nightly/html/classvtkPointSource.html) object is operating on.

### setNumberOfPoints
This method will be called from [QML](https://doc.qt.io/qt-5/qtqml-index.html) every time a new value is assigned to the `numberOfPoints` property. There are three steps involved in applying a new value to a property:

- `m_vtkObject->SetNumberOfPoints(numberOfPoints)` forwards the value to the [vtkPointSource](https://vtk.org/doc/nightly/html/classvtkPointSource.html) object.
- `emit numberOfPointsChanged()` tells [QML](https://doc.qt.io/qt-5/qtqml-index.html) that all observers of the `numberOfPoints` property should be updated. We will take a closer look at `-changed` signals a bit later.
- `update()` is an inherited method from the [Vtk::Algorithm]({{ site.baseurl }}/api/Vtk/Algorithm) base class. Basically, all algorithms in the context of [VTK](https://vtk.org/) are connectable nodes in the visualization pipeline. If a single node changes, the whole pipeline has to be updated and a new image must be rendered.

While `getNumberOfPoints` and `setNumberOfPoints` are both implemented in the **.cpp** file, the `numberOfPointsChanged` method is only declared as signal in the header file. The [Meta-Object Compiler (moc)](https://doc.qt.io/qt-5/moc.html) does the work for us and we only have to `emit` this signal after a value was changed.

## Property access in QML
After rebuilding the project we have access to the `numberOfPoints` property. In order to render the [VTK](https://vtk.org/) content in [QML](https://doc.qt.io/qt-5/qtqml-index.html), we will implement a simple pipeline by connecting different components inside a `Vtk.Viewer` component

>PointSource.qml
{: .hl-caption}

{% highlight qml %}
import Vtk 1.0 as Vtk

Vtk.Viewer {
  anchors.fill: parent;

  mouseEnabled: true;

  Vtk.Actor {
    Vtk.PolyDataMapper {
      Vtk.PointSource {
        numberOfPoints: 20000;
      }
    }
  }
}

{% endhighlight %}

Instead of using a constant value of `20000`, we can bind the `numberOfPoints` property to a control element. QuickVtk provides some user input components in the `Utils` module. We will import this module and use a `Slider` element to adjust the `numberOfPoints` property.

>PointSource.qml
{: .hl-caption}

{% highlight qml %}
import QtQuick 2.9
import Vtk 1.0 as Vtk
import Utils 1.0 as Utils

Item {
  anchors.fill: parent

  Vtk.Viewer {
    anchors.fill: parent

    mouseEnabled: true;

    Vtk.Actor {
      Vtk.PolyDataMapper {
        Vtk.PointSource {
          id: source
          numberOfPoints: 20000
        }
      }
    }
  }

  Utils.View {
    Utils.Slider {
      from: source
      bind: "numberOfPoints"

      min: 1000
      max: 50000
      step: 100
      value: 1000
    }
  }
}

{% endhighlight %}

Note that the root object is a simple [QML Item](https://doc.qt.io/qt-5/qml-qtquick-item.html). This is necessary because of the fact that `Vtk.Viewer` expects all child-components to be of type [Vtk.Object]({{ site.baseurl }}/api/Vtk/Object) in order to build the visualization pipeline from the object hierarchy.

`Utils.View` provides a container view on the bottom-right and conveniently arranges elements in a row layout automatically without having to specify layout parameters for each component individually.

The `Slider` component expects:
- an object id (in case `source` which refers to our `PointSource`)
- the name of the property to bind to (`numberOfPoints`)
- some optional parameters:
  - `min` value
  - `max` value
  - a stepsize `step`
  - an initial value `value`
