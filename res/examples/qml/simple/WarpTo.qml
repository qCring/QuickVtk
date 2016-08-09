import QtQuick 2.6

import Vtk 1.0 as Vtk
import Math 1.0 as Math
import Utils 1.0 as Utils

Item {
    id: root;

    anchors.fill: parent;

    property alias position: filter.position;

    Vtk.Viewer {
        anchors.fill: parent;

        mouseEnabled: true;

        Vtk.Actor {
            property.edgeVisibility: true;

            Vtk.PolyDataMapper {
                Vtk.WarpTo {
                    id: filter;

                    absolute: true;

                    Vtk.ImageDataGeometryFilter {
                        Vtk.PNGReader {
                            fileName: SampleData.images.aPNG;
                        }
                    }
                }
            }
        }
    }

    Utils.View {
        title: "WarpTo"

        Utils.Slider {
            from: filter; bind: "scaleFactor";
            min: 0.9; max: 1; step: 0.01; value: 0.9;
        }

        Utils.Slider {
            from: position; bind: "x"; label: "position.x";
            min: 0; max: 32; step: 0.1; value: 32;
        }

        Utils.Slider {
            from: position; bind: "y"; label: "position.y";
            min: 0; max: 32; step: 0.1; value: 32;
        }

        Utils.Slider {
            from: position; bind: "z"; label: "position.z";
            min: 0; max: 10; step: 0.1; value: 10;
        }

        Utils.CheckBox {
            from: filter; bind: "absolute";
        }
    }
}
