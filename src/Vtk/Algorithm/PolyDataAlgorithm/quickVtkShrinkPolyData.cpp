#include "quickVtkShrinkPolyData.hpp"

namespace quick {

    namespace Vtk {

        Qml::Register::Class<ShrinkPolyData> ShrinkPolyData::Register;

        ShrinkPolyData::ShrinkPolyData() : PolyDataAlgorithm(vtkSmartPointer<vtkShrinkPolyData>::New()) {
            this->m_vtkObject = vtkShrinkPolyData::SafeDownCast(Algorithm::getVtkObject());
        }

        auto ShrinkPolyData::setShrinkFactor(float val) -> void {
            this->m_vtkObject->SetShrinkFactor(val);
            emit this->shrinkFactorChanged();
            this->update();
        }

        auto ShrinkPolyData::getShrinkFactor() -> float {
            return this->m_vtkObject->GetShrinkFactor();
        }
    }
}