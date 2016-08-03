#include "quickVtkDecimatePro.hpp"

namespace quick {

    namespace Vtk {

        Qml::Register::Class<DecimatePro> DecimatePro::Register;

        DecimatePro::DecimatePro() : PolyDataAlgorithm(vtkSmartPointer<vtkDecimatePro>::New()) {
            this->m_vtkObject = vtkDecimatePro::SafeDownCast(Algorithm::getVtkObject());
        }

        auto DecimatePro::setDegree(int val) -> void {
            this->m_vtkObject->SetDegree(val);
            emit this->degreeChanged();
            this->update();
        }

        auto DecimatePro::getDegree() -> int {
            return this->m_vtkObject->GetDegree();
        }

        auto DecimatePro::setSplitting(bool val) -> void {
            this->m_vtkObject->SetSplitting(val);
            emit this->splittingChanged();
            this->update();
        }

        auto DecimatePro::getSplitting() -> bool {
            return this->m_vtkObject->GetSplitting();
        }

        auto DecimatePro::setPreSplitMesh(bool val) -> void {
            this->m_vtkObject->SetPreSplitMesh(val);
            emit this->preSplitMeshChanged();
            this->update();
        }

        auto DecimatePro::getPreSplitMesh() -> bool {
            return this->m_vtkObject->GetPreSplitMesh();
        }

        auto DecimatePro::setSplitAngle(float val) -> void {
            this->m_vtkObject->SetSplitAngle(val);
            emit this->splittingChanged();
            this->update();
        }

        auto DecimatePro::getSplitAngle() -> float {
            return this->m_vtkObject->GetSplitAngle();
        }

        auto DecimatePro::setFeatureAngle(float val) -> void {
            this->m_vtkObject->SetFeatureAngle(val);
            emit this->featureAngleChanged();
            this->update();
        }

        auto DecimatePro::getFeatureAngle() -> float {
            return this->m_vtkObject->GetFeatureAngle();
        }

        auto DecimatePro::setPreserveTopology(bool val) -> void {
            this->m_vtkObject->SetPreserveTopology(val);
            emit this->preserveTopologyChanged();
            this->update();
        }

        auto DecimatePro::getPreserveTopology() -> bool {
            return this->m_vtkObject->GetPreserveTopology();
        }

        auto DecimatePro::setTargetReduction(float val) -> void {
            this->m_vtkObject->SetTargetReduction(val);
            emit this->targetReductionChanged();
            this->update();
        }

        auto DecimatePro::getTargetReduction() -> float {
            return this->m_vtkObject->GetTargetReduction();
        }
    }
}