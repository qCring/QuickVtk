#include "quickVtkTransformTextureCoords.hpp"

namespace quick::Vtk {

    Qml::Register::Class<TransformTextureCoords> TransformTextureCoords::Register(true);

    TransformTextureCoords::TransformTextureCoords() : DataSetAlgorithm(vtkSmartPointer<vtkTransformTextureCoords>::New()) {
        this->m_vtkObject = vtkTransformTextureCoords::SafeDownCast(DataSetAlgorithm::getVtkObject());
        
        this->m_origin = new Math::Vector3([this](){
            this->m_vtkObject->SetOrigin(this->m_origin->getValues().data());
            this->update();
        });
        
        this->m_position = new Math::Vector3([this](){
            this->m_vtkObject->SetPosition(this->m_position->getValues().data());
            this->update();
        });
        
        this->m_scale = new Math::Vector3([this](){
            this->m_vtkObject->SetScale(this->m_scale->getValues().data());
            this->update();
        });
    }

    auto TransformTextureCoords::getOrigin() -> Math::Vector3* {
        return this->m_origin;
    }
    
    auto TransformTextureCoords::getPosition() -> Math::Vector3* {
        return this->m_position;
    }
    
    auto TransformTextureCoords::getScale() -> Math::Vector3* {
        return this->m_scale;
    }
    
    auto TransformTextureCoords::setFlipR(bool flipR) -> void {
        this->m_vtkObject->SetFlipR(flipR);
        emit this->flipRChanged();
        this->update();
    }
    
    auto TransformTextureCoords::getFlipR() -> bool {
        return this->m_vtkObject->GetFlipR();
    }
    
    auto TransformTextureCoords::setFlipS(bool flipS) -> void {
        this->m_vtkObject->SetFlipS(flipS);
        emit this->flipSChanged();
        this->update();
    }
    
    auto TransformTextureCoords::getFlipS() -> bool {
        return this->m_vtkObject->GetFlipS();
    }
    
    auto TransformTextureCoords::setFlipT(bool flipT) -> void {
        this->m_vtkObject->SetFlipT(flipT);
        emit this->flipTChanged();
        this->update();
    }
    
    auto TransformTextureCoords::getFlipT() -> bool {
        return this->m_vtkObject->GetFlipT();
    }
}
