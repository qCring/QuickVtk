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

        Vtk.Volume {
            Vtk.SmartVolumeMapper {
                id: mapper;

                Vtk.DICOMImageReader {
                    directoryName: SampleData.volumes.brain1DIR;
                }
            }
        }
    }

    Utils.View {
        title: "VolumeMapper"

        Utils.ComboBox {
            label: "blendMode";
            model: ["Composite", "MaximumIntensity", "MinimumIntensity", "Additive"];
            onIndexChanged: {
                switch (index) {
                case 0: mapper.blendMode = Vtk.VolumeMapper.CompositeBlend; break;
                case 1: mapper.blendMode = Vtk.VolumeMapper.MaximumIntensityBlend; break;
                case 2: mapper.blendMode = Vtk.VolumeMapper.MinimumIntensityBlend; break;
                case 3: mapper.blendMode = Vtk.VolumeMapper.AdditiveBlend; break;

                default: mapper.blendMode = Vtk.VolumeMapper.CompositeBlend;
                }
            }
        }
    }
}
