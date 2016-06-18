import QtQuick 2.5
import QtQuick.Controls 1.5

import Vtk 1.0 as Vtk
import Math 1.0 as Math

Item {
    id: root;

    anchors.fill: parent;

    Vtk.Viewer {
        anchors.fill: parent;

        mouseEnabled: true;

        Vtk.Actor {
            property.representation: Vtk.Property.Points;

            Vtk.PolyDataMapper {
                Vtk.SphereSource {
                }
            }
        }
    }
}
