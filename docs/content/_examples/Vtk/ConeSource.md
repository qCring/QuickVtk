---
layout: example
nav: examples
title: ConeSource
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

    property alias center: source.center;
    property alias direction: source.direction;

    Vtk.Viewer {
        anchors.fill: parent;

        mouseEnabled: true;

        Vtk.Actor {
            Vtk.PolyDataMapper {
                Vtk.ConeSource {
                    id: source;
                }
            }
        }
    }

    Utils.View {
        title: "ConeSource"

        Utils.Slider {
            from: source; bind: "height";
            min: 0.1; max: 2; step: 0.01; value: 2;
        }

        Utils.Slider {
            from: source; bind: "radius";
            min: 0.1; max: 1; step: 0.01; value: 1;
        }

        Utils.Slider {
            from: source; bind: "resolution";
            min: 3; max: 64; step: 1; value: 16;
        }

        Utils.Slider {
            from: source; bind: "angle";
            min: 30; max: 45; step: 1; value: 30;
        }

        Utils.CheckBox {
            from: source; bind: "capping";
        }

        Utils.Slider {
            from: center; bind: "x"; label: "center.x";
        }

        Utils.Slider {
            from: center; bind: "y"; label: "center.y";
        }

        Utils.Slider {
            from: center; bind: "z"; label: "center.z";
            min: -1; max: 0; step: 0.01; value: 0;
        }

        Utils.Slider {
            from: direction; bind: "x"; label: "direction.x"; min: -1; max: 1; value: 1;
        }

        Utils.Slider {
            from: direction; bind: "y"; label: "direction.y"; min: -1; max: 1; value: 1;
        }

        Utils.Slider {
            from: direction; bind: "z"; label: "direction.z"; min: -1; max: 1; value: 1;
        }
    }
}

{% endhighlight %}
