---
layout: subpage
nav: docs
title: Part 2 - Type Registration
category: Implementing a VTK wrapper in QuickVtk
---
## Custom Types in QML
While [QML](https://doc.qt.io/qt-5/qtqml-index.html) provides a set of built-in types, custom types have to be registered and imported from a module first. Let's think about how we would like to access the wrapper from a [QML](https://doc.qt.io/qt-5/qtqml-index.html) perspective

>PointSource.qml
{: .hl-caption}

{% highlight qml %}

import Vtk 1.0 as Vtk

Vtk.PointSource {
  numberOfPoints: 1024;
}

{% endhighlight %}  

The [QML engine](https://doc.qt.io/qt-5/qqmlengine.html) resolves the type at runtime by looking for a [QObject](https://doc.qt.io/qt-5/qobject.html)-derived class named `PointSource` in a module called `Vtk`. If the type exists, the default constructor will be invoked and a new instance of this type is created.

## QML Type Registration
In order to access our custom type from [QML](https://doc.qt.io/qt-5/qtqml-index.html), we have to register it first. Behind the scenes, the `qmlRegisterType<T>` function has to be called for every custom [QML](https://doc.qt.io/qt-5/qtqml-index.html) type at application startup. QuickVtk provides a generic way of registering types by simply adding a static `Qml::Register::Class<T>` member variable to the class.

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
    };
  }
}

{% endhighlight %}

`Class<T>` will register the type by extracting type information from the type's static [QMetaObject](https://doc.qt.io/qt-5/qmetaobject.html) property provided by the [QObject](https://doc.qt.io/qt-5/qobject.html) base. The class name is used as a unique type identifier while the namespace is used to determine the module name. In this case the class `PointSource` will be registered to the module `Vtk`.

Since `static` class members are not associated with objects of the class, they are independent variables with static storage duration and have to be defined explicitly on the **.cpp** side. Let's do this next

>quickVtkPointSource.cpp
{: .hl-caption}

{% highlight cpp %}

#include "quickVtkPointSource.hpp"

namespace quick {
  namespace Vtk {
    Qml::Register::Class<PointSource> PointSource::Register(true);
  }
}

{% endhighlight %}

