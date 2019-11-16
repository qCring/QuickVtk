---
layout: subpage
nav: docs
title: Part 8 - Finalizing the PointSource Implementation
category: Implementing a VTK wrapper in QuickVtk
number: 8
---

## Other Properties
There are two more properties we haven't discussed yet. The first is the `radius` property which specifies the size of the `PointSource`. Since we covered simple types by implementing the `numberOfPoints` property in [Part 4 - Properties]({{ site.baseurl }}/docs/part-4), we don't have to go into too much detail. All simple types are implemented similarly. The [type conversion]({{ site.baseurl }}/reference/type-conversion.html) reference provides an overview of which type to use for properties.

Another [vtkPointSource](https://vtk.org/doc/nightly/html/classvtkPointSource.html) class attribute is  `OutputPointsPrecision` which lets you control whether `float` or `double` should be used for internal calculations. An equivalent attribute is provided by many types in [VTK](https://vtk.org/) and implementing a property for this might not be the best choice. For now, all wrappers in QuickVtk rely on the default floating-point precision and ingore the precision attribute. It might make more sense to control this from the build-configuration.

## Updating the API-Docs
The [API Reference]({{ site.baseurl }}/api) is generated from C++ via the **API-DOCS** target. A JSON file contains all type information like the list of properties, enums and methods provided by individual wrappers in QuickVtk. Also, an **.md** file is generated for each type in order to generate unique urls for the website. If wrappers are changed or new wrappers are added to QuickVtk, make sure to run the **API-Docs** target and commit the generated **.json** and **.md** files to keep the documentation in sync with the implementation.

## quickVtkPointSource.hpp

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
      Q_PROPERTY(qreal radius READ getRadius WRITE setRadius NOTIFY radiusChanged);
      Q_CLASSINFO("DefaultProperty", "randomSequence");
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
      auto setRadius(qreal) -> void;
      auto getRadius() -> qreal;
      auto getCenter() -> Math::Vector3*;
      auto setRandomSequence(RandomSequence*) -> void;
      auto getRandomSequence() -> RandomSequence*;
    signals:
      void randomSequenceChanged();
      void distributionChanged();
      void numberOfPointsChanged();
      void radiusChanged();
    };
  }
}

{% endhighlight %}


## quickVtkPointSource.cpp

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

    auto PointSource::setDistribution(Distribution distribution) -> void {
      this->m_vtkObject->SetDistribution(distribution);
      emit this->distributionChanged();
      this->resetSeed();
      this->update();
    }

    auto PointSource::getDistribution() -> Distribution {
      return static_cast<Distribution>(this->m_vtkObject->GetDistribution());
    }

    auto PointSource::setNumberOfPoints(int numberOfPoints) -> void {
      this->m_vtkObject->SetNumberOfPoints(numberOfPoints);
      emit this->numberOfPointsChanged();
      this->resetSeed();
      this->update();
    }

    auto PointSource::getNumberOfPoints() -> int {
      return this->m_vtkObject->GetNumberOfPoints();
    }

    auto PointSource::setRadius(qreal radius) -> void {
      this->m_vtkObject->SetRadius(radius);
      emit this->radiusChanged();
      this->resetSeed();
      this->update();
    }

    auto PointSource::getRadius() -> qreal {
      return this->m_vtkObject->GetRadius();
    }

    auto PointSource::getCenter() -> Math::Vector3* {
      return this->m_center;
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

    auto PointSource::resetSeed() -> void {
      if (this->m_randomSequence != nullptr) {
        this->m_randomSequence->initialize();
      }
    }
  }
}

{% endhighlight %}
