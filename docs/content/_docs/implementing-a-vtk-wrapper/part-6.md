---
layout: subpage
nav: docs
title: Part 6 - Adding an Enum Property
category: Implementing a VTK wrapper in QuickVtk
number: 6
---

## Adding an Enum Property
Next we are going to add an enum property to our `PointSource` implementation. While the  [documentation](https://vtk.org/doc/nightly/html/classvtkPointSource.html) states that the `Distribution` attribute uses an `int` type internally, only two values are really supported. Taking a closer look at the [implementation](https://vtk.org/doc/nightly/html/vtkPointSource_8h_source.html) reveals that the constant `VTK_POINT_UNIFORM` and `VTK_POINT_SHELL` definitions are used to control point distribution. It would be resonable to use a simple `int` property since we want to keep our `PointSource` wrapper as consistent as possible with the [VTK](https://vtk.org/) implementation. But an enum is obviously the better choice in this case.

It is not always possible to follow a strict guideline on how to implement properties. Sometimes it is the better choice to deliberately deviate from the [VTK](https://vtk.org/) implementation in order to provide a clean API. There are some indicators that can help to decide whether an enum is better suited for `int` properties. The `SetDistributionToUniform` and `SetDistributionToShell` methods of [vtkPointSource](https://vtk.org/doc/nightly/html/classvtkPointSource.html) tell us that the `Distriibution` attribute can only have one of two possible states. So let's go ahead and extend our `PointSource` implementation in order to expose a new enum property.

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
    public:
      enum Distribution {
          UniformDistribution = VTK_POINT_UNIFORM,
          ShellDistribution = VTK_POINT_SHELL
      };
    private:
      Q_ENUM(Distribution);
      Q_PROPERTY(quick::Math::Vector3* center READ getCenter CONSTANT);
      Q_PROPERTY(Distribution distribution READ getDistribution WRITE setDistribution NOTIFY distributionChanged);
      Q_PROPERTY(int numberOfPoints READ getNumberOfPoints WRITE setNumberOfPoints NOTIFY numberOfPointsChanged);
    private:
      static Qml::Register::Class<PointSource> Register;
      vtkSmartPointer<vtkPointSource> m_vtkObject;
      Math::Vector3* m_center;
    public:
      PointSource();
      auto setDistribution(Distribution) -> void;
      auto getDistribution() -> Distribution;
      auto setNumberOfPoints(int) -> void;
      auto getNumberOfPoints() -> int;
      auto getCenter() -> Math::Vector3*;
    signals:
      void distributionChanged();
      void numberOfPointsChanged();
    };
  }
}

{% endhighlight %}

We have to define our `enum` in a `public` block before we can use the type from the `Q_PROPERTY` declaration. Keep in mind that the `Q_OBJECT` macro has to be used before any class declarations in order to work correctly. We will assign the enum values directly from `VTK_POINT_UNIFORM` and `VTK_POINT_SHELL` so that we don't have to worry about changes in the [VTK](https://vtk.org/) implementation. For now, the values are `0` and `1` but this might change in the future.

Enum properties are declared just like regular properties. We use the `READ`, `WRITE`, and `NOTIFY` macros to connect the property accessors and the appropriate signal to the property. We also have to register the enum type explicitly via the `Q_ENUM` macro. Note that we are not using the typesafe `enum class` declaration. This allows us to forward our enum directly to the `SetDistribution` method provided by [vtkPointSource](https://vtk.org/doc/nightly/html/classvtkPointSource.html). Let's take a look at the implementation.

>quickVtkPointSource.cpp
{: .hl-caption}

{% highlight cpp %}
#include "quickVtkPointSource.hpp"

namespace quick {
  namespace Vtk {

    Qml::Register::Class<PointSource> PointSource::Register(true);

    auto PointSource::setDistribution(Distribution distribution) -> void {
      this->m_vtkObject->SetDistribution(distribution);
      emit this->distributionChanged();
      this->update();
    }

    auto PointSource::getDistribution() -> Distribution {
      return static_cast<Distribution>(this->m_vtkObject->GetDistribution());
    }

    // and more things that we already know
  }
}

{% endhighlight %}

Since we use a plain `enum` instead of an `enum class`, we can rely on  implicit conversion to `int` which is the expected argument type for `m_vtkObject->SetDistribution()`. We only have to explicitly convert the returned `int` from `m_vtkObject->GetDistribution()`. This should be always done via a `static_cast`. C-style casts (round brackets) are using a combination of explicit and implicit type conversions and can fail at runtime.

## Accessing the Enum Property in QML
As always, we will take a look at how to access our newly created property after rebuilding the project. We will use the `Utils` module to change the `distribution` property at runtime and see how this affects generated points.

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
          distribution: Vtk.PointSource.UniformDistribution
        }
      }
    }
  }

  Utils.View {
    Utils.Slider {
      from: source;  bind: "numberOfPoints"

      min: 1000; max: 50000
      step: 100; value: 1000
    }

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
  }
}

{% endhighlight %}

We can see how the `distribution` propery is accessed and also how individual enum values are retrieved via the `Vtk.PointSource` prefix. Keep in mind that enums are only available from where they are defined. While this can lead to lengthy identifiers in some cases, we maintain a clean API design. If a type provides an enum property, we know that all enum values are defined in the same type.

While there are some cases where the same enum type is used by different classes in [VTK](https://vtk.org/), we will always provide an individual enum for every class in QuickVtk even though this might add some redundant enum definitions.

The last thing to note is how the `ComboBox` component is used to change the value of the `distribution` property. The `model` property contains an array of strings which are used to label individual items. The `onIndexChanged` function is called after a new value is selected. Based on the new index we can assign a value to the `distribution` property.
