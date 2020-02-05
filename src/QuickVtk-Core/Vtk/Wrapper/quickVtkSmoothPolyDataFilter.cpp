#include "quickVtkSmoothPolyDataFilter.hpp"

namespace quick::Vtk {

    Qml::Register::Class<SmoothPolyDataFilter> SmoothPolyDataFilter::Register(true);

    SmoothPolyDataFilter::SmoothPolyDataFilter() : PolyDataAlgorithm(vtkSmartPointer<vtkSmoothPolyDataFilter>::New()) {
        this->m_vtkObject = vtkSmoothPolyDataFilter::SafeDownCast(Algorithm::getVtkObject());
    }

    auto SmoothPolyDataFilter::setConvergence(qreal convergence) -> void {
        this->m_vtkObject->SetConvergence(convergence);
        this->update();
        emit this->convergenceChanged();
    }

    auto SmoothPolyDataFilter::getConvergence() -> qreal {
        return this->m_vtkObject->GetConvergence();
    }

    auto SmoothPolyDataFilter::setNumberOfIterations(int numberOfIterations) -> void {
        this->m_vtkObject->SetNumberOfIterations(numberOfIterations);
        this->update();
        emit this->numberOfIterationsChanged();
    }

    auto SmoothPolyDataFilter::setRelaxationFactor(qreal relaxationFactor) -> void {
        this->m_vtkObject->SetRelaxationFactor(relaxationFactor);
        this->update();
        emit this->relaxationFactorChanged();
    }
    
    auto SmoothPolyDataFilter::getRelaxationFactor() -> qreal {
        return this->m_vtkObject->GetRelaxationFactor();
    }
    
    auto SmoothPolyDataFilter::getNumberOfIterations() -> int {
        return this->m_vtkObject->GetNumberOfIterations();
    }

    auto SmoothPolyDataFilter::setFeatureEdgeSmoothing(bool featureEdgeSmoothing) -> void {
        this->m_vtkObject->SetFeatureEdgeSmoothing(featureEdgeSmoothing);
        this->update();
        emit this->featureEdgeSmoothingChanged();
    }
    
    auto SmoothPolyDataFilter::getFeatureEdgeSmoothing() -> bool {
        return this->m_vtkObject->GetFeatureEdgeSmoothing();
    }

    auto SmoothPolyDataFilter::setFeatureAngle(qreal featureAngle) -> void {
        this->m_vtkObject->SetFeatureAngle(featureAngle);
        this->update();
        emit this->featureAngleChanged();
    }

    auto SmoothPolyDataFilter::getFeatureAngle() -> qreal {
        return this->m_vtkObject->GetFeatureAngle();
    }

    auto SmoothPolyDataFilter::setEdgeAngle(qreal edgeAngle) -> void {
        this->m_vtkObject->SetEdgeAngle(edgeAngle);
        this->update();
        emit this->edgeAngleChanged();
    }

    auto SmoothPolyDataFilter::getEdgeAngle() -> qreal {
        return this->m_vtkObject->GetEdgeAngle();
    }

    auto SmoothPolyDataFilter::setBoundarySmoothing(bool boundarySmoothing) -> void {
        this->m_vtkObject->SetBoundarySmoothing(boundarySmoothing);
        this->update();
        emit this->boundarySmoothingChanged();
    }

    auto SmoothPolyDataFilter::getBoundarySmoothing() -> bool {
        return this->m_vtkObject->GetBoundarySmoothing();
    }

    auto SmoothPolyDataFilter::setGenerateErrorScalars(bool generateErrorScalars) -> void {
        this->m_vtkObject->SetGenerateErrorScalars(generateErrorScalars);
        this->update();
        emit this->generateErrorScalarsChanged();
    }
    
    auto SmoothPolyDataFilter::getGenerateErrorScalars() -> bool {
        return this->m_vtkObject->GetGenerateErrorScalars();
    }

    auto SmoothPolyDataFilter::setGenerateErrorVectors(bool generateErrorVectors) -> void {
        this->m_vtkObject->SetGenerateErrorScalars(generateErrorVectors);
        this->update();
        emit this->generateErrorVectorsChanged();
    }
    
    auto SmoothPolyDataFilter::getGenerateErrorVectors() -> bool {
        return this->m_vtkObject->GetGenerateErrorVectors();
    }
}
