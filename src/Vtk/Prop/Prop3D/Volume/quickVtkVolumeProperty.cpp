#include "quickVtkVolumeProperty.hpp"
#include "quickVtkVolume.hpp"
#include "quickVtkPiecewiseFunction.hpp"
#include "quickVtkColorTransferFunction.hpp"

namespace quick {

    namespace Vtk {

        Qml::Register::UncreatableClass<VolumeProperty> VolumeProperty::Register;

        VolumeProperty::VolumeProperty(Volume* volume) : m_volume(volume), m_vtkVolume(volume->getVtkObject()) {
            auto property = this->m_vtkVolume->GetProperty();

            this->m_scalarOpacityFunction = new PiecewiseFunction(property->GetScalarOpacity(), [this](){ this->update(); });
            this->m_transferFunction = new ColorTransferFunction(property->GetRGBTransferFunction(), [this](){ this->update(); });
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

        auto VolumeProperty::getScalarOpacityFunction() -> PiecewiseFunction* {
            return this->m_scalarOpacityFunction;
        }

        auto VolumeProperty::getTransferFunction() -> ColorTransferFunction* {
            return this->m_transferFunction;
        }
    }
}
