#include "quickVtkVolumeMapper.hpp"

namespace quick {

    namespace Vtk {

        Qml::Register::AbstractClass<VolumeMapper> VolumeMapper::Register(true);

        VolumeMapper::VolumeMapper(vtkSmartPointer<vtkVolumeMapper> vtkObject) : AbstractVolumeMapper(vtkObject) {
            this->m_vtkObject = vtkVolumeMapper::SafeDownCast(vtkObject);
        }

        auto VolumeMapper::setBlendMode(BlendMode blendMode) -> void {
            this->m_vtkObject->SetBlendMode(blendMode);
            emit this->blendModeChanged();
            this->update();
        }

        auto VolumeMapper::getBlendMode() -> BlendMode {
            return (BlendMode) this->m_vtkObject->GetBlendMode();
        }

        auto VolumeMapper::setCropping(bool cropping) -> void {
            this->m_vtkObject->SetCropping(cropping);
            emit this->croppingChanged();
            this->update();
        }

        auto VolumeMapper::getCropping() -> bool {
            return this->m_vtkObject->GetCropping();
        }
    }
}
