---
layout: page
nav: docs
title: Implementing a VTK wrapper class
category: Articles
number: 1
---

# Implementing a new VTK wrapper in QuickVtk
In this article we will discuss the process of implementing the wrapper for [vtkPointSource](https://vtk.org/doc/nightly/html/classvtkPointSource.html) in QuickVtk. For a practical approach, you can delete the existing [PointSource]({{ site.baseurl }}/api/Vtk/PointSource) implementation, rebuild the project, and rewrite the wrapper from scratch along with this article.

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

### Custom Types in QML
While [QML](https://doc.qt.io/qt-5/qtqml-index.html) provides a set of built-in types, custom types have to be registered and imported from a module first. Let's think about how we would like to access the wrapper from a [QML](https://doc.qt.io/qt-5/qtqml-index.html) perspective

>PointSource.qml
{: .hl-caption}

{% highlight qml %}
import Vtk 1.0 as Vtk

Vtk.PointSource {
  numberOfPoints: 1024;
}

{% endhighlight %}  

The [QML engine](https://doc.qt.io/qt-5/qqmlengine.html) resolves all types at runtime. In this case, [QML](https://doc.qt.io/qt-5/qtqml-index.html) is going to look for a [QObject](https://doc.qt.io/qt-5/qobject.html)-derived class named `PointSource` in a module called `Vtk`. If such a type exists, the C++ default constructor will be invoked and a new instance of this type is created.

## QML Type Registration
In order to access our custom type from [QML](https://doc.qt.io/qt-5/qtqml-index.html), we have to register it first. Behind the scenes, `qmlRegisterType<T>` is called for every custom [QML](https://doc.qt.io/qt-5/qtqml-index.html) type at application startup. QuickVtk provides a generic way of registering types via `Qml::Register::Symbol::Class<T>`

>quickVtkPointSource.hpp
{: .hl-caption}

{% highlight cpp %}
#pragma once

#include "quickVtkPolyDataAlgorithm.hpp"

namespace quick {
  namespace Vtk {

    class PointSource : public PolyDataAlgorithm {
    private:
      static Qml::Register::Symbol::Class<PointSource> Register;
    };
  }
}
{% endhighlight %}

`Class<T>` will register the type by extracting type information (class name and namespace) from the type's static [QMetaObject](https://doc.qt.io/qt-5/qmetaobject.html) property provided by the [QObject](https://doc.qt.io/qt-5/qobject.html) base. The [QML type registration article]({{ site.baseurl }}/docs/articles/qml-type-registration) provides a more in-depth explanation on [QML](https://doc.qt.io/qt-5/qtqml-index.html) type registration in QuickVtk.

Since `static` class members are not associated with objects of the class, they are independent variables with static storage duration and have to be defined explicitly on the **.cpp** side. Let's do this next

>quickVtkPointSource.cpp
{: .hl-caption}

{% highlight cpp %}
#include "quickVtkPointSource.hpp"

namespace quick {
  namespace Vtk {

    Qml::Register::Symbol::Class<PointSource> PointSource::Register(true);
  }
}

{% endhighlight %}

The `bool` argument indicates that this type wraps a class from the [VTK](https://vtk.org/) framework and is only used by the **API-Docs** target to determine whether an HTML link to the [VTK](https://vtk.org/) documentation should be provided or not. All [API Reference]({{ site.baseurl }}/api) pages are generated by processing types containing this static `Register` member variable.

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
