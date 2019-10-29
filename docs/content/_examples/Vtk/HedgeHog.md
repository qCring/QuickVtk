---
layout: example
nav: examples
title: HedgeHog
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
                Vtk.LoopSubdivisionFilter {
                    Vtk.STLReader {
                        fileName: SampleData.meshes.suzanneSTL
                    }
                }
            }
        }

        Vtk.Actor {
            Vtk.PolyDataMapper {
                Vtk.HedgeHog {
                    id: filter;

                    Vtk.LoopSubdivisionFilter {
                        Vtk.PolyDataNormals {
                            splitting: false;

                            Vtk.STLReader {
                                fileName: SampleData.meshes.suzanneSTL
                            }
                        }
                    }
                }
            }
        }
    }

    Utils.View {
        title: "HedgeHog"

        Utils.ComboBox {
            label: "VectorMode";
            model: ["UseVector", "UseNormal"];
            currentIndex: 1;
            onIndexChanged: {
                switch (index) {
                case 0: filter.vectorMode = Vtk.HedgeHog.UseVector; break;
                case 1: filter.vectorMode = Vtk.HedgeHog.UseNormal; break;

                default: filter.vectorMode = Vtk.HedgeHog.UseVector;
                }
            }
        }

        Utils.Slider {
            from: filter; bind: "scaleFactor";
            min: 0.01; max: 1; step: 0.01; value: 0.2;
        }
    }
}

{% endhighlight %}
