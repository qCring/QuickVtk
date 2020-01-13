#include "quickVtkSmartVolumeMapper.hpp"

namespace quick {

    namespace Vtk {

        Qml::Register::Class<SmartVolumeMapper> SmartVolumeMapper::Register(true);

        SmartVolumeMapper::SmartVolumeMapper() : VolumeMapper(vtkSmartPointer<vtkSmartVolumeMapper>::New()) {
            this->m_vtkObject = vtkSmartVolumeMapper::SafeDownCast(this->Algorithm::getVtkObject());
        }

        auto SmartVolumeMapper::setFinalColorWindow(qreal finalColorWindow) -> void {
            this->m_vtkObject->SetFinalColorWindow(finalColorWindow);
            emit this->finalColorWindowChanged();
            this->update();
        }

        auto SmartVolumeMapper::getFinalColorWindow() -> qreal {
            return this->m_vtkObject->GetFinalColorWindow();
        }

        auto SmartVolumeMapper::setFinalColorLevel(qreal finalColorLevel) -> void {
            this->m_vtkObject->SetFinalColorLevel(finalColorLevel);
            emit this->finalColorLevelChanged();
            this->update();
        }

        auto SmartVolumeMapper::getFinalColorLevel() -> qreal {
            return this->m_vtkObject->GetFinalColorLevel();
        }
    }
}
