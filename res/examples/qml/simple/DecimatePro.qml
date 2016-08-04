import QtQuick 2.6
import QtQuick.Controls 1.5

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
                Vtk.DecimatePro {
                    id: filter;

                    Vtk.STLReader {
                        fileName: SampleData.meshes.suzanne;
                    }
                }
            }
        }
    }

    Utils.View {
        title: "DecimatePro"

        Utils.Slider {
            from: filter; bind: "splitAngle";
            min: 0; max: 180; step: 1; value: 75
        }

        Utils.Slider {
            from: filter; bind: "featureAngle";
            min: 0; max: 180; step: 1; value: 15
        }

        Utils.Slider {
            from: filter; bind: "targetReduction";
            min: 0; max: 1; step: 0.01; value: 0.9
        }

        Utils.Slider {
            from: filter; bind: "degree";
            min: 0; max: 360; step: 1; value: 25
        }

        Utils.CheckBox {
            from: filter; bind: "preserveTopology";
        }

        Utils.CheckBox {
            from: filter; bind: "splitting";
        }

        Utils.CheckBox {
            from: filter; bind: "preSplitMesh";
        }
    }
}
