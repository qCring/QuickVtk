#include "quickVtkGlyph3D.hpp"

namespace quick {

    namespace Vtk {

        Qml::Register::Class<Glyph3D> Glyph3D::Register;

        Glyph3D::Glyph3D() : PolyDataAlgorithm(this) {
            this->m_vtkGlyph3D = vtkSmartPointer<vtkGlyph3D>::New();
            PolyDataAlgorithm::setVtkPolyDataAlgorithm(m_vtkGlyph3D);
        }

        auto Glyph3D::setScaleMode(Glyph3D::ScaleMode scaleMode) -> void {
            this->m_vtkGlyph3D->SetScaleMode(scaleMode);
            emit this->scaleModeChanged();
            this->update();
        }

        auto Glyph3D::getScaleMode() -> Glyph3D::ScaleMode {
            return (Glyph3D::ScaleMode) this->m_vtkGlyph3D->GetScaleMode();
        }

        auto Glyph3D::setColorMode(Glyph3D::ColorMode colorMode) -> void {
            this->m_vtkGlyph3D->SetColorMode(colorMode);
            emit this->colorModeChanged();
            this->update();
        }

        auto Glyph3D::getColorMode() -> Glyph3D::ColorMode {
            return (Glyph3D::ColorMode) this->m_vtkGlyph3D->GetColorMode();
        }

        auto Glyph3D::setScaleFactor(double scaleFactor) -> void {
            this->m_vtkGlyph3D->SetScaleFactor(scaleFactor);
            emit this->scaleFactorChanged();
            this->update();
        }

        auto Glyph3D::getScaleFactor() -> double {
            return this->m_vtkGlyph3D->GetScaleFactor();
        }
        
        Glyph3D::~Glyph3D() {
            this->m_vtkGlyph3D = nullptr;
        }
    }
}