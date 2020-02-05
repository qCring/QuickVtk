#include "quickVtkExtractSurface.hpp"

namespace quick::Vtk {

    Qml::Register::Class<ExtractSurface> ExtractSurface::Register(true);

    ExtractSurface::ExtractSurface() : PolyDataAlgorithm(vtkSmartPointer<vtkExtractSurface>::New()) {
        this->m_vtkObject = vtkExtractSurface::SafeDownCast(Algorithm::getVtkObject());
    }

    auto ExtractSurface::setRadius(qreal radius) -> void {
        this->m_vtkObject->SetRadius(radius);
        this->update();
        emit this->radiusChanged();
    }

    auto ExtractSurface::getRadius() -> qreal {
        return this->m_vtkObject->GetRadius();
    }

    auto ExtractSurface::setHoleFilling(bool holeFilling) -> void {
        this->m_vtkObject->SetHoleFilling(holeFilling);
        this->update();
        emit this->holeFillingChanged();
    }

    auto ExtractSurface::getHoleFilling() -> bool {
        return this->m_vtkObject->GetHoleFilling();
    }

    auto ExtractSurface::setComputeNormals(bool computeNormals) -> void {
        this->m_vtkObject->SetComputeNormals(computeNormals);
        this->update();
        emit this->computeNormalsChanged();
    }

    auto ExtractSurface::getComputeNormals() -> bool {
        return this->m_vtkObject->GetComputeNormals();
    }

    auto ExtractSurface::setComputeGradients(bool computeGradients) -> void {
        this->m_vtkObject->SetComputeGradients(computeGradients);
        this->update();
        emit this->computeGradientsChanged();
    }

    auto ExtractSurface::getComputeGradients() -> bool {
        return this->m_vtkObject->GetComputeGradients();
    }
}
