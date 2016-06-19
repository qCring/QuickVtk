import QtQuick 2.5
import QtQuick.Controls 1.5

import Vtk 1.0 as Vtk
import Math 1.0 as Math

Item {
    id: root;

    anchors.fill: parent;

    Vtk.SphereSource {
        id: sphereSource;

        radius: 5;
        thetaResolution: slider.value;
        phiResolution: 32;
    }

    Vtk.Viewer {
        anchors.fill: parent;

        mouseEnabled: true;

        Vtk.Actor {
            Vtk.PolyDataMapper {
                Vtk.SphereSource {
                    radius: 5;
                    thetaResolution: slider.value;
                    phiResolution: 32;
                }
            }
        }

        Vtk.Actor {
            Vtk.PolyDataMapper {
                Vtk.Glyph3D {
                    scaleMode: Vtk.Glyph3D.ScalingOff;
                    vectorMode: Vtk.Glyph3D.UseNormal;

                    Vtk.SphereSource {
                        radius: 5;
                        thetaResolution: slider.value;
                        phiResolution: 32;
                    }

                    Vtk.ArrowSource {

                    }
                }
            }
        }
    }

    Slider {
        id: slider;

        anchors.left: parent.left;
        anchors.right: parent.right;
        anchors.bottom: parent.bottom;

        minimumValue: 3;
        maximumValue: 10;
        value: 3;
    }
}
