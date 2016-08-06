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
                Vtk.SphereSource {
                    id: source;
                }
            }
        }
    }

    Utils.View {
        title: "SphereSource"

        Utils.Slider {
            from: source; bind: "radius";
            min: 0.1; max: 1; step: 0.01; value: 0.5;
        }

        Utils.Slider {
            from: source; bind: "startTheta";
            min: 0; max: 90; step: 1; value: 0;
        }

        Utils.Slider {
            from: source; bind: "endTheta";
            min: 180; max: 360; step: 1; value: 360;
        }

        Utils.Slider {
            from: source; bind: "startPhi";
            min: 0; max: 90; step: 1; value: 0;
        }

        Utils.Slider {
            from: source; bind: "endPhi";
            min: 90; max: 180; step: 1; value: 180;
        }

        Utils.Slider {
            from: source; bind: "thetaResolution";
            min: 3; max: 64; step: 1; value: 16;
        }

        Utils.Slider {
            from: source; bind: "phiResolution";
            min: 3; max: 64; step: 1; value: 16;
        }

        Utils.CheckBox {
            from: source; bind: "latLongTessellation";
        }
    }
}
