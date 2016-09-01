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

            Vtk.GPUVolumeRayCastMapper {
                id: mapper;

                Vtk.DICOMImageReader {
                    directoryName: SampleData.volumes.brain2DIR;
                }
            }
        }
    }

    Utils.View {
        title: "GPUVolumeRayCastMapper";

        Utils.CheckBox {
            from: volume.property; bind: "shade";
        }

        Utils.CheckBox {
            from: mapper; bind: "autoAdjustSampleDistances";
        }

        Utils.CheckBox {
            from: mapper; bind: "useJittering";
        }

        Utils.CheckBox {
            from: mapper; bind: "useDepthPass";
        }

        Utils.Slider {
            from: mapper; bind: "sampleDistance";
            min: 0.5; max: 20; step: 0.5; value: 2;
        }

        Utils.Slider {
            from: mapper; bind: "finalColorWindow";
            min: 0.01; max: 1; step: 0.01; value: 1;
        }

        Utils.Slider {
            from: mapper; bind: "finalColorLevel";
            min: 0.01; max: 1; step: 0.01; value: 0.5;
        }
    }

    Component.onCompleted: {
        volume.property.scalarOpacityFunction.add(0, 0);
        volume.property.scalarOpacityFunction.add(120, 0.02);
        volume.property.scalarOpacityFunction.add(140, 0.02);
        volume.property.scalarOpacityFunction.add(500, 0);

        volume.property.transferFunction.add("#00ff00",   0);
        volume.property.transferFunction.add("#ff0000", 100);
        volume.property.transferFunction.add("#0000ff", 500);
    }
}
