#include "quickVtkVolumeProperty.hpp"
#include "quickVtkVolume.hpp"

namespace quick {

    namespace Vtk {

        Qml::Register::Class<VolumeProperty> VolumeProperty::Register;

        VolumeProperty::VolumeProperty() {
        }

        VolumeProperty::VolumeProperty(Volume* volume) : m_volume(volume) {
            this->m_vtkVolume = this->m_volume->getVtkObject();
        }

        auto VolumeProperty::setVolume(Volume* volume) -> void {
            this->m_volume = volume;
            this->m_vtkVolume = volume->getVtkObject();
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

        VolumeProperty::~VolumeProperty() {
            this->m_vtkVolume = nullptr;
            this->m_volume = nullptr;
        }
    }
}
