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

        auto Glyph3D::setScaleMode(ScaleMode scaleMode) -> void {
            this->m_vtkGlyph3D->SetScaleMode(scaleMode);
            emit this->scaleModeChanged();
            this->update();
        }

        auto Glyph3D::getScaleMode() -> Glyph3D::ScaleMode {
            return (Glyph3D::ScaleMode) this->m_vtkGlyph3D->GetScaleMode();
        }

        auto Glyph3D::setColorMode(ColorMode colorMode) -> void {
            this->m_vtkGlyph3D->SetColorMode(colorMode);
            emit this->colorModeChanged();
            this->update();
        }

        auto Glyph3D::getColorMode() -> ColorMode {
            return (ColorMode) this->m_vtkGlyph3D->GetColorMode();
        }

        auto Glyph3D::setIndexMode(IndexMode indexMode) -> void {
            this->m_vtkGlyph3D->SetIndexMode(indexMode);
            emit this->indexModeChanged();
            this->update();
        }

        auto Glyph3D::getIndexMode() -> IndexMode {
            return (IndexMode) this->m_vtkGlyph3D->GetIndexMode();
        }

        auto Glyph3D::setVectorMode(VectorMode vectorMode) -> void {
            this->m_vtkGlyph3D->SetVectorMode(vectorMode);
            emit this->vectorModeChanged();
            this->update();
        }

        auto Glyph3D::getVectorMode() -> VectorMode {
            return (VectorMode) this->m_vtkGlyph3D->GetVectorMode();
        }

        auto Glyph3D::setScaleFactor(double scaleFactor) -> void {
            this->m_vtkGlyph3D->SetScaleFactor(scaleFactor);
            emit this->scaleFactorChanged();
            this->update();
        }

        auto Glyph3D::getScaleFactor() -> double {
            return this->m_vtkGlyph3D->GetScaleFactor();
        }

        auto Glyph3D::setOrient(bool orient) -> void {
            this->m_vtkGlyph3D->SetOrient(orient);
            emit this->orientChanged();
            this->update();
        }

        auto Glyph3D::getOrient() -> bool {
            return this->m_vtkGlyph3D->GetOrient();
        }

        auto Glyph3D::setClamping(bool clamping) -> void {
            this->m_vtkGlyph3D->SetClamping(clamping);
            emit this->clampingChanged();
            this->update();
        }

        auto Glyph3D::getClamping() -> bool {
            return this->m_vtkGlyph3D->GetClamping();
        }

        auto Glyph3D::setScaling(bool scaling) -> void {
            this->m_vtkGlyph3D->SetScaling(scaling);
            emit this->scalingChanged();
            this->update();
        }

        auto Glyph3D::getScaling() -> bool {
            return this->m_vtkGlyph3D->GetScaling();
        }

        auto Glyph3D::setFillCellData(bool fillCellData) -> void {
            this->m_vtkGlyph3D->SetFillCellData(fillCellData);
            emit this->fillCellDataChanged();
            this->update();
        }

        auto Glyph3D::getFillCellData() -> bool {
            return this->m_vtkGlyph3D->GetFillCellData();
        }

        auto Glyph3D::setGeneratePointIds(bool generatePointIds) -> void {
            this->m_vtkGlyph3D->SetGeneratePointIds(generatePointIds);
            emit this->generatePointIdsChanged();
            this->update();
        }

        auto Glyph3D::getGeneratePointIds() -> bool {
            return this->m_vtkGlyph3D->GetGeneratePointIds();
        }

        Glyph3D::~Glyph3D() {
            this->m_vtkGlyph3D = nullptr;
        }
    }
}