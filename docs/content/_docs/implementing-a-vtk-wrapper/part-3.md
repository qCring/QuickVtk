---
layout: subpage
nav: docs
title: Part 3 - Constructor
category: Implementing a VTK wrapper in QuickVtk
number: 3
---

## Adding the Constructor
We have a basic implementation for our `PointSource` class and registered the type to the [QML engine](https://doc.qt.io/qt-5/qqmlengine.html). Now let's declare the default constructor in the header which will be called every time a `PointSource` is created in [QML](https://doc.qt.io/qt-5/qtqml-index.html)

>quickVtkPointSource.hpp
{: .hl-caption}

{% highlight cpp %}

#pragma once

#include "quickVtkPolyDataAlgorithm.hpp"

namespace quick {
  namespace Vtk {

    class PointSource : public PolyDataAlgorithm {
      Q_OBJECT
    private:
      static Qml::Register::Class<PointSource> Register;
    public:
      PointSource();
    };
  }
}

{% endhighlight %}

Since the `PolyDataAlgorithm` constructor expects an argument, we have to implement the  default constructor for our `PointSource` wrapper explicitly. We will take a closer look at this in just a bit.

>quickVtkPointSource.cpp
{: .hl-caption}

{% highlight cpp %}

#include "quickVtkPointSource.hpp"
#include <vtkPointSource.h>

namespace quick {
  namespace Vtk {

    Qml::Register::Symbol::Class<PointSource> PointSource::Register(true);

    PointSource::PointSource() : PolyDataAlgorithm(vtkSmartPointer<vtkPointSource>::New()) {
      qDebug() << "Hello, PointSource!";
    }
  }
}

{% endhighlight %}

Let's ignore the call to the [Vtk::PolyDataAlgorithm]({{ site.baseurl }}/api/Vtk/PolyDataAlgorithm) base constructor for now. Just note that we need to `#include <vtkPointSource.h>` in order to pass the proper argument via `vtkSmartPointer<vtkPointSource>::New()`. First we want to see if we can get our `PointSource` to say "Hi" by creating a new instance in [QML](https://doc.qt.io/qt-5/qtqml-index.html).

## Creating a PointSource in QML
Since we added a default constructor, we should be able to create our `PointSource` in [QML](https://doc.qt.io/qt-5/qtqml-index.html). After rebuilding the project, we can create a new `.qml` file and take a look at how things work out with our `PointSource` implementation.

>PointSource.qml
{: .hl-caption}

{% highlight qml %}

import Vtk 1.0 as Vtk

Vtk.PointSource {
}

{% endhighlight %}

After loading the **.qml** file in QuickVtk, we should see the `qDebug` output in the IDE's output window and also the application's **Log** panel. This indicates that the constructor was called as expected and that we successfully created a new `PointSource` object from [QML](https://doc.qt.io/qt-5/qtqml-index.html).

In case you encounter linker errors, try to rebuild the project in [CMake](https://cmake.org/). Some IDEs don't properly invoke the [Meta-Object Compiler](https://doc.qt.io/qt-5/moc.html) after adding new classes that contain the `Q_OBJECT` macro. In some other cases, newly created source files are not associated with the correct build target. Rebuilding the project via [CMake](https://cmake.org/) should fix these issues.

## Storing a vtkObject Reference
Each wrapper has to store a local reference to the corresponding [VTK](https://vtk.org/) object for data exchange. In order to access the underlying [vtkPointSource](https://vtk.org/doc/nightly/html/classvtkPointSource.html), we will add a private member variable to the `PointSource` class. Note that we have to move the `#include` for `<vtkPointSource.h>` from the **.cpp** file to the header.

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
    private:
      static Qml::Register::Class<PointSource> Register;
      vtkSmartPointer<vtkPointSource> m_vtkObject;
    public:
      PointSource();
    };
  }
}

{% endhighlight %}

We are going to initialize the `m_vtkObject` member in the constructor. We want to make sure that the reference is always valid so that we can safely access our `m_vtkObject` and avoid `nullptr`-checks. This might seem like bad practice but we have full control over the object's lifecycle. Instantiation is always immediate. And since the [vtkSmartPointer](https://vtk.org/doc/nightly/html/classvtkSmartPointer.html) is bound to the wrapper, we don't have to worry about the smart pointer's reference count either.

Let's take a look at how an object reference is assigned to our private `m_vtkObject` member. While it might seem a bit confusing at first, we will see what the advantages are of doing things this way

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
  }
}

