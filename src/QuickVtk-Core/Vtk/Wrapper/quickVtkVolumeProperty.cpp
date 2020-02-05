#include "quickVtkVolumeProperty.hpp"
#include "quickVtkVolume.hpp"
#include "quickVtkPiecewiseFunction.hpp"
#include "quickVtkColorTransferFunction.hpp"

namespace quick::Vtk {

    Qml::Register::UncreatableClass<VolumeProperty> VolumeProperty::Register(true);

    VolumeProperty::VolumeProperty(Volume* volume) : m_volume(volume), m_vtkVolume(volume->getVtkObject()) {
        auto property = this->m_vtkVolume->GetProperty();

        this->m_gradientOpacityFunction = new PiecewiseFunction(property->GetGradientOpacity(), [this](){ this->update(); });
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

    auto VolumeProperty::setAmbient(qreal ambient) -> void {
        this->m_vtkVolume->GetProperty()->SetAmbient(ambient);
        emit this->ambientChanged();
        this->update();
    }

    auto VolumeProperty::getAmbient() -> qreal {
        return this->m_vtkVolume->GetProperty()->GetAmbient();
    }

    auto VolumeProperty::setDiffuse(qreal diffuse) -> void {
        this->m_vtkVolume->GetProperty()->SetDiffuse(diffuse);
        emit this->diffuseChanged();
        this->update();
    }

    auto VolumeProperty::getDiffuse() -> qreal {
        return this->m_vtkVolume->GetProperty()->GetDiffuse();
    }

    auto VolumeProperty::setSpecular(qreal specular) -> void {
        this->m_vtkVolume->GetProperty()->SetSpecular(specular);
        emit this->specularChanged();
        this->update();
    }

    auto VolumeProperty::getSpecular() -> qreal {
        return this->m_vtkVolume->GetProperty()->GetSpecular();
    }

    auto VolumeProperty::setSpecularPower(qreal specularPower) -> void {
        this->m_vtkVolume->GetProperty()->SetSpecularPower(specularPower);
        emit this->specularPowerChanged();
        this->update();
    }

    auto VolumeProperty::getSpecularPower() -> qreal {
        return this->m_vtkVolume->GetProperty()->GetSpecularPower();
    }

    auto VolumeProperty::getGradientOpacityFunction() -> PiecewiseFunction* {
        return this->m_gradientOpacityFunction;
    }

    auto VolumeProperty::getScalarOpacityFunction() -> PiecewiseFunction* {
        return this->m_scalarOpacityFunction;
    }

    auto VolumeProperty::getTransferFunction() -> ColorTransferFunction* {
        return this->m_transferFunction;
    }
}
