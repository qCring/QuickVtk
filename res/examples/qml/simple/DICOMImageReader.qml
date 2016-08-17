import QtQuick 2.6

import Vtk 1.0 as Vtk
import Math 1.0 as Math

Item {
    id: root;

    anchors.fill: parent;

    Vtk.Viewer {
        anchors.fill: parent;

        mouseEnabled: true;

        Vtk.Volume {
            Vtk.SmartVolumeMapper {
                Vtk.DICOMImageReader {
                    directoryName: SampleData.volumes.brain1DIR;
                }
            }
        }
    }
}
