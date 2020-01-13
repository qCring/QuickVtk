import QtQuick 2.12

import Vtk 1.0 as Vtk
import Math 1.0 as Math
import Utils 1.0 as Utils

Item {
    id: root;

    anchors.fill: parent;

    property alias center: filter.center;
    property alias principalPoint: filter.principalPoint;

    Vtk.Viewer {
        anchors.fill: parent;

        mouseEnabled: true;

        Vtk.Actor {
            property.edgeVisibility: true;

            Vtk.PolyDataMapper {
                Vtk.WarpLens {
                    id: filter;

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
        title: "WarpLens"

        Utils.Slider {
            from: filter; bind: "k1";
            min: 0; max: 10; step: 0.01; value: 10;
        }

        Utils.Slider {
            from: filter; bind: "k2";
            min: 0; max: 0.001; step: 0.0001; value: 0.0003;
        }

        Utils.Slider {
            from: filter; bind: "p1";
            min: 0; max: 0.00002; step: 0.000001; value: 0.00001;
        }

        Utils.Slider {
            from: filter; bind: "p2";
            min: -0.00002; max: 0; step: 0.000001; value: -0.00001;
        }

        Utils.Slider {
            from: center; bind: "x"; label: "center.x";
            min: 0; max: 128; step: 0.1; value: 32;
        }

        Utils.Slider {
            from: center; bind: "y"; label: "center.y";
            min: 0; max: 128; step: 0.1; value: 32;
        }

        Utils.Slider {
            from: principalPoint; bind: "x"; label: "principalPoint.x";
            min: 0; max: 128; step: 0.1; value: 32;
        }

        Utils.Slider {
            from: principalPoint; bind: "y"; label: "principalPoint.y";
            min: 0; max: 128; step: 0.1; value: 32;
        }
    }
}
