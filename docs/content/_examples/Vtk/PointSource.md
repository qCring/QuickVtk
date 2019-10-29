---
layout: example
nav: examples
title: PointSource
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

    Vtk.Viewer {
        anchors.fill: parent;

        mouseEnabled: true;

        Vtk.Actor {
            Vtk.PolyDataMapper {
                Vtk.PointSource {
                    id: source;
                }
            }
        }
    }

    Utils.View {
        title: "PointSource"

        Utils.ComboBox {
            label: "Distribution";
            model: ["Uniform", "Shell"];
            onIndexChanged: {
                switch (index) {
                case 0: source.distribution = Vtk.PointSource.UniformDistribution; break;
                case 1: source.distribution = Vtk.PointSource.ShellDistribution; break;

                default: source.distribution = Vtk.PointSource.UniformDistribution; break;
                }
            }
        }

        Utils.Slider {
            from: source; bind: "numberOfPoints";
            min: 100; max: 10000; step: 1; value: 500;
        }

        Utils.Slider {
            from: source; bind: "radius";
            min: 0.5; max: 2; step: 0.01; value: 1;
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
    }
}

{% endhighlight %}
