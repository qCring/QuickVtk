#include "quickVtkAdaptiveSubdivisionFilter.hpp"

namespace quick {

    namespace Vtk {
        Qml::Register::Class<AdaptiveSubdivisionFilter> AdaptiveSubdivisionFilter::Register;

        AdaptiveSubdivisionFilter::AdaptiveSubdivisionFilter() : PolyDataAlgorithm(vtkSmartPointer<vtkAdaptiveSubdivisionFilter>::New()) {
            this->m_vtkObject = vtkAdaptiveSubdivisionFilter::SafeDownCast(this->Algorithm::getVtkObject());
        }

        auto AdaptiveSubdivisionFilter::setMaximumEdgeLength(float maximumEdgeLength) -> void {
            this->m_vtkObject->SetMaximumEdgeLength(maximumEdgeLength);
            emit this->maximumEdgeLengthChanged();
            this->update();
        }

        auto AdaptiveSubdivisionFilter::getMaximumEdgeLength() -> float {
            return this->m_vtkObject->GetMaximumEdgeLength();
        }

        auto AdaptiveSubdivisionFilter::setMaximumTriangleArea(float maximumTriangleArea) -> void {
            this->m_vtkObject->SetMaximumTriangleArea(maximumTriangleArea);
            emit this->maximumTriangleAreaChanged();
            this->update();
        }

        auto AdaptiveSubdivisionFilter::getMaximumTriangleArea() -> float {
            return this->m_vtkObject->GetMaximumTriangleArea();
        }

        auto AdaptiveSubdivisionFilter::setMaximumNumberOfTriangles(int maximumNumberOfTriangles) -> void {
            this->m_vtkObject->SetMaximumNumberOfTriangles(maximumNumberOfTriangles);
            emit this->maximumNumberOfTrianglesChanged();
            this->update();
        }

        auto AdaptiveSubdivisionFilter::getMaximumNumberOfTriangles() -> int {
            return this->m_vtkObject->GetMaximumNumberOfTriangles();
        }

        auto AdaptiveSubdivisionFilter::setMaximumNumberOfPasses(int maximumNumberOfPasses) -> void {
            this->m_vtkObject->SetMaximumNumberOfPasses(maximumNumberOfPasses);
            emit this->maximumNumberOfPassesChanged();
            this->update();
        }

        auto AdaptiveSubdivisionFilter::getMaximumNumberOfPasses() -> int {
            return this->m_vtkObject->GetMaximumNumberOfPasses();
        }
    }
}