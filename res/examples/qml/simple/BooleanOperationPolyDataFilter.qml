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
                Vtk.BooleanOperationPolyDataFilter {
                    id: filter;

                    Vtk.STLReader {
                        fileName: SampleData.meshes.bSTL;
                    }

                    Vtk.STLReader {
                        fileName: SampleData.meshes.suzanneSTL;
                    }
                }
            }
        }
    }

    Utils.View {
        title: "BooleanOperationPolyDataFilter"

        Utils.ComboBox {
            label: "operation";
            model: ["Union", "Intersection", "Difference"];
            onIndexChanged: {
                switch (index) {
                case 0: filter.operation = Vtk.BooleanOperationPolyDataFilter.Union; break;
                case 1: filter.operation = Vtk.BooleanOperationPolyDataFilter.Intersection; break;
                case 2: filter.operation = Vtk.BooleanOperationPolyDataFilter.Difference; break;

                default: filter.operation = Vtk.BooleanOperationPolyDataFilter.Union;
                }
            }
        }

        Utils.CheckBox {
            from: filter; bind: "reorientDifferentCells";
        }
    }
}
