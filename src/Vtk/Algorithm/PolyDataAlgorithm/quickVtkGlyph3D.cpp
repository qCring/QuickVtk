#include "quickVtkGlyph3D.hpp"

namespace quick {

    namespace Vtk {

        Qml::Register::Class<Glyph3D> Glyph3D::Register;

        Glyph3D::Glyph3D() : PolyDataAlgorithm(vtkSmartPointer<vtkGlyph3D>::New()) {
            this->m_vtkObject = vtkGlyph3D::SafeDownCast(Algorithm::getVtkObject());

            this->m_range = new Math::Vector2([this](){
                this->m_vtkObject->SetRange(this->m_range->getX(), this->m_range->getY());
                this->update();
            });
        }

        auto Glyph3D::getRange() -> Math::Vector2* {
            return this->m_range;
        }

        auto Glyph3D::setScaleMode(ScaleMode scaleMode) -> void {
            this->m_vtkObject->SetScaleMode(scaleMode);
            emit this->scaleModeChanged();
            this->update();
        }

        auto Glyph3D::getScaleMode() -> Glyph3D::ScaleMode {
            return (Glyph3D::ScaleMode) this->m_vtkObject->GetScaleMode();
        }

        auto Glyph3D::setColorMode(ColorMode colorMode) -> void {
            this->m_vtkObject->SetColorMode(colorMode);
            emit this->colorModeChanged();
            this->update();
        }

        auto Glyph3D::getColorMode() -> ColorMode {
            return (ColorMode) this->m_vtkObject->GetColorMode();
        }

        auto Glyph3D::setIndexMode(IndexMode indexMode) -> void {
            this->m_vtkObject->SetIndexMode(indexMode);
            emit this->indexModeChanged();
            this->update();
        }

        auto Glyph3D::getIndexMode() -> IndexMode {
            return (IndexMode) this->m_vtkObject->GetIndexMode();
        }

        auto Glyph3D::setVectorMode(VectorMode vectorMode) -> void {
            this->m_vtkObject->SetVectorMode(vectorMode);
            emit this->vectorModeChanged();
            this->update();
        }

        auto Glyph3D::getVectorMode() -> VectorMode {
            return (VectorMode) this->m_vtkObject->GetVectorMode();
        }

        auto Glyph3D::setScaleFactor(double scaleFactor) -> void {
            this->m_vtkObject->SetScaleFactor(scaleFactor);
            emit this->scaleFactorChanged();
            this->update();
        }

        auto Glyph3D::getScaleFactor() -> double {
            return this->m_vtkObject->GetScaleFactor();
        }

        auto Glyph3D::setOrient(bool orient) -> void {
            this->m_vtkObject->SetOrient(orient);
            emit this->orientChanged();
            this->update();
        }

        auto Glyph3D::getOrient() -> bool {
            return this->m_vtkObject->GetOrient();
        }

        auto Glyph3D::setClamping(bool clamping) -> void {
            this->m_vtkObject->SetClamping(clamping);
            emit this->clampingChanged();
            this->update();
        }

        auto Glyph3D::getClamping() -> bool {
            return this->m_vtkObject->GetClamping();
        }

        auto Glyph3D::setScaling(bool scaling) -> void {
            this->m_vtkObject->SetScaling(scaling);
            emit this->scalingChanged();
            this->update();
        }

        auto Glyph3D::getScaling() -> bool {
            return this->m_vtkObject->GetScaling();
        }

        auto Glyph3D::setFillCellData(bool fillCellData) -> void {
            this->m_vtkObject->SetFillCellData(fillCellData);
            emit this->fillCellDataChanged();
            this->update();
        }

        auto Glyph3D::getFillCellData() -> bool {
            return this->m_vtkObject->GetFillCellData();
        }

        auto Glyph3D::setGeneratePointIds(bool generatePointIds) -> void {
            this->m_vtkObject->SetGeneratePointIds(generatePointIds);
            emit this->generatePointIdsChanged();
            this->update();
        }

        auto Glyph3D::getGeneratePointIds() -> bool {
            return this->m_vtkObject->GetGeneratePointIds();
        }
    }
}