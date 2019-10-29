---
layout: example
nav: examples
title: PlatonicSolidSource
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
                Vtk.PlatonicSolidSource {
                    id: source;
                }
            }
        }
    }

    Utils.View {
        title: "PlatonicSolidSource"

        Utils.ComboBox {
            label: "solidType";
            model: ["Tetrahedron", "Cube", "Octahedron", "Icosahedron", "Dodecahedron"];
            onIndexChanged: {
                switch (index) {
                case 0: source.solidType = Vtk.PlatonicSolidSource.SolidTetrahedron; break;
                case 1: source.solidType = Vtk.PlatonicSolidSource.SolidCube; break;
                case 2: source.solidType = Vtk.PlatonicSolidSource.SolidOctahedron; break;
                case 3: source.solidType = Vtk.PlatonicSolidSource.SolidIcosahedron; break;
                case 4: source.solidType = Vtk.PlatonicSolidSource.SolidDodecahedron; break;

                default: source.solidType = Vtk.PlatonicSolidSource.SolidTetrahedron;
                }
            }
        }
    }
}

{% endhighlight %}
