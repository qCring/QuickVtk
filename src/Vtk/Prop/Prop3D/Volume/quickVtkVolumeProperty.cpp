#include "quickVtkVolumeProperty.hpp"
#include "quickVtkVolume.hpp"

namespace quick {

    namespace Vtk {

        Qml::Register::UncreatableClass<VolumeProperty> VolumeProperty::Register;

        VolumeProperty::VolumeProperty(Volume* volume) : m_volume(volume), m_vtkVolume(volume->getVtkObject()) {
        }

        auto VolumeProperty::update() -> void {
            this->m_volume->update();
        }

        auto VolumeProperty::setShade(bool shade) -> void {
            this->m_vtkVolume->GetProperty()->SetShade(shade);
            emit this->shadeChanged();
            this->update();
        }

        auto VolumeProperty::getShade() -> bool {
            return this->m_vtkVolume->GetProperty()->GetShade();
        }
    }
}
