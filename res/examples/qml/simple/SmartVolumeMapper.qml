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
            Vtk.SmartVolumeMapper {
                id: mapper;

                Vtk.DICOMImageReader {
                    directoryName: SampleData.volumes.brainDIR;
                }
            }
        }
    }

    Utils.View {
        title: "SmartVolumeMapper"

        Utils.Slider {
            from: mapper; bind: "finalColorWindow";
            min: 0; max: 10; step: 0.01; value: 1;
        }

        Utils.Slider {
            from: mapper; bind: "finalColorLevel";
            min: -5; max: 5; step: 0.01; value: 1;
        }
    }
}
