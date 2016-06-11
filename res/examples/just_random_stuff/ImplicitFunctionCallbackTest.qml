import QtQuick 2.5
import QtQuick.Controls 1.5

import Vtk 1.0 as Vtk
import Math 1.0 as Math

Item {
    id: root;

    anchors.fill: parent;


    Vtk.PerlinNoise {
        id: cutFunc;

        amplitude: 1

        frequency.x: slider.value;
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
                    Vtk.PolyDataMapper {
                        Vtk.Cutter {
                            cutFunction: cutFunc;

                            Vtk.SphereSource {
                            }
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
        value: 3;
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
