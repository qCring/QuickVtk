#include "quickVtkHedgeHog.hpp"

namespace quick {
    namespace Vtk {

        Qml::Register::Class<HedgeHog> HedgeHog::Register(true);

        HedgeHog::HedgeHog() : PolyDataAlgorithm(vtkSmartPointer<vtkHedgeHog>::New()) {
            this->m_vtkObject = vtkHedgeHog::SafeDownCast(Algorithm::getVtkObject());
        }

        auto HedgeHog::setScaleFactor(qreal scaleFactor) -> void {
            this->m_vtkObject->SetScaleFactor(scaleFactor);
            emit this->scaleFactorChanged();
            this->update();
        }

        auto HedgeHog::getScaleFactor() -> qreal {
            return this->m_vtkObject->GetScaleFactor();
        }

        auto HedgeHog::setVectorMode(VectorMode vectorMode) -> void {
            this->m_vtkObject->SetVectorMode(vectorMode);
            emit this->vectorModeChanged();
            this->update();
        }

        auto HedgeHog::getVectorMode() -> VectorMode {
            return static_cast<VectorMode>(this->m_vtkObject->GetVectorMode());
        }
    }
}
