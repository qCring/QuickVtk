import QtQuick 2.6

import Vtk 1.0 as Vtk
import Math 1.0 as Math
import Utils 1.0 as Utils

Item {
    id: root;

    anchors.fill: parent;

    property alias extrusionPoint: filter.extrusionPoint;
    property alias vector: filter.vector;

    Vtk.Viewer {
        anchors.fill: parent;

        mouseEnabled: true;

        Vtk.Actor {
            Vtk.PolyDataMapper {
                Vtk.LinearExtrusionFilter {
                    id: filter;

                    Vtk.DiskSource {
                    }
                }
            }
        }
    }

    Utils.View {
        title: "LinearExtrusionFilter"

        Utils.ComboBox {
            label: "Type";
            model: ["Vector", "Normal", "Point"];
            onIndexChanged: {
                switch (index) {
                case 0: filter.extrusionType = Vtk.LinearExtrusionFilter.VectorExtrusion; break;
                case 1: filter.extrusionType = Vtk.LinearExtrusionFilter.NormalExtrusion; break;
                case 2: filter.extrusionType = Vtk.LinearExtrusionFilter.PointExtrusion; break;

                default: filter.extrusionType = Vtk.LinearExtrusionFilter.VectorExtrusion;
                }
            }
        }

        Utils.Slider {
            from: filter; bind: "scaleFactor";
            min: 0; max: 1; step: 0.01; value: 0.5;
        }

        Utils.Slider {
            from: extrusionPoint; bind: "x"; label: "point.x";
            min: -1; max: 1; step: 0.01; value: 0;
        }

        Utils.Slider {
            from: extrusionPoint; bind: "y"; label: "point.y";
            min: -1; max: 1; step: 0.01; value: 0;
        }

        Utils.Slider {
            from: extrusionPoint; bind: "z"; label: "point.z";
            min: -1; max: 1; step: 0.01; value: 0;
        }

        Utils.Slider {
            from: vector; bind: "x"; label: "vector.x";
            min: -1; max: 1; step: 0.01; value: 0;
        }

        Utils.Slider {
            from: vector; bind: "y"; label: "vector.y";
            min: -1; max: 1; step: 0.01; value: 0;
        }

        Utils.Slider {
            from: vector; bind: "z"; label: "vector.z";
            min: -1; max: 1; step: 0.01; value: 0;
        }
    }
}
