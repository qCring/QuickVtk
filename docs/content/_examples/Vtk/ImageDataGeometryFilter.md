---
layout: example
nav: examples
title: ImageDataGeometryFilter
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
                Vtk.ImageDataGeometryFilter {
                    id: filter;

                    Vtk.PNGReader {
                        fileName: SampleData.images.aPNG;
                    }
                }
            }
        }
    }
}

{% endhighlight %}
