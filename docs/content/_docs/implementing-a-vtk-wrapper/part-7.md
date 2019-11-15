---
layout: subpage
nav: docs
title: Part 7 - Adding an Object Property
category: Implementing a VTK wrapper in QuickVtk
---

## Adding an Object Property
The [vtkPointSource](https://vtk.org/doc/nightly/html/classvtkPointSource.html) class uses a certain strategy for calculating individual points. If we don't want to use the default algorithm, we can provide an alternative point generator via the `SetRandomSequence` method. The method expects an object reference to a `vtkRandomSequence`-derived class. We will implement the `randomSequence` property in order to assign such objects to our `PointSource`.

Object type properties are a bit more complex to implement since we have to consider object lifetimes. If we are referencing objects and allow them to be assigned at runtime, we have to make sure that we also handle cases where objects might be uninitialized. We already used an object property for the `center` property which we implemented by using the [Math::Vector3]({{ site.baseurl }}/api/Math/Vector3) type. All properties that hold a reference to an object can be considered object properties. But in this case we will not use `CONSTANT` declaration to provide a read-only object. Instead of providing an existing object, we will implement the `randomSequence` property a bit differently.

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

>quickVtkPointSource.hpp
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

        // ...

        auto PointSource::setRandomSequence(RandomSequence* randomSequence) -> void {
            this->m_randomSequence = randomSequence;

            if (randomSequence == nullptr) {
                this->m_vtkObject->SetRandomSequence(nullptr);
            } else {
                this->m_vtkObject->SetRandomSequence(randomSequence->getVtkObject());
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

We don't have to initialize our `m_randomSequence` member variable since there is no [vtkRandomSequence](https://vtk.org/doc/nightly/html/classvtkRandomSequence.html) object assigned to [vtkPointSource](https://vtk.org/doc/nightly/html/classvtkPointSource.html). Instead, we provide the `setRandomSequence` method which is called every time we assign an object to the `randomSource` property in [QML](https://doc.qt.io/qt-5/qtqml-index.html). If the assigned object is a valid [Vtk::RandomSequence]({{ site.baseurl }}/api/Vtk/RandomSequence) instance, we can access the underlying [vtkRandomSequence](https://vtk.org/doc/nightly/html/classvtkRandomSequence.html) object by calling `getVtkObject()`. If the assigned value is a `nullptr`, we have to tell our [vtkPointSource](https://vtk.org/doc/nightly/html/classvtkPointSource.html) object to use the default point generator method. We can do this by passing a `nullptr` argument to the `SetRandomSequence` method.

We will always emit the `randomSequenceChanged` signal and update the visualization pipeline after assigning a new value to the `randomSource` property. It doesn't make a difference if the `randomSequence` argument is valid or `nullptr`. In both cases an update is necessary. The `get-` method simply returns the current `m_randomSequence` object which can be `nullptr` or an instance of any [vtkRandomSequence](https://vtk.org/doc/nightly/html/classvtkRandomSequence.html)-derived class.

You might be wondering, why we don't have to use lambda expressions like we did for our [Math::Vector3]({{ site.baseurl }}/api/Math/Vector3) property. We will take a look at this.

## Accessing the Object Property in QML
After successful compilation we can use our `randomSequence` property in [QML](https://doc.qt.io/qt-5/qtqml-index.html).
