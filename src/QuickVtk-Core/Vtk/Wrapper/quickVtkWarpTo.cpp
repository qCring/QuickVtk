#include "quickVtkWarpTo.hpp"

namespace quick::Vtk {

    Qml::Register::Class<WarpTo> WarpTo::Register(true);

    WarpTo::WarpTo() : PointSetAlgorithm(vtkSmartPointer<vtkWarpTo>::New()) {
        this->m_vtkObject = vtkWarpTo::SafeDownCast(Algorithm::getVtkObject());
        this->m_position = new Math::Vector3([this](){
            this->m_vtkObject->SetPosition(this->m_position->getValues().data());
            this->update();
        });
    }

    auto WarpTo::getPosition() -> Math::Vector3* {
        return this->m_position;
    }

    auto WarpTo::setScaleFactor(qreal scaleFactor) -> void {
        this->m_vtkObject->SetScaleFactor(scaleFactor);
        emit this->scaleFactorChanged();
        this->update();
    }

    auto WarpTo::getScaleFactor() -> qreal {
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
