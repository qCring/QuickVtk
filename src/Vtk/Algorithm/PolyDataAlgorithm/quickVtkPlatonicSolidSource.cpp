#include "quickVtkPlatonicSolidSource.hpp"

namespace quick {

    namespace Vtk {

        Qml::Register::Class<PlatonicSolidSource> PlatonicSolidSource::Register;

        PlatonicSolidSource::PlatonicSolidSource() : PolyDataAlgorithm(this) {
            this->m_vtkPlatonicSolidSource = vtkSmartPointer<vtkPlatonicSolidSource>::New();
            PolyDataAlgorithm::setVtkPolyDataAlgorithm(m_vtkPlatonicSolidSource);
        }

        auto PlatonicSolidSource::setSolidType(SolidType solidType) -> void {
            this->m_vtkPlatonicSolidSource->SetSolidType(solidType);
            this->update();
            emit this->solidTypeChanged();
        }

        auto PlatonicSolidSource::getSolidType() -> SolidType {
            return (SolidType) this->m_vtkPlatonicSolidSource->GetSolidType();
        }
    }
}