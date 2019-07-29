import QtQuick 2.6

import Vtk 1.0 as Vtk
import Math 1.0 as Math

Item {
    id: root;
    
    anchors.fill: parent;

    property real cellWidth: width/2;
    property real cellHeight: height/2;
    
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

    Vtk.Viewer {
        input: sharedActor;

        width: root.cellWidth;
        height: root.cellHeight;

        mouseEnabled: true;
    }

    Vtk.Viewer {
        input: sharedActor;

        x: root.cellWidth;

        width: root.cellWidth;
        height: root.cellHeight;

        mouseEnabled: true;
    }

    Vtk.Viewer {
        input: sharedActor;

        y: root.cellHeight;
        
        width: root.cellWidth;
        height: root.cellHeight;

        mouseEnabled: true;
    }

    Vtk.Viewer {
        input: sharedActor;

        x: root.cellWidth;
        y: root.cellHeight;
        
        width: root.cellWidth;
        height: root.cellHeight;

        mouseEnabled: true;
    }
}