---
layout: subpage
nav: docs
title: Part 7 - Adding an Object Property
category: Implementing a VTK wrapper in QuickVtk
number: 7
---

## Adding an Object Property
The [vtkPointSource](https://vtk.org/doc/nightly/html/classvtkPointSource.html) class uses a certain strategy for calculating individual points. If we don't want to use the default algorithm, we can provide an alternative point generator via the `SetRandomSequence` method. The method expects an object reference to a [vtkRandomSequence](https://vtk.org/doc/nightly/html/classvtkRandomSequence.html)-derived class. We will implement the `randomSequence` property in order to assign such objects to our `PointSource`.

Object type properties are a bit more complex to implement since we have to consider object lifetimes. If we are referencing objects and allow them to be assigned at runtime, we have to make sure that we also handle cases where objects might be uninitialized. We already used an object property for the `center` property which we implemented by using the [Math::Vector3]({{ site.baseurl }}/api/Math/Vector3) type. All properties that hold a reference to an object can be considered object properties. But in this case we will not use `CONSTANT` declaration to provide a read-only object.

Let's start by adding a new `Q_PROPERTY` to our class together with the related `get-`, `set-`, and `-changed` methods. We will also add the private member variable `m_randomSequence` which will hold a reference to the assigned `Vtk::RandomSequence` object. If no [Vtk::RandomSequence]({{ site.baseurl }}/api/Vtk/RandomSequence) object is assigned, the property will be `nullptr`.

>quickVtkPointSource.hpp
{: .hl-caption}

{% highlight cpp %}

#pragma once

#include "quickVtkPolyDataAlgorithm.hpp"
#include "quickVtkRandomSequence.hpp"
#include "quickMathVector3.hpp"

#include <vtkPointSource.h>

namespace quick {
  namespace Vtk {

    class PointSource : public PolyDataAlgorithm {
      Q_OBJECT
    public:
      enum Distribution {
        UniformDistribution = VTK_POINT_UNIFORM,
        ShellDistribution = VTK_POINT_SHELL
      };
    private:
      Q_ENUM(Distribution);
      Q_PROPERTY(quick::Math::Vector3* center READ getCenter CONSTANT);
      Q_PROPERTY(Distribution distribution READ getDistribution WRITE setDistribution NOTIFY distributionChanged);
      Q_PROPERTY(quick::Vtk::RandomSequence* randomSequence READ getRandomSequence WRITE setRandomSequence NOTIFY randomSequenceChanged);
      Q_PROPERTY(int numberOfPoints READ getNumberOfPoints WRITE setNumberOfPoints NOTIFY numberOfPointsChanged);
    private:
      static Qml::Register::Class<PointSource> Register;
      vtkSmartPointer<vtkPointSource> m_vtkObject;
      Math::Vector3* m_center;
      RandomSequence* m_randomSequence;
    public:
      PointSource();
      auto setDistribution(Distribution) -> void;
      auto getDistribution() -> Distribution;
      auto setNumberOfPoints(int) -> void;
      auto getNumberOfPoints() -> int;
      auto getCenter() -> Math::Vector3*;
      auto setRandomSequence(RandomSequence*) -> void;
      auto getRandomSequence() -> RandomSequence*;
    signals:
      void distributionChanged();
      void numberOfPointsChanged();
      void randomSequenceChanged();
    };
  }
}

{% endhighlight %}

The only difference between [Math::Vector3]({{ site.baseurl }}/api/Math/Vector3) and [Vtk::RandomSequence]({{ site.baseurl }}/api/Vtk/RandomSequence) is that we also provide a `set-` method and define a `-changed` signal for the property. Let's take a look at the implementation.

>quickVtkPointSource.cpp
{: .hl-caption}

{% highlight cpp %}

#include "quickVtkPointSource.hpp"

namespace quick {

  namespace Vtk {

    Qml::Register::Class<PointSource> PointSource::Register(true);

    PointSource::PointSource() : PolyDataAlgorithm(vtkSmartPointer<vtkPointSource>::New()) {
      this->m_vtkObject = vtkPointSource::SafeDownCast(Algorithm::getVtkObject());

      this->m_center = new Math::Vector3([this](){
        this->m_vtkObject->SetCenter(this->m_center->getValues().data());
        this->update();
      });
    }

    auto PointSource::setRandomSequence(RandomSequence* randomSequence) -> void {
      this->m_randomSequence = randomSequence;

      if (randomSequence == nullptr) {
        this->m_vtkObject->SetRandomSequence(nullptr);
      } else {
        this->m_vtkObject->SetRandomSequence(randomSequence->getVtkObject());
        randomSequence->initialize();
      }

      emit this->randomSequenceChanged();
      this->update();
    }

    auto PointSource::getRandomSequence() -> RandomSequence* {
      return this->m_randomSequence;
    }
  }
}

{% endhighlight %}

We don't have to initialize our `m_randomSequence` member variable in the constructor since there is no [vtkRandomSequence](https://vtk.org/doc/nightly/html/classvtkRandomSequence.html) object assigned to [vtkPointSource](https://vtk.org/doc/nightly/html/classvtkPointSource.html) by default. Instead, we provide the `setRandomSequence` method which is called every time we assign an object to the `randomSequence` property. If the assigned object is not `nullptr`, we can access the underlying [vtkRandomSequence](https://vtk.org/doc/nightly/html/classvtkRandomSequence.html) object by calling `getVtkObject()`. We will use the returned object reference as an argument for the `m_vtkObject->SetRandomSequence()` call which effectively connects the [vtkRandomSequence](https://vtk.org/doc/nightly/html/classvtkRandomSequence.html) to our [vtkPointSource](https://vtk.org/doc/nightly/html/classvtkPointSource.html) object. The `initialize` method is used to reset the seed which is used to generate random number values from our [Vtk::RandomSequence]({{ site.baseurl }}/api/Vtk/RandomSequence) object. We will discuss this in just a bit.

If the assigned value is a `nullptr`, we have to tell our [vtkPointSource](https://vtk.org/doc/nightly/html/classvtkPointSource.html) object to use the default point generator method. We do this by passing a `nullptr` argument to the `SetRandomSequence` method. We will always emit the `randomSequenceChanged` signal and update the visualization pipeline after assigning a new value to the `randomSequence` property. It doesn't make a difference if the argument is valid or `nullptr`. In both cases an update is necessary. The `get-` method simply returns the current `m_randomSequence` object which can be `nullptr` or an instance of any [vtkRandomSequence](https://vtk.org/doc/nightly/html/classvtkRandomSequence.html)-derived class.

You might be wondering, why we don't have to use lambda expressions like we did for our [Math::Vector3]({{ site.baseurl }}/api/Math/Vector3) property. We will come back to this.

## Accessing the Object Property in QML
After successful compilation we can use our `randomSequence` property in [QML](https://doc.qt.io/qt-5/qtqml-index.html). We will create a [Vtk::MinimalStandardRandomSequence]({{ site.baseurl }}/api/Vtk/MinimalStandardRandomSequence) object (a subclass of the abstract [Vtk::RandomSequence]({{ site.baseurl }}/api/Vtk/RandomSequence) base class) and use the ternary `? :` operator to assign to the `randomSequence` property based on a condition. This allows us to quickly switch between the default point generation algorithm provided by [vtkPointSource](https://vtk.org/doc/nightly/html/classvtkPointSource.html) and a more specific algorithm from [Vtk::RandomSequence]({{ site.baseurl }}/api/Vtk/RandomSequence)-derived classes.

>PointSource.qml
{: .hl-caption}

{% highlight qml %}

import QtQuick 2.9
import Vtk 1.0 as Vtk
import Utils 1.0 as Utils

Item {
  id: root;

  anchors.fill: parent
  property bool useRandomSequence: false;

  Vtk.MinimalStandardRandomSequence {
    id: sequence;
    seed: 128;
  }

  Vtk.Viewer {
    anchors.fill: parent

    mouseEnabled: true;

    Vtk.Actor {
      Vtk.PolyDataMapper {
        Vtk.PointSource {
          id: source
          numberOfPoints: 2000
          distribution: Vtk.PointSource.UniformDistribution
          randomSequence: root.useRandomSequence ? sequence : null;
        }
      }
    }
  }

  Utils.View {

    Utils.ComboBox {
      label: "Distribution";
      model: ["Uniform", "Shell"];
      onIndexChanged: {
        switch (index) {
          case 0: source.distribution = Vtk.PointSource.UniformDistribution; break;
          case 1: source.distribution = Vtk.PointSource.ShellDistribution; break;
        }
      }
    }

    Utils.Slider {
      from: source;  bind: "numberOfPoints"

      min: 1000; max: 10000
      step: 100; value: 1000
    }

    Utils.CheckBox {
      from: root; bind: "useRandomSequence";
    }
  }
}

{% endhighlight %}

This time, we use an explicit `id` for our root object. We do this in order to access the `bool` value of the `useRandomSequence` property which will determine whether the [Vtk::MinimalStandardRandomSequence]({{ site.baseurl }}/api/Vtk/MinimalStandardRandomSequence) object or the default point generation algorithm should be used. This conditional assignment is performed by using the expression `randomSequence: root.useRandomSequence ? sequence : null;`. Depending on the value of `root.useRandomSequence`, we will assign either the `sequence` object or null. We also use the `CheckBox` component from the `Utils` module so that we can change the value of `useRandomSequence`.

## Calculating Stable Values
The default point generation method of [vtkPointSource](https://vtk.org/doc/nightly/html/classvtkPointSource.html) relies on [vtkMath](https://vtk.org/doc/nightly/html/classvtkMath.html) which is not ideal for random number generation. Since almost all methods from [vtkMath](https://vtk.org/doc/nightly/html/classvtkMath.html) are `static`, we will always generate different number values. This can be observed when changing the `numberOfPoints` (or any other property) of `PointSource`. You will notice that the actual points will always change. Even when changing the `center` property for example.

Random number generators usually provide a `seed` in order to generate consistent values. Individual seeds will generate specific number sequences. While this could be ensured by resetting the seed which is used in [vtkMath](https://vtk.org/doc/nightly/html/classvtkMath.html), this would cause unwanted side-effects since the seed is implemented as a `static` member variable in [vtkMath](https://vtk.org/doc/nightly/html/classvtkMath.html).

Therefore it is better to assign a specific [Vtk::RandomSequence]({{ site.baseurl }}/api/Vtk/RandomSequence) subclass to the `randomSequence` property. In order to generate consistent values, we have to re-initialize individual seed explicitly which we will discuss next. Let's start by adding a private `resetSeed` method to our `PointSource` implementation in the header.

>quickVtkPointSource.hpp
{: .hl-caption}

{% highlight cpp %}

#pragma once

#include "quickVtkPolyDataAlgorithm.hpp"
#include "quickVtkRandomSequence.hpp"
#include "quickMathVector3.hpp"

#include <vtkPointSource.h>

namespace quick {
  namespace Vtk {

    class PointSource : public PolyDataAlgorithm {
      Q_OBJECT
    public:
      enum Distribution {
          UniformDistribution = VTK_POINT_UNIFORM,
          ShellDistribution = VTK_POINT_SHELL
      };
    private:
      Q_ENUM(Distribution);
      Q_PROPERTY(quick::Math::Vector3* center READ getCenter CONSTANT);
      Q_PROPERTY(Distribution distribution READ getDistribution WRITE setDistribution NOTIFY distributionChanged);
      Q_PROPERTY(quick::Vtk::RandomSequence* randomSequence READ getRandomSequence WRITE setRandomSequence NOTIFY randomSequenceChanged);
      Q_PROPERTY(int numberOfPoints READ getNumberOfPoints WRITE setNumberOfPoints NOTIFY numberOfPointsChanged);
    private:
      static Qml::Register::Class<PointSource> Register;
      vtkSmartPointer<vtkPointSource> m_vtkObject;
      Math::Vector3* m_center;
      RandomSequence* m_randomSequence;
    private:
      auto resetSeed() -> void;
    public:
      PointSource();
      auto setDistribution(Distribution) -> void;
      auto getDistribution() -> Distribution;
      auto setNumberOfPoints(int) -> void;
      auto getNumberOfPoints() -> int;
      auto getCenter() -> Math::Vector3*;
      auto setRandomSequence(RandomSequence*) -> void;
      auto getRandomSequence() -> RandomSequence*;
    signals:
      void distributionChanged();
      void numberOfPointsChanged();
      void randomSequenceChanged();
    };
  }
}

{% endhighlight %}

We will implement `resetSeed()` in the **.cpp** file and call the method from every `set-` method. Note that this only makes sense if `m_randomSequence` points to a valid [Vtk::RandomSequence]({{ site.baseurl }}/api/Vtk/RandomSequence) instance. Let's take a look at how this is implemented.

>quickVtkPointSource.cpp
{: .hl-caption}

{% highlight cpp %}

#include "quickVtkPointSource.hpp"

namespace quick {

  namespace Vtk {

    Qml::Register::Class<PointSource> PointSource::Register(true);

    PointSource::PointSource() : PolyDataAlgorithm(vtkSmartPointer<vtkPointSource>::New()) {
      this->m_vtkObject = vtkPointSource::SafeDownCast(Algorithm::getVtkObject());

      this->m_center = new Math::Vector3([this](){
        this->m_vtkObject->SetCenter(this->m_center->getValues().data());
        this->resetSeed();
        this->update();
      });
    }

    auto PointSource::setNumberOfPoints(int numberOfPoints) -> void {
      this->m_vtkObject->SetNumberOfPoints(numberOfPoints);
      emit this->numberOfPointsChanged();
      this->resetSeed();
      this->update();
    }

    // getNumberOfPoints

    auto PointSource::setDistribution(Distribution distribution) -> void {
      this->m_vtkObject->SetDistribution(distribution);
      emit this->distributionChanged();
      this->resetSeed();
      this->update();
    }

    // getDistribution

    auto PointSource::setRandomSequence(RandomSequence* randomSequence) -> void {
      this->m_randomSequence = randomSequence;

      if (randomSequence == nullptr) {
        this->m_vtkObject->SetRandomSequence(nullptr);
      } else {
        this->m_vtkObject->SetRandomSequence(randomSequence->getVtkObject());
        randomSequence->initialize();
      }

      emit this->randomSequenceChanged();
      this->update();
    }

    auto PointSource::getRandomSequence() -> RandomSequence* {
      return this->m_randomSequence;
    }

    auto PointSource::resetSeed() -> void {
      if (this->m_randomSequence != nullptr) {
        this->m_randomSequence->initialize();
      }
    }
  }
}

{% endhighlight %}

This will reset the `seed` property of the referenced [Vtk::RandomSequence]({{ site.baseurl }}/api/Vtk/RandomSequence) object. You can see that points are placed in a consistent pattern as long as the same `seed` is used.

## Why no Lambda Expression?
If you compare this to the implementation of the [Math::Vector3]({{ site.baseurl }}/api/Math/Vector3) property, you will notice that we didn't have to use any callbacks. The reason for this is that we use a shared [vtkRandomSequence](https://vtk.org/doc/nightly/html/classvtkRandomSequence.html) object. By returning `m_vtkObject` when calling `getVtkObject()` on [Vtk::RandomSequence]({{ site.baseurl }}/api/Vtk/RandomSequence), we assign the same [vtkRandomSequence](https://vtk.org/doc/nightly/html/classvtkRandomSequence.html) to [vtkPointSource](https://vtk.org/doc/nightly/html/classvtkPointSource.html) via `SetRandomSequence()`. We can rely on [VTK](https://vtk.org/) and don't have to implement any callbacks to manually react to property changes.

## The Default Property
We can only assign [Vtk::RandomSequence]({{ site.baseurl }}/api/Vtk/RandomSequence) objects to the `randomSource` property by using an explicit `id`. We want to provide a more convenient way for this by using the object hierarchy in [QML](https://doc.qt.io/qt-5/qtqml-index.html). Our goal is to automatically assign a child component to the `randomSource` property like demonstrated in the following example.

>PointSource.qml
{: .hl-caption}

{% highlight qml %}

import QtQuick 2.9
import Vtk 1.0 as Vtk

Item {
  id: root;

  anchors.fill: parent

  Vtk.Viewer {
    anchors.fill: parent

    mouseEnabled: true;

    Vtk.Actor {
      Vtk.PolyDataMapper {
        Vtk.PointSource {
          numberOfPoints: 2000

          Vtk.MinimalStandardRandomSequence {
            seed: 128;
          }
        }
      }
    }
  }
}

{% endhighlight %}

With our current implementation, the [QML](https://doc.qt.io/qt-5/qtqml-index.html) runtime would report the following error: `Cannot assign object to list property 'input'`. The default behaviour for all [Vtk::Algorithm]({{ site.baseurl }}/api/Vtk/Algorithm)-derived classes is to connect child-components to the `input` property which is used to construct the visualization pipeline. Since [Vtk::MinimalStandardRandomSequence]({{ site.baseurl }}/api/Vtk/MinimalStandardRandomSequence) is no subclass of [Vtk::Algorithm]({{ site.baseurl }}/api/Vtk/Algorithm), we will override the default property of our `PointSource` type via the `Q_CLASSINFO` macro.

>quickVtkPointSource.hpp
{: .hl-caption}

{% highlight cpp %}

#pragma once

#include "quickVtkPolyDataAlgorithm.hpp"
#include "quickVtkRandomSequence.hpp"
#include "quickMathVector3.hpp"

#include <vtkPointSource.h>

namespace quick {
  namespace Vtk {

    class PointSource : public PolyDataAlgorithm {
      Q_OBJECT
    public:
      enum Distribution {
        UniformDistribution = VTK_POINT_UNIFORM,
        ShellDistribution = VTK_POINT_SHELL
      };
    private:
      Q_ENUM(Distribution);
      Q_PROPERTY(quick::Math::Vector3* center READ getCenter CONSTANT);
      Q_PROPERTY(Distribution distribution READ getDistribution WRITE setDistribution NOTIFY distributionChanged);
      Q_PROPERTY(quick::Vtk::RandomSequence* randomSequence READ getRandomSequence WRITE setRandomSequence NOTIFY randomSequenceChanged);
      Q_PROPERTY(int numberOfPoints READ getNumberOfPoints WRITE setNumberOfPoints NOTIFY numberOfPointsChanged);
      Q_CLASSINFO("DefaultProperty", "randomSequence");
    private:
      static Qml::Register::Class<PointSource> Register;
      vtkSmartPointer<vtkPointSource> m_vtkObject;
      Math::Vector3* m_center;
      RandomSequence* m_randomSequence;
    public:
      PointSource();
      auto setDistribution(Distribution) -> void;
      auto getDistribution() -> Distribution;
      auto setNumberOfPoints(int) -> void;
      auto getNumberOfPoints() -> int;
      auto getCenter() -> Math::Vector3*;
      auto setRandomSequence(RandomSequence*) -> void;
      auto getRandomSequence() -> RandomSequence*;
    signals:
      void distributionChanged();
      void numberOfPointsChanged();
      void randomSequenceChanged();
    };
  }
}

{% endhighlight %}

Note that [QML](https://doc.qt.io/qt-5/qtqml-index.html) ensures type-safety. If we try to assign an object that is no subclass of [Vtk::RandomSequence]({{ site.baseurl }}/api/Vtk/RandomSequence), we receive the following error: `Cannot assign object of tpye "<some incompatible type>" to property of type "quick::Vtk::RandomSequence*" as the former is neither the same as the latter nor a sub-class of it.`.

Using the `Q_CLASSINFO` macro only makes sense if the wrapper provides a single object property or a list of properties of the same types. This enables types to be nested and assign child-components automatically to a specific property.
