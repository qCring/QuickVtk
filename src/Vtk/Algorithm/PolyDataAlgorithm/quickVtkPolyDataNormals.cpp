#include "quickVtkPolyDataNormals.hpp"

namespace quick {

    namespace Vtk {

        Qml::Register::Class<PolyDataNormals> PolyDataNormals::Register;

        PolyDataNormals::PolyDataNormals() : PolyDataAlgorithm(vtkSmartPointer<vtkPolyDataNormals>::New()) {
            this->m_vtkObject = vtkPolyDataNormals::SafeDownCast(Algorithm::getVtkObject());
        }

        auto PolyDataNormals::setFeatureAngle(float featureAngle) -> void {
            this->m_vtkObject->SetFeatureAngle(featureAngle);
            emit this->featureAngleChanged();
            this->update();
        }

        auto PolyDataNormals::getFeatureAngle() -> float {
            return this->m_vtkObject->GetFeatureAngle();
        }

        auto PolyDataNormals::setSplitting(bool splitting) -> void {
            this->m_vtkObject->SetSplitting(splitting);
            emit this->splittingChanged();
            this->update();
        }

        auto PolyDataNormals::getSplitting() -> bool {
            return this->m_vtkObject->GetSplitting();
        }

        auto PolyDataNormals::setConsistency(bool consistency) -> void {
            this->m_vtkObject->SetConsistency(consistency);
            emit this->consistencyChanged();
            this->update();
        }

        auto PolyDataNormals::getConsistency() -> bool {
            return this->m_vtkObject->GetConsistency();
        }

        auto PolyDataNormals::setAutoOrientNormals(bool autoOrientNormals) -> void {
            this->m_vtkObject->SetAutoOrientNormals(autoOrientNormals);
            emit this->autoOrientNormalsChanged();
            this->update();
        }

        auto PolyDataNormals::getAutoOrientNormals() -> bool {
            return this->m_vtkObject->GetAutoOrientNormals();
        }

        auto PolyDataNormals::setComputePointNormals(bool computePointNormals) -> void {
            this->m_vtkObject->SetComputePointNormals(computePointNormals);
            emit this->computePointNormalsChanged();
            this->update();
        }

        auto PolyDataNormals::getComputePointNormals() -> bool {
            return this->m_vtkObject->GetComputePointNormals();
        }

        auto PolyDataNormals::setComputeCellNormals(bool computeCellNormals) -> void {
            this->m_vtkObject->SetComputeCellNormals(computeCellNormals);
            emit this->computeCellNormalsChanged();
            this->update();
        }

        auto PolyDataNormals::getComputeCellNormals() -> bool {
            return this->m_vtkObject->GetComputeCellNormals();
        }

        auto PolyDataNormals::setFlipNormals(bool flipNormals) -> void {
            this->m_vtkObject->SetFlipNormals(flipNormals);
            emit this->flipNormalsChanged();
            this->update();
        }

        auto PolyDataNormals::getFlipNormals() -> bool {
            return this->m_vtkObject->GetFlipNormals();
        }

        auto PolyDataNormals::setNonManifoldTraversal(bool nonManifoldTraversal) -> void {
            this->m_vtkObject->SetNonManifoldTraversal(nonManifoldTraversal);
            emit this->nonManifoldTraversalChanged();
            this->update();
        }

        auto PolyDataNormals::getNonManifoldTraversal() -> bool {
            return this->m_vtkObject->GetNonManifoldTraversal();
        }
    }
}