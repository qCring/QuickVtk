#include "quickVtkTubeFilter.hpp"

namespace quick {
    namespace Vtk {
        
        Qml::Register::Class<TubeFilter> TubeFilter::Register(true);
    
        TubeFilter::TubeFilter() : PolyDataAlgorithm(vtkSmartPointer<vtkTubeFilter>::New()) {
            this->m_vtkObject = vtkTubeFilter::SafeDownCast(Algorithm::getVtkObject());
            
            this->m_defaultNormal = new Math::Vector3([this](){
                this->m_vtkObject->SetDefaultNormal(this->m_defaultNormal->getValues().data());
                this->update();
            });
        }
    
        auto TubeFilter::setVaryRadius(VaryRadius varyRadius) -> void {
            this->m_vtkObject->SetVaryRadius(varyRadius);
            this->update();
            emit this->varyRadiusChanged();
        }
    
        auto TubeFilter::getVaryRadius() -> VaryRadius {
            return static_cast<VaryRadius>(this->m_vtkObject->GetVaryRadius());
        }
    
        auto TubeFilter::setGenerateTCoords(TCoords tCoords) -> void {
            this->m_vtkObject->SetGenerateTCoords(tCoords);
        }
    
        auto TubeFilter::getGenerateTCoords() -> TCoords {
            return static_cast<TCoords>(this->m_vtkObject->GetGenerateTCoords());
        }
    
        auto TubeFilter::setRadius(qreal radius) -> void {
            this->m_vtkObject->SetRadius(radius);
            this->update();
            emit this->radiusChanged();
        }
    
        auto TubeFilter::getRadius() -> qreal {
            return this->m_vtkObject->GetRadius();
        }
    
        auto TubeFilter::setTextureLength(qreal textureLength) -> void {
            this->m_vtkObject->SetTextureLength(textureLength);
            this->update();
            emit this->textureLengthChanged();
        }
    
        auto TubeFilter::getTextureLength() -> qreal {
            return this->m_vtkObject->GetTextureLength();
        }
    
        auto TubeFilter::setNumberOfSides(int numberOfSides) -> void {
            this->m_vtkObject->SetNumberOfSides(numberOfSides);
            this->update();
            emit this->numberOfSidesChanged();
        }
    
        auto TubeFilter::getNumberOfSides() -> int {
            return this->m_vtkObject->GetNumberOfSides();
        }
    
        auto TubeFilter::setRadiusFactor(qreal radiusFactor) -> void {
            this->m_vtkObject->SetRadiusFactor(radiusFactor);
            this->update();
            emit this->radiusFactorChanged();
        }
    
        auto TubeFilter::getRadiusFactor() -> qreal {
            return this->m_vtkObject->GetRadiusFactor();
        }
    
        auto TubeFilter::setUseDefaultNormal(bool useDefaultNormal) -> void {
            this->m_vtkObject->SetUseDefaultNormal(useDefaultNormal);
            this->update();
            emit this->useDefaultNormalChanged();
        }
    
        auto TubeFilter::getUseDefaultNormal() -> bool {
            return this->m_vtkObject->GetUseDefaultNormal();
        }
    
        auto TubeFilter::setSidesShareVertices(bool sidesShareVertices) -> void {
            this->m_vtkObject->SetSidesShareVertices(sidesShareVertices);
            this->update();
            emit this->sidesShareVerticesChanged();
        }
    
        auto TubeFilter::getSidesShareVertices() -> bool {
            return this->m_vtkObject->GetSidesShareVertices();
        }
    
        auto TubeFilter::setCapping(bool capping) -> void {
            this->m_vtkObject->SetCapping(capping);
            this->update();
            emit this->cappingChanged();
        }
    
        auto TubeFilter::getCapping() -> bool {
            return this->m_vtkObject->GetCapping();
        }
    
        auto TubeFilter::setOnRatio(int onRatio) -> void {
            this->m_vtkObject->SetOnRatio(onRatio);
            this->update();
            emit this->onRatioChanged();
        }
    
        auto TubeFilter::getOnRatio() -> int {
            return this->m_vtkObject->GetOnRatio();
        }
    
        auto TubeFilter::setOffset(int offset) -> void {
            this->m_vtkObject->SetOffset(offset);
            this->update();
            emit this->offsetChanged();
        }
    
        auto TubeFilter::getOffset() -> int {
            return this->m_vtkObject->GetOffset();
        }
    
        auto TubeFilter::getDefaultNormal() -> Math::Vector3* {
            return this->m_defaultNormal;
        }
    }
}
