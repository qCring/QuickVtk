import QtQuick 2.12

import Vtk 1.0 as Vtk
import Math 1.0 as Math

Item {
    id: root;

    anchors.fill: parent;

    Vtk.Viewer {
        anchors.fill: parent;

        mouseEnabled: true;

        Vtk.Actor2D {
            Vtk.ImageMapper {
                colorWindow: 255;
                colorLevel: 127.5;

                Vtk.ImageLaplacian {
                    Vtk.PNGReader {
                        fileName: SampleData.images.lenaPNG;
                    }
                }
            }
        }
    }
}
