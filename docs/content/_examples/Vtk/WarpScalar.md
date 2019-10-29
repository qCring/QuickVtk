---
layout: example
nav: examples
title: WarpScalar
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
            property.edgeVisibility: true;

            Vtk.PolyDataMapper {
                Vtk.WarpScalar {
                    id: filter;

                    Vtk.ImageDataGeometryFilter {
                        Vtk.PNGReader {
                            fileName: SampleData.images.aPNG;
                        }
                    }
                }
            }
        }
    }

    Utils.View {
        title: "WarpScalar"

        Utils.Slider {
            from: filter; bind: "scaleFactor";
            min: 0; max: 0.25; step: 0.1; value: 0.25;
        }
    }
}

{% endhighlight %}
