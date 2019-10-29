---
layout: example
nav: examples
title: RotationalExtrusionFilter
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
                Vtk.RotationalExtrusionFilter {
                    id: filter;
                    Vtk.PointSource {
                        numberOfPoints: 50
                    }
                }
            }
        }
    }

    Utils.View {
        title: "RotationalExtrusionFilter"

        Utils.Slider {
            from: filter; bind: "resolution";
            min: 2; max: 64; step: 1; value: 16;
        }

        Utils.Slider {
            from: filter; bind: "angle";
            min: 0; max: 720; step: 1; value: 130;
        }

        Utils.Slider {
            from: filter; bind: "translation";
            min: 0; max: 2; step: 0.01; value: 0.5;
        }

        Utils.Slider {
            from: filter; bind: "deltaRadius";
            min: 0; max: 1; step: 0.001; value: 0;
        }

        Utils.CheckBox {
            from: filter; bind: "capping";
        }
    }
}

{% endhighlight %}
