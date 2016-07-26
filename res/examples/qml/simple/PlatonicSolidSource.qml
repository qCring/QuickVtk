import QtQuick 2.6
import QtQuick.Controls 1.5

import Vtk 1.0 as Vtk
import Math 1.0 as Math

Item {
    id: root;

    anchors.fill: parent;

    Vtk.Viewer {
        anchors.fill: parent;

        mouseEnabled: true;

        Vtk.Actor {
            Vtk.PolyDataMapper {
                Vtk.PlatonicSolidSource {
                    id: platonicSolid;
                }
            }
        }
    }

    ComboBox {
        anchors.right: parent.right;
        anchors.top: parent.top;
        anchors.margins: 8;
        model: ["Tetrahedron", "Cube", "Octahedron", "Icosahedron", "Dodecahedron"];

        onCurrentIndexChanged: {
            switch (currentIndex) {
            case 0: platonicSolid.solidType = Vtk.PlatonicSolidSource.SolidTetrahedron; break;
            case 1: platonicSolid.solidType = Vtk.PlatonicSolidSource.SolidCube; break;
            case 2: platonicSolid.solidType = Vtk.PlatonicSolidSource.SolidOctahedron; break;
            case 3: platonicSolid.solidType = Vtk.PlatonicSolidSource.SolidIcosahedron; break;
            case 4: platonicSolid.solidType = Vtk.PlatonicSolidSource.SolidDodecahedron; break;

            default: platonicSolid.solidType = Vtk.PlatonicSolidSource.SolidTetrahedron;
            }
        }
    }
}
