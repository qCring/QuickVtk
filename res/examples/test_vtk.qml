import QtQuick 2.5

import Vtk 1.0

Item {
    anchors.fill: parent;

    Viewer
    {
        anchors.fill: parent;
        mouseEnabled: true;

        Actor {
            PolyDataMapper {
                DiskSource {
                }
            }
        }
    }
}
