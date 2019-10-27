---
layout: page
nav: examples
title: Prop3D
---

>Prop3D.qml
{: .hl-caption}

{% highlight qml %}

import QtQuick 2.6

import Vtk 1.0 as Vtk
import Math 1.0 as Math
import Utils 1.0 as Utils

Item {
    id: root;

    anchors.fill: parent;

    property alias propPos: prop.position;
    property alias propScale: prop.scale;
    property alias propOrientation: prop.orientation;

    Vtk.Viewer {
        anchors.fill: parent;

        mouseEnabled: true;

        Vtk.Actor {
            id: prop;

            Vtk.PolyDataMapper {
                Vtk.PolyDataNormals {
                    Vtk.OBJReader {
                        fileName: SampleData.meshes.suzanneOBJ
                    }
                }
            }
        }
    }

    Utils.View {
        title: "Prop3D"

        Utils.Slider {
            from: propPos; bind: "x"; label: "position.x";
        }

        Utils.Slider {
            from: propPos; bind: "y"; label: "position.y";
        }

        Utils.Slider {
            from: propPos; bind: "z"; label: "position.z";
            min: -1; max: 0; step: 0.01; value: 0;
        }

        Utils.Slider {
            from: propScale; bind: "x"; label: "scale.x"; min: 0.01; max: 2; value: 1;
        }

        Utils.Slider {
            from: propScale; bind: "y"; label: "scale.y"; min: 0.01; max: 2; value: 1;
        }

        Utils.Slider {
            from: propScale; bind: "z"; label: "scale.z"; min: 0.01; max: 2; value: 1;
        }

        Utils.Slider {
            from: propOrientation; bind: "x"; label: "orientation.x"; min: 0; max: 360; value: 0;
        }

        Utils.Slider {
            from: propOrientation; bind: "y"; label: "orientation.y"; min: 0; max: 360; value: 0;
        }

        Utils.Slider {
            from: propOrientation; bind: "z"; label: "orientation.z"; min: 0; max: 360; value: 0;
        }
    }
}

{% endhighlight %}
