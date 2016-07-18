import QtQuick 2.6
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
            id: actor;

            Vtk.PolyDataMapper {
                Vtk.SphereSource {
                }
            }
        }
    }

    ComboBox {
        anchors.right: parent.right;
        anchors.top: parent.top;
        anchors.margins: 8;
        model: ["Points", "Wireframe", "Surface"];

        currentIndex: 2;

        onCurrentIndexChanged: {
            switch (currentIndex) {
            case 0: actor.property.representation = Vtk.Property.Points; break;
            case 1: actor.property.representation = Vtk.Property.Wireframe; break;
            case 2: actor.property.representation = Vtk.Property.Surface; break;

            default: actor.property.representation = Vtk.Property.Surface; break;
            }
        }
    }
}
