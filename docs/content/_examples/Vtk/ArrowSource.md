---
layout: example
nav: examples
title: ArrowSource
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
                Vtk.ArrowSource {
                    id: source;
                }
            }
        }
    }

    Utils.View {
        title: "ArrowSource"

        Utils.Slider {
            from: source; bind: "tipResolution";
            min: 1; max: 10; step: 1; value: 1;
        }

        Utils.Slider {
            from: source; bind: "tipLength";
            min: 0.1; max: 1; step: 0.01; value: 0.3;
        }

        Utils.Slider {
            from: source; bind: "tipRadius";
            min: 0.01; max: 0.5; step: 0.01; value: 0.2;
        }

        Utils.Slider {
            from: source; bind: "shaftResolution";
            min: 1; max: 10; step: 1; value: 1;
        }

        Utils.Slider {
            from: source; bind: "shaftRadius";
            min: 0.01; max: 0.5; step: 0.01; value: 0.05;
        }

        Utils.CheckBox {
            from: source; bind: "invert";
        }
    }
}

{% endhighlight %}
