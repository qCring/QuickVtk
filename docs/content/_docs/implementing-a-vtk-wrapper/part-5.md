---
layout: subpage
nav: docs
title: Part 5 - Adding a Vector Property
category: Implementing a VTK wrapper in QuickVtk
---

## Adding a Vector property
Next we are going to implement the `Center` attribute of the [vtkPointSource](https://vtk.org/doc/nightly/html/classvtkPointSource.html) class. [VTK](https://vtk.org/) stores data types like vectors and colors component-wise in native arrays. Instead of adding three individual properties for `x`, `y`, and `z`, QuickVtk provides the [Math::Vector3]({{ site.baseurl }}/api/Math/Vector3) type which we are using to implement a new `center` property.

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
      Q_PROPERTY(quick::Math::Vector3* center READ getCenter CONSTANT);
    private:
      static Qml::Register::Class<PointSource> Register;
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

Note that the `Q_PROPERTY` declaration for `center` uses a pointer and doesn't provide `WRITE` and `NOTIFY` methods but instead uses the `CONSTANT` macro. This means that our `PointSource` always uses the same [Math::Vector3]({{ site.baseurl }}/api/Math/Vector3) instance which has some advantages but also some limitations which we will discuss later. Also, keep in mind that the full typename with all namespaces must be used inside the `Q_PROPERTY` declaration when using custom types.

Let's implement the `getCenter` method and initialize the private `m_center` member variable in the constructor next

>quickVtkPointSource.cpp
{: .hl-caption}

{% highlight cpp %}

#include "quickVtkPointSource.hpp"

namespace quick {
  namespace Vtk {

    Qml::Register::Class<PointSource> PointSource::Register(true);

    PointSource::PointSource() : PolyDataAlgorithm(vtkSmartPointer<vtkPointSource>::New()) {
        this->m_vtkObject = vtkPointSource::SafeDownCast(Algorithm::getVtkObject());

        this->m_center = new Math::Vector3([this]() {
            this->m_vtkObject->SetCenter(this->m_center->getValues().data());
            this->update();
        });
    }

    auto PointSource::getCenter() -> Math::Vector3* {
        return this->m_center;
    }

    // setNumberOfPoints/getNumberOfPoints
  }
}

{% endhighlight %}

Instead of retrieving values from our `m_vtkObject` directly, the `get-` method simply returns the local `m_center` member variable. Let's figure out how we keep our [Math::Vector3]({{ site.baseurl }}/api/Math/Vector3) property updated with the `m_vtkObject`'s `Center` attribute since we don't provide a `set-` property accessor.

## Math::Vector3 Initialization
Every `PointSource` object creates an individual [Math::Vector3]({{ site.baseurl }}/api/Math/Vector3) instance which is used throughout the wrapper's lifetime. This is indicated by the `CONSTANT` macro inside the `Q_PROPERTY` declaration. This means that the `get-` method will always return the same constant [Math::Vector3]({{ site.baseurl }}/api/Math/Vector3) instance when we access the `center` property of our `PointSource` type in [QML](https://doc.qt.io/qt-5/qtqml-index.html).

If we take a quick look at how [Math::Vector3]({{ site.baseurl }}/api/Math/Vector3) is implemented, we will find `Q_PROPERTY` definitions for each vector component. Here, the `WRITE` and `NOTIFY` macros are used since we want to provide read and write access to the `x`, `y`, and `z` properties.

>quickMathVector3.hpp
{: .hl-caption}

{% highlight cpp %}

// namespace quick::Math {

class Vector3 : public QObject {
  Q_OBJECT
  Q_PROPERTY(double x READ getX WRITE setX NOTIFY xChanged);
  Q_PROPERTY(double y READ getY WRITE setY NOTIFY yChanged);
  Q_PROPERTY(double z READ getZ WRITE setZ NOTIFY zChanged);
}

{% endhighlight %}

Since individual vector components can be changed at any time, we need a way to tell our `PointSource` that the underlying [vtkPointSource](https://vtk.org/doc/nightly/html/classvtkPointSource.html) object has to be updated accordingly. We do this by passing a lambda expression to the [Math::Vector3]({{ site.baseurl }}/api/Math/Vector3) constructor.  [Math::Vector3]({{ site.baseurl }}/api/Math/Vector3) objects can not be instantiated without a function object since we always want to be informed if any of the vector components changed. Let's take a closer look at how the [Math::Vector3]({{ site.baseurl }}/api/Math/Vector3) constructor is called from the `PointSource` constructor.

>quickVtkPointSource.cpp
{: .hl-caption}

{% highlight cpp %}

PointSource::PointSource() : PolyDataAlgorithm(vtkSmartPointer<vtkPointSource>::New()) {
    this->m_vtkObject = vtkPointSource::SafeDownCast(Algorithm::getVtkObject());

    this->m_center = new Math::Vector3([this]() {
        this->m_vtkObject->SetCenter(this->m_center->getValues().data());
        this->update();
    });
}

{% endhighlight %}

The lambda's function body will be executed every time a vector component changes. We will see how and when this function object is called in a bit. The first statement will forward the new vector values to our [vtkPointSource](https://vtk.org/doc/nightly/html/classvtkPointSource.html) object. You can see that the [Math::Vector3]({{ site.baseurl }}/api/Math/Vector3) class provides a `getValues()` method for acessing the actual vector values. We have to call `data()` in order to convert the result to a native `float[3]` array which can be passed to the `SetCenter` method. After that we have to update the visualization pipeline by calling `update` on the `PointSource` instance.

Lambda expressions don't have access to variables from their outside scope. But we have to interact with `m_vtkObject` and call `update` somehow. In order to make the `PointSource` object accessible from our lambda, we have to **caputure** a pointer to the current `PointSource` instance via `[this]`.

## Accessing the Vector Property in QML
While there are still some interesting implementation details which we can discuss, we will first take a look at how to interact with our [Math::Vector3]({{ site.baseurl }}/api/Math/Vector3) property in [QML](https://doc.qt.io/qt-5/qtqml-index.html). The following sample demonstrates how the `center` property is assigned inside the `PointSource` object and also how values are controlled by a `Slider` component.

>quickVtkPointSource.qml
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
          center.x: 0.1
          center.y: 0.2
          center.z: 0.3
        }
      }
    }
  }

  Utils.View {
    Utils.Slider {
      from: source; bind: "numberOfPoints"
      min: 1000; max: 50000; step: 100; value: 1000
    }

    Utils.Slider {
      from: source.center; bind: "x"
      min: -1; max: 1; step: 0.001; value: 0
    }

    Utils.Slider {
      from: source.center; bind: "y"
      min: -1; max: 1; step: 0.001; value: 0
    }

    Utils.Slider {
      from: source.center; bind: "z"
      min: -1; max: 1; step: 0.001; value: 0
    }
  }
}

