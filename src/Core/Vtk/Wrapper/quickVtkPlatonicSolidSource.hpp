#pragma once

#include "quickVtkPolyDataAlgorithm.hpp"

#include <vtkPlatonicSolidSource.h>

namespace quick {

    namespace Vtk {

        class PlatonicSolidSource : public PolyDataAlgorithm {
            Q_OBJECT
        public:
            enum SolidType {
                SolidTetrahedron = VTK_SOLID_TETRAHEDRON,
                SolidCube = VTK_SOLID_CUBE,
                SolidOctahedron = VTK_SOLID_OCTAHEDRON,
                SolidIcosahedron = VTK_SOLID_ICOSAHEDRON,
                SolidDodecahedron = VTK_SOLID_DODECAHEDRON
            };
        private:
            Q_ENUM(SolidType);
            Q_PROPERTY(SolidType solidType READ getSolidType WRITE setSolidType NOTIFY solidTypeChanged);
        private:
            static Qml::Register::Class<PlatonicSolidSource> Register;
            vtkSmartPointer<vtkPlatonicSolidSource> m_vtkObject = nullptr;
        public:
            PlatonicSolidSource();
            auto setSolidType(SolidType) -> void;
            auto getSolidType() -> SolidType;
        signals:
            void solidTypeChanged();
        };
    }
}
