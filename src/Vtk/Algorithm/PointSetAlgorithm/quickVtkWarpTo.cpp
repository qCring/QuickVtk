#include "quickVtkWarpTo.hpp"

namespace quick {

    namespace Vtk {

        Qml::Register::Class<WarpTo> WarpTo::Register;

        WarpTo::WarpTo() : PointSetAlgorithm(vtkSmartPointer<vtkWarpTo>::New()) {
            this->m_vtkObject = vtkWarpTo::SafeDownCast(Algorithm::getVtkObject());

            this->m_positionCb = [this] (Math::Vector3&& vector) {
                this->updatePosition(std::move(vector));
            };
        }

        auto WarpTo::updatePosition(Math::Vector3&& vector) -> void {
            this->m_vtkObject->SetPosition(vector.getValues().data());
            this->update();
        }

        auto WarpTo::setPosition(Math::Vector3* vector) -> void {
            if (this->m_position) {
                this->m_position->removeCallback(std::move(this->m_positionCb));
            }

            this->m_position = vector;

            if (vector) {
                vector->addCallback(std::move(this->m_positionCb));
                this->updatePosition(std::move(*vector));
            }

            emit this->positionChanged();
        }

        auto WarpTo::getPosition() -> Math::Vector3* {
            if (!this->m_position) {
                auto position = this->m_vtkObject->GetPosition();
                this->setPosition(new Math::Vector3(position[0], position[1], position[2]));
            }

            return this->m_position;
        }

        auto WarpTo::setScaleFactor(float scaleFactor) -> void {
            this->m_vtkObject->SetScaleFactor(scaleFactor);
            emit this->scaleFactorChanged();
            this->update();
        }

        auto WarpTo::getScaleFactor() -> float {
            return this->m_vtkObject->GetScaleFactor();
        }

        auto WarpTo::setAbsolute(bool absolute) -> void {
            this->m_vtkObject->SetAbsolute(absolute);
            emit this->absoluteChanged();
            this->update();
        }

        auto WarpTo::getAbsolute() -> bool {
            return this->m_vtkObject->GetAbsolute();
        }
    }
}