import QtQuick 2.5
import QtQuick.Controls 1.5

import Vtk 1.0 as Vtk
import Math 1.0 as Math

/*  One Math.Vector is assigned to different Prop3D instances. The top slider
 *  controls the number of DiskSource objects at runtime, the bottom slider
 *  controls the x value of the single Math.Vector instance. All DiscSource
 *  objects dynamically bind to the vector and update properly when the vector
 *  changes.
 */

Item {
    id: root;

    anchors.fill: parent;

    Math.Vector {
        id: vec;

        x: slider.value / 100;
    }

    Grid {
        anchors.fill: parent;

        rows: 3;
        columns: 3;

        Repeater {
            model: slider2.value
            delegate: Vtk.Viewer {
                width: root.width / 3;
                height: root.height / 3;

                mouseEnabled: true;

                Vtk.Actor {
                    position: vec

                    Vtk.PolyDataMapper {
                        Vtk.DiskSource {

                        }
                    }
                }
            }
        }
    }

    Slider {
        id: slider2;

        anchors.left: parent.left;
        anchors.right: parent.right;
        anchors.bottom: slider.top;

        minimumValue: 1;
        maximumValue: 10;
        value: 1;
        stepSize: 1;
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
