import QtQuick 2.6
import QtQuick.Layouts 1.12

import Vtk 1.0 as Vtk
import Math 1.0 as Math

Item {
    id: root;
    
    anchors.fill: parent;
    
    Vtk.Actor {
        id: sharedActor;

        Vtk.PolyDataMapper {
            Vtk.LoopSubdivisionFilter {
                id: filter;
                Vtk.STLReader {
                    fileName: SampleData.meshes.suzanneSTL;
                }
            }
        }
    }

    GridLayout {
        anchors.fill: parent;
        columns: 2;

        Vtk.Viewer {
            input: sharedActor;
            Layout.fillWidth: true;
            Layout.fillHeight: true;
            mouseEnabled: true;
        }

        Vtk.Viewer {
            input: sharedActor;
            Layout.fillWidth: true;
            Layout.fillHeight: true;
            mouseEnabled: true;
        }

        Vtk.Viewer {
            input: sharedActor;
            Layout.fillWidth: true;
            Layout.fillHeight: true;
            mouseEnabled: true;
        }

        Vtk.Viewer {
            input: sharedActor;
            Layout.fillWidth: true;
            Layout.fillHeight: true;
            mouseEnabled: true;
        }
    }
}