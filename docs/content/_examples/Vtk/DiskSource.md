---
layout: example
nav: examples
title: DiskSource
category: Vtk
---
{% highlight qml %}

import QtQuick 2.6

import Vtk 1.0 as Vtk
import Math 1.0 as Math
import Utils 1.0 as Utils

Item {
    id: root;

    anchors.fill: parent;

    Vtk.Viewer {
        anchors.fill: parent;

        mouseEnabled: true;

        Vtk.Actor {
            Vtk.PolyDataMapper {
                Vtk.DiskSource {
                    id: source;
                }
            }
        }
    }

    Utils.View {
        title: "DiskSource"

        Utils.Slider {
            from: source; bind: "innerRadius";
            min: 0.1; max: 0.5; step: 0.01; value: 0.25;
        }

        Utils.Slider {
            from: source; bind: "outerRadius";
            min: 0.6; max: 1; step: 0.01; value: 0.6;
        }

        Utils.Slider {
            from: source; bind: "radialResolution";
            min: 3; max: 64; step: 1; value: 16;
        }

        Utils.Slider {
            from: source; bind: "circumferentialResolution";
            min: 3; max: 64; step: 1; value: 16;
        }
    }
}

{% endhighlight %}
