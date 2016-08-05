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
                Vtk.ButterflySubdivisionFilter {
                    id: filter;
                    Vtk.STLReader {
                        fileName: SampleData.meshes.suzanneSTL;
                    }
                }
            }
        }
    }

    Utils.View {
        title: "ButterflySubdivisionFilter"

        Utils.Slider {
            from: filter; bind: "numberOfSubdivisions";
            min: 0; max: 4; step: 1; value: 0;
        }
    }
}