{% endhighlight %}

Note that the `Slider` binds differently to [Math::Vector3]({{ site.baseurl }}/api/Math/Vector3) components. We have to assign `source.center` to the slider's `from` property. We use the `.` operator to access the nested `center` object property of our `PointSource`.

## Recap
Every `PointSource` instance creates its own constant [Math::Vector3]({{ site.baseurl }}/api/Math/Vector3) object. By passing a lambda to the [Math::Vector3]({{ site.baseurl }}/api/Math/Vector3) constructor, we provide a callback function which is executed every time a vector component changes. The vector object itself can be considered `readonly`. We can not assign to the `center` property of our `PointSource` object directly. Only individual components can be set via `center.x`, `center.y`, and `center.z`.

There are still some things we left uncovered about the [Math::Vector3]({{ site.baseurl }}/api/Math/Vector3) implementation. But it might get a bit technical so feel free to jump right to [the next article]({{ site.baseurl }}/docs/part-6) where we will talk about how to implement object references.

## A Bit More About Math::Vector3
In this section, we will talk about the technical aspects of how we handle function objects and vector data in [Math::Vector3]({{ site.baseurl }}/api/Math/Vector3). Let's take a look at the header of our [Math::Vector3]({{ site.baseurl }}/api/Math/Vector3) class.

>quickMathVector3.hpp
{: .hl-caption}

{% highlight cpp %}

#pragma once

#include "quickQmlRegister.hpp"

#include <array>
#include <functional>

#include <QObject>

namespace quick {
  namespace Math {

