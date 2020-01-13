import QtQuick 2.12

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
            property.edgeVisibility: true;

            Vtk.PolyDataMapper {
                Vtk.AdaptiveSubdivisionFilter {
                    id: filter;

                    Vtk.TriangleFilter {
                        Vtk.STLReader {
                            fileName: SampleData.meshes.suzanneSTL;
                        }
                    }
                }
            }
        }
    }

    Utils.View {
        title: "AdaptiveSubdivisionFilter"

        Utils.Slider {
            from: filter; bind: "maximumEdgeLength";
            min: 0.1; max: 1; step: 0.1; value: 1;
        }

        Utils.Slider {
            from: filter; bind: "maximumTriangleArea";
            min: 0.01; max: 1; step: 0.1; value: 1;
        }

        Utils.Slider {
            from: filter; bind: "maximumNumberOfTriangles";
            min: 1; max: 1000; step: 1; value: 1000;
        }

        Utils.Slider {
            from: filter; bind: "maximumNumberOfPasses";
            min: 1; max: 1000; step: 1; value: 1000;
        }
    }
}
