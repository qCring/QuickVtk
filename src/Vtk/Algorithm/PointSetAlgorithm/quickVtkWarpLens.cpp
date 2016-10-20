#include "quickVtkWarpLens.hpp"

namespace quick {

    namespace Vtk {

        Qml::Register::Symbol::Class<WarpLens> WarpLens::Register;

        WarpLens::WarpLens() : PointSetAlgorithm(vtkSmartPointer<vtkWarpLens>::New()) {
            this->m_vtkObject = vtkWarpLens::SafeDownCast(Algorithm::getVtkObject());

            this->m_center = new Math::Vector2([this](){
                this->m_vtkObject->SetCenter(this->m_center->getX(), this->m_center->getY());
                this->update();
            });

            this->m_principalPoint = new Math::Vector2([this](){
                this->m_vtkObject->SetPrincipalPoint(this->m_principalPoint->getX(), this->m_principalPoint->getY());
                this->update();
            });
        }

        auto WarpLens::getCenter() -> Math::Vector2* {
            return this->m_center;
        }

        auto WarpLens::getPrincipalPoint() -> Math::Vector2* {
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
