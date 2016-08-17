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
        title: "VolumeProperty";

        Utils.CheckBox {
            from: volume.property; bind: "shade";
        }
    }

    Component.onCompleted: {
        volume.property.scalarOpacityFunction.add(0, 0);
        volume.property.scalarOpacityFunction.add(120, 0);
        volume.property.scalarOpacityFunction.add(140, 0.08);
        volume.property.scalarOpacityFunction.add(500, 0);

        volume.property.transferFunction.add("#00ff00",   0);
        volume.property.transferFunction.add("#ff0000", 100);
        volume.property.transferFunction.add("#0000ff", 500);
    }
}
