#include "quickVtkGlyph3D.hpp"

namespace quick {

    namespace Vtk {

        Qml::Register::Class<Glyph3D> Glyph3D::Register;

        Glyph3D::Glyph3D() : PolyDataAlgorithm(this) {
            this->m_vtkGlyph3D = vtkSmartPointer<vtkGlyph3D>::New();
            PolyDataAlgorithm::setVtkPolyDataAlgorithm(m_vtkGlyph3D);

            this->m_rangeCb = [this] (Math::Vector2&& vector) {
                this->updateRange(std::move(vector));
            };
        }

        auto Glyph3D::updateRange(Math::Vector2&& vector) -> void {
            this->m_vtkGlyph3D->SetRange(vector.getValues().data());
            this->update();
        }

        auto Glyph3D::setRange(Math::Vector2* vector) -> void {
            if (this->m_range) {
                this->m_range->removeCallback(std::move(this->m_rangeCb));
            }

            this->m_range = vector;

            if (vector) {
                vector->addCallback(std::move(this->m_rangeCb));
                this->updateRange(std::move(*vector));
            }

            emit this->rangeChanged();
        }

        auto Glyph3D::getRange() -> Math::Vector2* {
            if (!this->m_range) {
                auto range = this->m_vtkGlyph3D->GetRange();
                this->setRange(new Math::Vector2(range[0], range[1]));
            }

            return this->m_range;
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