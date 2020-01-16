#include "quickVtkRibbonFilter.hpp"

namespace quick {
    namespace Vtk {
        
        Qml::Register::Class<RibbonFilter> RibbonFilter::Register(true);
    
        RibbonFilter::RibbonFilter() : PolyDataAlgorithm(vtkSmartPointer<vtkRibbonFilter>::New()) {
            this->m_vtkObject = vtkRibbonFilter::SafeDownCast(Algorithm::getVtkObject());
            
            this->m_defaultNormal = new Math::Vector3([this](){
                this->m_vtkObject->SetDefaultNormal(this->m_defaultNormal->getValues().data());
                this->update();
            });
        }
    
        auto RibbonFilter::setVaryWidth(bool varyWidth) -> void {
            this->m_vtkObject->SetVaryWidth(varyWidth);
            this->update();
            emit this->varyWidthChanged();
        }
    
        auto RibbonFilter::getVaryWidth() -> bool {
            return this->m_vtkObject->GetVaryWidth();
        }
    
        auto RibbonFilter::setGenerateTCoords(TCoords tCoords) -> void {
            this->m_vtkObject->SetGenerateTCoords(tCoords);
        }
    
        auto RibbonFilter::getGenerateTCoords() -> TCoords {
            return static_cast<TCoords>(this->m_vtkObject->GetGenerateTCoords());
        }
    
        auto RibbonFilter::setWidth(qreal width) -> void {
            this->m_vtkObject->SetWidth(width);
            this->update();
            emit this->widthChanged();
        }
    
        auto RibbonFilter::getWidth() -> qreal {
            return this->m_vtkObject->GetWidth();
        }
    
        auto RibbonFilter::setTextureLength(qreal textureLength) -> void {
            this->m_vtkObject->SetTextureLength(textureLength);
            this->update();
            emit this->textureLengthChanged();
        }
    
        auto RibbonFilter::getTextureLength() -> qreal {
            return this->m_vtkObject->GetTextureLength();
        }
    
        auto RibbonFilter::setWidthFactor(qreal widthFactor) -> void {
            this->m_vtkObject->SetWidthFactor(widthFactor);
            this->update();
            emit this->widthFactorChanged();
        }
    
        auto RibbonFilter::getWidthFactor() -> qreal {
            return this->m_vtkObject->GetWidthFactor();
        }
    
        auto RibbonFilter::setUseDefaultNormal(bool useDefaultNormal) -> void {
            this->m_vtkObject->SetUseDefaultNormal(useDefaultNormal);
            this->update();
            emit this->useDefaultNormalChanged();
        }
    
        auto RibbonFilter::getUseDefaultNormal() -> bool {
            return this->m_vtkObject->GetUseDefaultNormal();
        }
    
        auto RibbonFilter::getDefaultNormal() -> Math::Vector3* {
            return this->m_defaultNormal;
        }
    }
}
