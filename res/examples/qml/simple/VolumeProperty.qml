import QtQuick 2.6

import Vtk 1.0 as Vtk
import Math 1.0 as Math
import Utils 1.0 as Utils

Rectangle {
    id: root;

    anchors.fill: parent;

    Vtk.Viewer {
        anchors.fill: parent;

        mouseEnabled: true;

        Vtk.Volume {
            id: volume;

            Vtk.SmartVolumeMapper {
                Vtk.DICOMImageReader {
                    directoryName: SampleData.volumes.brain2DIR;
                }
            }
        }
    }

    Utils.View {
        title: "VolumeProperty"
    }

    Component.onCompleted: {
        volume.property.scalarOpacity.x[0] = 0;
        volume.property.scalarOpacity.y[0] = 0;
        volume.property.scalarOpacity.x[1] = 200;
        volume.property.scalarOpacity.y[1] = 0;
        volume.property.scalarOpacity.x[2] = 500;
        volume.property.scalarOpacity.y[2] = 1;

        volume.property.color.x[0] = 0;
        volume.property.color.x[1] = 200;
        volume.property.color.x[2] = 500;

        volume.property.color.colors[0] = "#000";
        volume.property.color.colors[1] = "#ff0000";
        volume.property.color.colors[2] = "#0000ff";
    }
}
