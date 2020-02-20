#include "quickVtkTexture.hpp"

namespace quick::Vtk {

    Qml::Register::Class<Texture> Texture::Register(true);

    Texture::Texture() : ImageAlgorithm(vtkSmartPointer<vtkTexture>::New()) {
        this->m_vtkObject = vtkTexture::SafeDownCast(ImageAlgorithm::getVtkObject());
    }
    
    Texture::Texture(vtkSmartPointer<vtkTexture> vtkObject, cb_t&& callback) : ImageAlgorithm(vtkObject), m_vtkObject(vtkObject), m_callback(callback) {
    }

    auto Texture::setQuality(Quality quality) -> void {
        this->m_vtkObject->SetQuality(quality);
        emit this->qualityChanged();
        this->update();
    }
    
    auto Texture::getVtkObject() -> vtkSmartPointer<vtkTexture> {
        return this->m_vtkObject;
    }

    auto Texture::getQuality() -> Quality {
        return static_cast<Quality>(this->m_vtkObject->GetQuality());
    }

    auto Texture::setBlendingMode(BlendingMode blendingMode) -> void {
        this->m_vtkObject->SetBlendingMode(blendingMode);
        emit this->blendingModeChanged();
        this->update();
    }

    auto Texture::getBlendingMode() -> BlendingMode {
        return static_cast<BlendingMode>(this->m_vtkObject->GetBlendingMode());
    }

    auto Texture::setRepeat(bool repeat) -> void {
        this->m_vtkObject->SetRepeat(repeat);
        emit this->repeatChanged();
        this->update();
    }

    auto Texture::getRepeat() -> bool {
        return this->m_vtkObject->GetRepeat();
    }

    auto Texture::setEdgeClamp(bool edgeClamp) -> void {
        this->m_vtkObject->SetEdgeClamp(edgeClamp);
        emit this->edgeClampChanged();
        this->update();
    }

    auto Texture::getEdgeClamp() -> bool {
        return this->m_vtkObject->GetEdgeClamp();
    }

    auto Texture::setInterpolate(bool interpolate) -> void {
        this->m_vtkObject->SetInterpolate(interpolate);
        emit this->interpolateChanged();
        this->update();
    }

    auto Texture::getInterpolate() -> bool {
        return this->m_vtkObject->GetInterpolate();
    }
}
