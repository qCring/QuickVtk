#include "quickVtkShrinkPolyData.hpp"

namespace quick {

    namespace Vtk {

        Qml::Register::VtkClass<ShrinkPolyData> ShrinkPolyData::Register;

        ShrinkPolyData::ShrinkPolyData() : PolyDataAlgorithm(this) {
            this->m_vtkShrinkPolyData = vtkSmartPointer<vtkShrinkPolyData>::New();
            PolyDataAlgorithm::setVtkPolyDataAlgorithm(m_vtkShrinkPolyData);
        }

        auto ShrinkPolyData::setShrinkFactor(float val) -> void {
            this->m_vtkShrinkPolyData->SetShrinkFactor(val);
            emit this->shrinkFactorChanged();
            this->update();
        }

        auto ShrinkPolyData::getShrinkFactor() -> float {
            return this->m_vtkShrinkPolyData->GetShrinkFactor();
        }

        ShrinkPolyData::~ShrinkPolyData() {
            this->m_vtkShrinkPolyData = 0;
        }
    }
}