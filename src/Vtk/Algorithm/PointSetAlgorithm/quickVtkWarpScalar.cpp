#include "quickVtkWarpScalar.hpp"

namespace quick {

    namespace Vtk {

        Qml::Register::Class<WarpScalar> WarpScalar::Register;

        WarpScalar::WarpScalar() : PointSetAlgorithm(vtkSmartPointer<vtkWarpScalar>::New()) {
            this->m_vtkObject = vtkWarpScalar::SafeDownCast(Algorithm::getVtkObject());
        }

        auto WarpScalar::setScaleFactor(float scaleFactor) -> void {
            this->m_vtkObject->SetScaleFactor(scaleFactor);
            emit this->scaleFactorChanged();
            this->update();
        }

        auto WarpScalar::getScaleFactor() -> float {
            return this->m_vtkObject->GetScaleFactor();
        }

        auto WarpScalar::setUseNormal(bool useNormal) -> void {
            this->m_vtkObject->SetUseNormal(useNormal);
            emit this->useNormalChanged();
            this->update();
        }

        auto WarpScalar::getUseNormal() -> bool {
            return this->m_vtkObject->GetUseNormal();
        }
    }
}