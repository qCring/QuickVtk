import QtQuick 2.12

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
            id: actor;

            Vtk.PolyDataMapper {
                Vtk.VertexGlyphFilter {
                    Vtk.OFFReader {
                        fileName: SampleData.meshes.teapotOFF
                    }
                }
            }
        }
    }

    Utils.View {
        title: "Property"

        Utils.Slider {
            from: actor.property; bind: "opacity";
            min: 0; max: 1; step: 0.01; value: 1;
        }

        Utils.Slider {
            from: actor.property; bind: "pointSize";
            min: 1; max: 15; step: 0.1; value: 2;
        }

        Utils.Slider {
            from: actor.property; bind: "ambient";
            min: 0; max: 1; step: 0.01; value: 0.1;
        }

        Utils.Slider {
            from: actor.property; bind: "diffuse";
            min: 0; max: 1; step: 0.01; value: 0.75;
        }

        Utils.ColorPicker {
            from: actor.property; bind: "ambientColor"; color: "#fff"
        }

        Utils.ColorPicker {
            from: actor.property; bind: "diffuseColor"; color: "#fff"
        }
    }
}
