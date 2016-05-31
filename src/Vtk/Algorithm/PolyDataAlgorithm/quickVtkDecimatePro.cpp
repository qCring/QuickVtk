#include "quickVtkDecimatePro.hpp"

namespace quick {

    namespace Vtk {

        Qml::Register::VtkClass<DecimatePro> DecimatePro::Register;

        DecimatePro::DecimatePro() : PolyDataAlgorithm(this) {
            this->m_vtkDecimatePro = vtkSmartPointer<vtkDecimatePro>::New();
            PolyDataAlgorithm::setVtkPolyDataAlgorithm(m_vtkDecimatePro);
        }

        auto DecimatePro::setDegree(int val) -> void {
            this->m_vtkDecimatePro->SetDegree(val);
            emit this->degreeChanged();
            this->update();
        }

        auto DecimatePro::getDegree() -> int {
            return this->m_vtkDecimatePro->GetDegree();
        }

        auto DecimatePro::setSplitting(bool val) -> void {
            this->m_vtkDecimatePro->SetSplitting(val);
            emit this->splittingChanged();
            this->update();
        }

        auto DecimatePro::getSplitting() -> bool {
            return this->m_vtkDecimatePro->GetSplitting();
        }

        auto DecimatePro::setPreSplitMesh(bool val) -> void {
            this->m_vtkDecimatePro->SetPreSplitMesh(val);
            emit this->preSplitMeshChanged();
            this->update();
        }

        auto DecimatePro::getPreSplitMesh() -> bool {
            return this->m_vtkDecimatePro->GetPreSplitMesh();
        }

        auto DecimatePro::setSplitAngle(float val) -> void {
            this->m_vtkDecimatePro->SetSplitAngle(val);
            emit this->splittingChanged();
            this->update();
        }

        auto DecimatePro::getSplitAngle() -> float {
            return this->m_vtkDecimatePro->GetSplitAngle();
        }

        auto DecimatePro::setFeatureAngle(float val) -> void {
            this->m_vtkDecimatePro->SetFeatureAngle(val);
            emit this->featureAngleChanged();
            this->update();
        }

        auto DecimatePro::getFeatureAngle() -> float {
            return this->m_vtkDecimatePro->GetFeatureAngle();
        }

        auto DecimatePro::setPreserveTopology(bool val) -> void {
            this->m_vtkDecimatePro->SetPreserveTopology(val);
            emit this->preserveTopologyChanged();
            this->update();
        }

        auto DecimatePro::getPreserveTopology() -> bool {
            return this->m_vtkDecimatePro->GetPreserveTopology();
        }

        auto DecimatePro::setTargetReduction(float val) -> void {
            this->m_vtkDecimatePro->SetTargetReduction(val);
            emit this->targetReductionChanged();
            this->update();
        }

        auto DecimatePro::getTargetReduction() -> float {
            return this->m_vtkDecimatePro->GetTargetReduction();
        }

        DecimatePro::~DecimatePro() {
            this->m_vtkDecimatePro = 0;
        }
    }
}