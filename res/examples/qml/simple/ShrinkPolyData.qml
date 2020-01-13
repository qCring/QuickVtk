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
            Vtk.PolyDataMapper {
                Vtk.ShrinkPolyData {
                    id: filter;

                    Vtk.STLReader {
                        fileName: SampleData.meshes.suzanneSTL;
                    }
                }
            }
        }
    }

    Utils.View {
        title: "ShrinkPolyData"

        Utils.Slider {
            from: filter; bind: "shrinkFactor";
            min: 0; max: 1; step: 0.01; value: 1;
        }
    }
}
