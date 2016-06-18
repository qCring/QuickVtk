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
            Vtk.PolyDataMapper {
                Vtk.Glyph3D {
                    scaleMode: Vtk.Glyph3D.ScaleOff;

                    Vtk.SphereSource {
                    }

                    Vtk.ArrowSource {

                    }
                }
            }
        }
    }

    Slider {
        id: slider;

        anchors.left: parent.left;
        anchors.right: parent.right;
        anchors.bottom: parent.bottom;

        minimumValue: 1;
        maximumValue: 100;
        value: 1;
    }
}
