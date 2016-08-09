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
            property.interpolation: Vtk.Property.Phong

            Vtk.PolyDataMapper {
                Vtk.PolyDataNormals {
                    id: filter;

                    Vtk.STLReader {
                        fileName: SampleData.meshes.suzanneSTL
                    }
                }
            }
        }
    }

    Utils.View {
        title: "Property"

        Utils.Slider {
            from: filter; bind: "featureAngle";
            min: 0; max: 180; step: 1; value: 15
        }

        Utils.CheckBox {
            from: filter; bind: "splitting";
        }

        Utils.CheckBox {
            from: filter; bind: "consistency";
        }

        Utils.CheckBox {
            from: filter; bind: "autoOrientNormals";
        }

        Utils.CheckBox {
            from: filter; bind: "computePointNormals";
        }

        Utils.CheckBox {
            from: filter; bind: "computeCellNormals";
        }

        Utils.CheckBox {
            from: filter; bind: "flipNormals";
        }

        Utils.CheckBox {
            from: filter; bind: "nonManifoldTraversal"
        }
    }
}
