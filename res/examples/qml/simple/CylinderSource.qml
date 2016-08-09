import QtQuick 2.6

import Vtk 1.0 as Vtk
import Math 1.0 as Math
import Utils 1.0 as Utils

Item {
    id: root;

    anchors.fill: parent;

    property alias center: source.center;

    Vtk.Viewer {
        anchors.fill: parent;

        mouseEnabled: true;

        Vtk.Actor {
            Vtk.PolyDataMapper {
                Vtk.CylinderSource {
                    id: source;
                }
            }
        }
    }

    Utils.View {
        title: "CylinderSource"

        Utils.Slider {
            from: source; bind: "height";
            min: 0.1; max: 2; step: 0.01; value: 2;
        }

        Utils.Slider {
            from: source; bind: "radius";
            min: 0.1; max: 0.5; step: 0.01; value: 0.5;
        }

        Utils.Slider {
            from: source; bind: "resolution";
            min: 3; max: 64; step: 1; value: 16;
        }

        Utils.CheckBox {
            from: source; bind: "capping";
        }

        Utils.Slider {
            from: center; bind: "x"; label: "center.x";
        }

        Utils.Slider {
            from: center; bind: "y"; label: "center.y";
        }

        Utils.Slider {
            from: center; bind: "z"; label: "center.z";
            min: -1; max: 0; step: 0.01; value: 0;
        }
    }
}