The `bool` argument indicates that this type wraps a class from the [VTK](https://vtk.org/) framework and is only used by the **API-Docs** target to determine whether an HTML link to the [VTK](https://vtk.org/) documentation should be provided or not.

## Implementation of the Type Registration System
Usually, every [QML](https://doc.qt.io/qt-5/qtqml-index.html) application registers a set of custom types on application startup by calling [qmlRegisterType\<T\>](https://doc.qt.io/qt-5/qqmlengine.html#qmlRegisterType-2) or other available register functions. In our case we would have to write the following line in order to register the new `PointSource` type to the `Vtk 1.0` module:

{% highlight cpp %}

qmlRegisterType<quick::Vtk::PointSource>("Vtk", 1, 0, "PointSource");

{% endhighlight %}

Instead of mapping each type individually and maintaining a list of `qmlRegisterType` calls somewhere in the  code like shown in the above example, we can rely on the static `Qml::Register::Class<T>` member. Let's take a look at the implementation of the `Class<T>` struct which can be found in `src/Lib/Utils/quickQmlRegister.hpp`

>quickQmlRegister.hpp
{: .hl-caption}

{% highlight cpp %}

// namespace quick::Qml::Register {

  template <class T>
  struct Class {

    Class(bool isWrapper = false) {

      auto initializer = [isWrapper]() {
        QMetaObject metaObject = T::staticMetaObject;
        auto name = QString(metaObject.className());
        auto prefix = name.section("::", 1, 1);
        auto className = name.section("::", 2, 2);

        qmlRegisterType<T>(prefix.toStdString().c_str(), 1, 0, className.toStdString().c_str());

        TypeInfo::MakeSymbol::Class(metaObject, isWrapper);
      };

      Initializers::GetList().append(initializer);
    }
  };

{% endhighlight %}

Let's focus on the `qmlRegisterType<T>` function call first. We know that the first parameter is used to identify the module. The second and third arguments specify the module version (which is always 1.0 since versioning the `Vtk` module is not really necessary yet) and the last argument has to be the typename.

Every type argument `T` must be a subclass of [QObject](https://doc.qt.io/qt-5/qobject.html) in order to be compatible with [QML](https://doc.qt.io/qt-5/qtqml-index.html). This allows us to access the static [QMetaObject](https://doc.qt.io/qt-5/qmetaobject.html) member through `T::staticMetaObject` (which is defined in the [QObject](https://doc.qt.io/qt-5/qobject.html) base class). This expression is evaluated at compile-time (see [SFINAE](https://en.cppreference.com/w/cpp/language/sfinae)) and we can safely retrieve the full type identifier which in the case of our `PointSource` example evaluates to `quick::Vtk::PointSource`. Now we can extract the type name as well as the module name and register the type to [QML](https://doc.qt.io/qt-5/qtqml-index.html) by calling `qmlRegisterType` with the correct arguments.

Since all of the above code is stored in a lambda expression, we haven't really done anything yet. Instead, we store these initializers in a list for every type that defines a static `Qml::Register::Class<T>` member for later execution via `Initializers::GetList().append(initializer)`. All of this is implemented in the struct's constructor so we only have to define a static `Register` member per class.

Since all of these lambdas are added at compile-time, we can invoke them safely at runtime from the `App::Instance` class before starting the [QML engine](https://doc.qt.io/qt-5/qqmlengine.html). Calling the static `Qml::RegisterTypes()` function iterates through all available function objects and performs the actual type registration

>quickQmlRegister.cpp
{: .hl-caption}

{% highlight cpp %}

// namespace quick::Qml {

  auto RegisterTypes() -> void {
    for (auto initializer : Register::Initializers::GetList()) {
      initializer();
    }
  }

{% endhighlight %}

## Recap

In order to register custom types in [QML](https://doc.qt.io/qt-5/qtqml-index.html), we have to call `qmlRegisterType` for every type explicitly somewhere in C++ before starting the [QML engine](https://doc.qt.io/qt-5/qqmlengine.html).

>Explicit type registration
{: .hl-caption}

{% highlight cpp %}

#include "quickMathVector2.hpp"
#include "quickMathVector3.hpp"
#include "quickVtkAbstractMapper.hpp"
#include "quickVtkAbstractMapper3D.hpp"
#include "quickVtkAbstractPolyDataReader.hpp"
#include "quickVtkAbstractVolumeMapper.hpp"
#include "quickVtkAbstractWidget.hpp"
#include "quickVtkActor.hpp"
#include "quickVtkActor2D.hpp"
#include "quickVtkAdaptiveSubdivissionFilter.hpp"
#include "quickVtkAlgorithm.hpp"

// and so on...

auto RegisterTypes() -> void {

  qmlRegisterType<Math.Vector2>("Vtk", 1, 0, "Vector2");
  qmlRegisterType<Math.Vector3>("Vtk", 1, 0, "Vector3");
  qmlRegisterType<Vtk.AbstractMapper>("Vtk", 1, 0, "AbstractMapper");
  qmlRegisterType<Vtk.AbstractMapper3D>("Vtk", 1, 0, "AbstractMapper3D");
  qmlRegisterType<Vtk.AbstractPolyDataReader>("Vtk", 1, 0, "AbstractPolyDataReader");
  qmlRegisterType<Vtk.AbstractVolumeMapper>("Vtk", 1, 0, "AbstractVolumeMapper");
  qmlRegisterType<Vtk.AbstractWidget>("Vtk", 1, 0, "AbstractWidget");
  qmlRegisterType<Vtk.Actor>("Vtk", 1, 0, "Actor");
  qmlRegisterType<Vtk.Actor2D>("Vtk", 1, 0, "Actor2D");
  qmlRegisterType<Vtk.AdaptiveSubdivisionFilter>("Vtk", 1, 0, "AdaptiveSubdivisionFilter");
  qmlRegisterType<Vtk.Algorithm>("Vtk", 1, 0, "Algorithm");

  // and so forth...
}

{% endhighlight %}

Maintaining a list of `qmlRegisterType` calls would be not ideal for obvious reasons. Typing errors, missing or redundant `#includes` and the inability to support refactoring without manually adjusting the code would introduce many potential problems with this approach.

Instead, we utilize the constructor of a generic struct simply by creating a static `Register` member of type `Qml::Register::Class<T>`. The logic necessary for type registration is stored in a function object which is added to a list of initializer lambdas at compile-time which we can invoke for all types at application startup from the `App::Instance` class by calling `Qml::RegisterTypes()`.

The main advantage of this generic approach is that wrappers are self-contained and implementation is structured and straight-forward while also avoiding many different pitfalls by design.

Another advantage of this system is that additional logic can be executed on a per-type basis. After a type is registered to [QML](https://doc.qt.io/qt-5/qtqml-index.html), the static `TypeInfo::MakeSymbol::Class()` method is called to create an entry in the type browser. For each wrapper the associated [QMetaObject](https://doc.qt.io/qt-5/qmetaobject.html) is used to access type information like the list of available properties, enums and method definitions. All pages from the [API Docs]({{ site.baseurl }}/api) section of this website are also generated based on type introspection provided by [Qt](https://www.qt.io/).