{% endhighlight %}

Before the function body of the `PointSource` constructor begins executing, initialization of all direct bases, virtual bases and data members is finished. This means that the object which we created via `vtkSmartPointer<vtkPointSource>::New()` is already created and processed by the base constructor. Let's take a quick look at the [Vtk::PolyDataAlgorithm]({{ site.baseurl }}/api/Vtk/PolyDataAlgorithm) constructor and find out how the [vtkPointSource](https://vtk.org/doc/nightly/html/classvtkPointSource.html) argument is processed.

>quickVtkPolyDataAlgorithm.cpp
{: .hl-caption}

{% highlight cpp %}

PolyDataAlgorithm::PolyDataAlgorithm(vtkSmartPointer<vtkPolyDataAlgorithm> vtkObject) : Algorithm(vtkObject) {
}

{% endhighlight %}

The [Vtk::PolyDataAlgorithm]({{ site.baseurl }}/api/Vtk/PolyDataAlgorithm) constructor also forwards the argument to the [Vtk::Algorithm]({{ site.baseurl }}/api/Vtk/Algorithm) base class constructor. So let's see what happens there

>quickVtkPointSource.cpp
{: .hl-caption}

{% highlight cpp %}

Algorithm::Algorithm(vtkSmartPointer<vtkAlgorithm> vtkObject) : Vtk::Object(Object::Type::Algorithm),
m_vtkObject(vtkObject) { // <- Aha!
}

{% endhighlight %}