    class Vector3 : public QObject {
      Q_OBJECT
      Q_PROPERTY(double x READ getX WRITE setX NOTIFY xChanged);
      Q_PROPERTY(double y READ getY WRITE setY NOTIFY yChanged);
      Q_PROPERTY(double z READ getZ WRITE setZ NOTIFY zChanged);
    private:
      using cb_t = std::function<void()>;
      using array_t = std::array<double, 3>;
      cb_t m_callback;
      array_t m_values;
      auto notify() -> void;
    public:
      static Qml::Register::UncreatableClass<Vector3> Register;
      Vector3() = delete;
      Vector3(cb_t&&, array_t = {% raw %}{{0,0,0}}{% endraw %});
      auto setX(double) -> void;
      auto getX() -> double;
      auto setY(double) -> void;
      auto getY() -> double;
      auto setZ(double) -> void;
      auto getZ() -> double;
      auto getValues() -> array_t;
    signals:
      void xChanged();
      void yChanged();
      void zChanged();
    };
  }
}

{% endhighlight %}

Since C++11 a typedef-name can also be introduced by an alias-declaration via the `using` keyword. This is used to define the types `cb_t` and `array_t`. `cb_t` is an alias for `std::function<void()>` and defines the callback type which we use to store the function object that is passed in as a constructor argument. `array_t` defines an `std::array<double, 3>` and is used to store individual vector components. The [std::array](https://en.cppreference.com/w/cpp/container/array) type allows conversion to a C-style array which is exactly how [VTK](https://vtk.org/) expects vector arguments. This enables assigning vectors in one single call instead of using single function calls for each individual vector component.

We can also see the default constructor is deleted. [Math::Vector3]({{ site.baseurl }}/api/Math/Vector3) always requires a function object argument for construction. Additionally, an optional argument is provided which can be used to initialize the vector with specific values. Let's take a look at the implementation.

>quickMathVector3.cpp
{: .hl-caption}

{% highlight cpp %}

#include "quickMathVector3.hpp"

namespace quick {
  namespace Math {

    Qml::Register::UncreatableClass<Vector3> Vector3::Register;

    Vector3::Vector3(cb_t&& cb, array_t values) : m_callback(cb), m_values(values) {
    }

    auto Vector3::notify() -> void {
        this->m_callback.operator()();
    }

    auto Vector3::setX(double x) -> void {
        this->m_values[0] = x;
        emit this->xChanged();
        this->notify();
    }

    auto Vector3::getX() -> double {
        return this->m_values[0];
    }

    auto Vector3::setY(double y) -> void {
        this->m_values[1] = y;
        emit this->yChanged();
        this->notify();
    }

    auto Vector3::getY() -> double {
        return this->m_values[1];
    }

    auto Vector3::setZ(double z) -> void {
        this->m_values[2] = z;
        emit this->zChanged();
        this->notify();
    }

    auto Vector3::getZ() -> double {
        return this->m_values[2];
    }

    auto Vector3::getValues() -> array_t {
        return this->m_values;
    }
  }
}

{% endhighlight %}

The `x`, `y`, and `z` accessors are relatively straight-forward. Components are assigned to the private `std::array` member by reading/writing from/to the underlying array. After assigning either one of the vector components, the `notify()` method will be called which invokes the assigned function object via `this->m_callback.operator()()`. This will execute the specific lambda expression provided by the object that instantiates [Math::Vector3]({{ site.baseurl }}/api/Math/Vector3) and is usually used to retrieve the current vector data via the `getValues()` method. Keep in mind that usually the captured wrapper will be accessed from here.

While lambda captures are a non-trivial topic, we don't have to worry about this too much in QuickVtk since [Math::Vector3]({{ site.baseurl }}/api/Math/Vector3) instances have the same lifetime as the object that created the vector object. This applies to all wrappers that hold [Math::Vector3]({{ site.baseurl }}/api/Math/Vector3) members. The same design is also used for the [Math::Vector2]({{ site.baseurl }}/api/Math/Vector2) type.

The only limitation of this implementation is that vectors can not be assigned or shared across wrappers. By maintaining a 1:1 relationship for wrappers and [Math::Vector3]({{ site.baseurl }}/api/Math/Vector3) instances, we can avoid many different edge cases and benefit from a much simpler implementation.
