#include "quickVtkVolumeProperty.hpp"
#include "quickVtkVolume.hpp"
#include "quickVtkPiecewiseFunction.hpp"

#include <vtkPiecewiseFunction.h>

namespace quick {

    namespace Vtk {

        Qml::Register::UncreatableClass<VolumeProperty> VolumeProperty::Register;

        VolumeProperty::VolumeProperty(Volume* volume) : m_volume(volume), m_vtkVolume(volume->getVtkObject()) {
            this->m_scalarOpacity = new PiecewiseFunction([this](){
                auto opacity = this->m_vtkVolume->GetProperty()->GetScalarOpacity();
                opacity->RemoveAllPoints();

                for (auto i=0; i < this->m_scalarOpacity->getLength(); ++i) {
                    opacity->AddPoint(this->m_scalarOpacity->getX(i), this->m_scalarOpacity->getY(i));
                }

                this->update();
            });
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

        auto VolumeProperty::getScalarOpacity() -> PiecewiseFunction* {
            return this->m_scalarOpacity;
        }
    }
}