While the constructor chain goes even further to [Vtk::Object]({{ site.baseurl }}/api/Vtk/Object), we can see that the `vtkObject` argument is assigned to a local member via `m_vtkObject(vtkObject)` using the [initializer list](https://en.cppreference.com/w/cpp/language/initializer_list).

This means that the [vtkPointSource](https://vtk.org/doc/nightly/html/classvtkPointSource.html) object which we created in our `PointSource` class is passed through all base constructors until the [Vtk::Algorithm]({{ site.baseurl }}/api/Vtk/Algorithm) base class eventually assigns the constructor argument to a local member variable. The only difference is that the [Vtk::Algorithm]({{ site.baseurl }}/api/Vtk/Algorithm) wrapper uses the more generic [vtkAlgorithm](https://vtk.org/doc/nightly/html/classvtkAlgorithm.html)>< type. Since [vtkAlgorithm](https://vtk.org/doc/nightly/html/classvtkAlgorithm.html) is an abstract type, [Vtk::Algorithm]({{ site.baseurl }}/api/Vtk/Algorithm) can never create an object on its own. Instead, the `m_vtkObject` variable can only be assigned from the constructor argument provided by subclasses.

Keep in mind that all of this happens before the `PointSource` constructor begins execution. At the time a new `PointSource` instance is constructed, all base classes are already initialized and the initializer list ensures that the [vtkPointSource](https://vtk.org/doc/nightly/html/classvtkPointSource.html) argument which we passed to our base classes is assigned to the private `m_vtkObject` member variable of the [Vtk::Algorithm]({{ site.baseurl }}/api/Vtk/Algorithm) class.

Let's take another look at our `PointSource` constructor which should be easier to understand now.

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
  }
}

{% endhighlight %}

The [Vtk::Algorithm]({{ site.baseurl }}/api/Vtk/Algorithm)-derived `getVtkObject` method is used to retrieve the earlier created [vtkPointSource](https://vtk.org/doc/nightly/html/classvtkPointSource.html) reference. This happens in the constructor body after all base classes and initializer lists are processed and we can safely access the `m_vtkObject` member from [Vtk::Algorithm]({{ site.baseurl }}/api/Vtk/Algorithm). A `SafeDownCast` converts the [vtkAlgorithm](https://vtk.org/doc/nightly/html/classvtkAlgorithm.html) object to [vtkPointSource](https://vtk.org/doc/nightly/html/classvtkPointSource.html) and assigns the reference to the private member variable.

## Why so Complicated
Alternatively, we could just pass the [VTK](https://vtk.org/) object to our base class. Assume, our [Vtk::Algorithm]({{ site.baseurl }}/api/Vtk/Algorithm) base provided a `setVtkAlgorithm` method

>Manually forwarding the vtkPointSource object
{: .hl-caption}

{% highlight cpp %}

PointSource::PointSource() {
  this->m_vtkObject = vtkSmartPointer<vtkPointSource>::New();
  this->setVtkAlgorithm(this->m_vtkObject);
}

{% endhighlight %}

While this would make our constructors a lot simpler in terms of implementation, this design would introduce two major problems. The first one is that there is no way to make sure that `setVtkAlgorithm` is actually called from [Vtk::Algorithm]({{ site.baseurl }}/api/Vtk/Algorithm) subclasses. Also, timing becomes an issue. Depending on **when** `setVtkAlgorithm` is called, we would have to consider that the `m_vtkObject` reference could be a `nullptr` at any time. This would only affect base classes which in some cases could try to access their unitialized `m_vtkObject` member. Another issue is that classes that wrap abstract [VTK](https://vtk.org/) types would be creatable by default. We would have to explicitly declare the default constructors of such types as private or deleted.

But why do we even have to forward the wrapped [VTK](https://vtk.org/) type to our base class? If we wouldn't have to forward our [vtkPointSource](https://vtk.org/doc/nightly/html/classvtkPointSource.html) object to [Vtk::Algorithm]({{ site.baseurl }}/api/Vtk/Algorithm), things would be a lot easier. The short answer is that our base classes also have to interact with the underlying [VTK](https://vtk.org/) object. Even though we don't go in too much detail in these articles, there are some cases where properties or methods which are implemented in the base class need to access the [VTK](https://vtk.org/) object. The reason why [Vtk::Algorithm]({{ site.baseurl }}/api/Vtk/Algorithm) needs a reference to a [vtkAlgorithm](https://vtk.org/doc/nightly/html/classvtkAlgorithm.html) object is that the visualization pipeline must be connected and updated. This is done by using the `SetInputConnection` and `GetOutputPort` methods provided by [vtkAlgorithm](https://vtk.org/doc/nightly/html/classvtkAlgorithm.html). So we just can't avoid to hold a [vtkAlgorithm](https://vtk.org/doc/nightly/html/classvtkAlgorithm.html) reference inside our [Vtk::Algorithm]({{ site.baseurl }}/api/Vtk/Algorithm) class.

But let's come back to why constructors are designed the way they are. We want to ensure that only valid objects can be created. We do this by requiring all necessary arguments in the constructor. We can rely on compile-time checks instead of running into runtime errors. Bassically we are trying to make the QuickVtk API hard to misuse which is just as important as making it easy to use.

## Recap
Each wrapper has to implement an explicit constructor and forward the underlying [VTK](https://vtk.org/) object to the base class constructor. In order to access the wrapped object, we use a private member variable which we assign by the `getVtkObject` method provided by our base class. A `SafeDownCast` is necessary to convert a generic type to the corresponding specific wrapper type like in our case [vtkPointSource](https://vtk.org/doc/nightly/html/classvtkPointSource.html). Since we have full control over the [VTK](https://vtk.org/) object, we don't need to perform `nullptr`-checks because our object will be valid throughout the entire lifetime of our wrapper.
