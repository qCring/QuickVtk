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
            id: actor;

            Vtk.PolyDataMapper {
                Vtk.LoopSubdivisionFilter {
                    Vtk.PolyDataNormals {
                        splitting: false;

                        Vtk.STLReader {
                            fileName: SampleData.meshes.suzanneSTL
                        }
                    }
                }
            }
        }
    }

    Utils.View {
        title: "Property"

        Utils.ComboBox {
            label: "representation";
            model: ["Points", "Wireframe", "Surface"];
            currentIndex: 2;
            onIndexChanged: {
                switch (index) {
                case 0: actor.property.representation = Vtk.Property.Points; break;
                case 1: actor.property.representation = Vtk.Property.Wireframe; break;
                case 2: actor.property.representation = Vtk.Property.Surface; break;

                default: actor.property.interpolation = Vtk.Property.Surface; break;
                }
            }
        }

        Utils.ComboBox {
            label: "interpolation";
            model: ["Flat", "Gouraud", "Phong"];
            onIndexChanged: {
                switch (index) {
                case 0: actor.property.interpolation = Vtk.Property.Flat; break;
                case 1: actor.property.interpolation = Vtk.Property.Gouraud; break;
                case 2: actor.property.interpolation = Vtk.Property.Phong; break;

                default: actor.property.interpolation = Vtk.Property.Flat; break;
                }
            }
        }

        Utils.Slider {
            from: actor.property; bind: "opacity";
            min: 0; max: 1; step: 0.01; value: 1;
        }

        Utils.Slider {
            from: actor.property; bind: "lineWidth";
            min: 1; max: 15; step: 0.1; value: 1;
        }

        Utils.Slider {
            from: actor.property; bind: "pointSize";
            min: 1; max: 15; step: 0.1; value: 1;
        }

        Utils.CheckBox {
            from: actor.property; bind: "shading";
        }

        Utils.CheckBox {
            from: actor.property; bind: "lighting";
        }

        Utils.CheckBox {
            from: actor.property; bind: "edgeVisibility";
        }

        Utils.CheckBox {
            from: actor.property; bind: "backfaceCulling";
        }

        Utils.CheckBox {
            from: actor.property; bind: "frontfaceCulling";
        }

        Utils.Slider {
            from: actor.property; bind: "ambient";
            min: 0; max: 1; step: 0.01; value: 0.1;
        }

        Utils.Slider {
            from: actor.property; bind: "diffuse";
            min: 0; max: 1; step: 0.01; value: 0.75;
        }

        Utils.Slider {
            from: actor.property; bind: "specular";
            min: 0; max: 1; step: 0.01; value: 0.25;
        }

        Utils.Slider {
            from: actor.property; bind: "specularPower";
            min: 0; max: 100; step: 1; value: 50;
        }

        Utils.ColorPicker {
            from: actor.property; bind: "ambientColor"; color: "#fff"
        }

        Utils.ColorPicker {
            from: actor.property; bind: "diffuseColor"; color: "#fff"
        }

        Utils.ColorPicker {
            from: actor.property; bind: "specularColor"; color: "#fff"
        }
    }
}
