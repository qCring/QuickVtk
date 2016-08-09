#include "quickVtkWarpLens.hpp"

namespace quick {

    namespace Vtk {

        Qml::Register::Class<WarpLens> WarpLens::Register;

        WarpLens::WarpLens() : PointSetAlgorithm(vtkSmartPointer<vtkWarpLens>::New()) {
            this->m_vtkObject = vtkWarpLens::SafeDownCast(Algorithm::getVtkObject());

            this->m_centerCb = [this] (Math::Vector2&& vector) {
                this->updateCenter(std::move(vector));
            };

            this->m_principalPointCb = [this] (Math::Vector2&& vector) {
                this->updatePrincipalPoint(std::move(vector));
            };
        }

        auto WarpLens::updateCenter(Math::Vector2&& vector) -> void {
            auto center = vector.getValues();
            this->m_vtkObject->SetCenter(center.at(0), center.at(1));
            this->update();
        }

        auto WarpLens::updatePrincipalPoint(Math::Vector2&& vector) -> void {
            auto principalPoint = vector.getValues();
            this->m_vtkObject->SetPrincipalPoint(principalPoint.at(0), principalPoint.at(1));
            this->update();
        }

        auto WarpLens::setCenter(Math::Vector2* vector) -> void {
            if (this->m_center) {
                this->m_center->removeCallback(std::move(this->m_centerCb));
            }

            this->m_center = vector;

            if (vector) {
                vector->addCallback(std::move(this->m_centerCb));
                this->updateCenter(std::move(*vector));
            }

            emit this->centerChanged();
        }

        auto WarpLens::getCenter() -> Math::Vector2* {
            if (!this->m_center) {
                auto center = this->m_vtkObject->GetCenter();
                this->setCenter(new Math::Vector2(center[0], center[1]));
            }

            return this->m_center;
        }

        auto WarpLens::setPrincipalPoint(Math::Vector2* vector) -> void {
            if (this->m_principalPoint) {
                this->m_principalPoint->removeCallback(std::move(this->m_principalPointCb));
            }

            this->m_principalPoint = vector;

            if (vector) {
                vector->addCallback(std::move(this->m_principalPointCb));
                this->updatePrincipalPoint(std::move(*vector));
            }

            emit this->principalPointChanged();
        }

        auto WarpLens::getPrincipalPoint() -> Math::Vector2* {
            if (!this->m_principalPoint) {
                auto principalPoint = this->m_vtkObject->GetPrincipalPoint();
                this->setPrincipalPoint(new Math::Vector2(principalPoint[0], principalPoint[1]));
            }

            return this->m_principalPoint;
        }

        auto WarpLens::setK1(float k1) -> void {
            this->m_vtkObject->SetK1(k1);
            emit this->k1Changed();
            this->update();
        }

        auto WarpLens::getK1() -> float {
            return this->m_vtkObject->GetK1();
        }

        auto WarpLens::setK2(float k2) -> void {
            this->m_vtkObject->SetK2(k2);
            emit this->k2Changed();
            this->update();
        }

        auto WarpLens::getK2() -> float {
            return this->m_vtkObject->GetK2();
        }

        auto WarpLens::setP1(float p1) -> void {
            this->m_vtkObject->SetP1(p1);
            emit this->p1Changed();
            this->update();
        }

        auto WarpLens::getP1() -> float {
            return this->m_vtkObject->GetP1();
        }

        auto WarpLens::setP2(float p2) -> void {
            this->m_vtkObject->SetP2(p2);
            emit this->p2Changed();
            this->update();
        }

        auto WarpLens::getP2() -> float {
            return this->m_vtkObject->GetP2();
        }
    }
}