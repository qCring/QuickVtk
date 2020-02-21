#include "quickVtkTextureMapToPlane.hpp"

namespace quick::Vtk {

    Qml::Register::Class<TextureMapToPlane> TextureMapToPlane::Register(true);

    TextureMapToPlane::TextureMapToPlane() : DataSetAlgorithm(vtkSmartPointer<vtkTextureMapToPlane>::New()) {
        this->m_vtkObject = vtkTextureMapToPlane::SafeDownCast(this->getVtkObject());
        
        this->m_origin = new Math::Vector3([this](){
            this->m_vtkObject->SetOrigin(this->m_origin->getValues().data());
            this->update();
        });
        
        this->m_point1 = new Math::Vector3([this](){
            this->m_vtkObject->SetPoint1(this->m_point1->getValues().data());
            this->update();
        });
        
        this->m_point2 = new Math::Vector3([this]() {
            this->m_vtkObject->SetPoint2(this->m_point2->getValues().data());
            this->update();
        });
        
        this->m_normal = new Math::Vector3([this]() {
            this->m_vtkObject->SetNormal(this->m_normal->getValues().data());
            this->update();
        });
        
        this->m_sRange = new Math::Vector2([this]() {
            this->m_vtkObject->SetSRange(this->m_sRange->getValues().data());
            this->update();
        });
        
        this->m_tRange = new Math::Vector2([this]() {
            this->m_vtkObject->SetTRange(this->m_tRange->getValues().data());
            this->update();
        });
    }
    
    auto TextureMapToPlane::getOrigin() -> Math::Vector3* {
        return this->m_origin;
    }
    
    auto TextureMapToPlane::getPoint1() -> Math::Vector3* {
        return this->m_point1;
    }
    
    auto TextureMapToPlane::getPoint2() -> Math::Vector3* {
        return this->m_point2;
    }
    
    auto TextureMapToPlane::getNormal() -> Math::Vector3* {
        return this->m_normal;
    }
    
    auto TextureMapToPlane::getSRange() -> Math::Vector2* {
        return this->m_sRange;
    }
    
    auto TextureMapToPlane::getTRange() -> Math::Vector2* {
        return this->m_tRange;
    }
}
