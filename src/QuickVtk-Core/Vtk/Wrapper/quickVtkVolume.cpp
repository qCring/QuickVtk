#include "quickVtkVolume.hpp"
#include "quickVtkAbstractVolumeMapper.hpp"
#include "quickVtkVolumeProperty.hpp"

namespace quick::Vtk {

    Qml::Register::Class<Volume> Volume::Register(true);

    Volume::Volume() : Prop3D(vtkSmartPointer<vtkVolume>::New()) {
        this->m_vtkVolume = vtkVolume::SafeDownCast(Prop::getVtkObject());
        this->m_property = new VolumeProperty(this);
    }

    auto Volume::getVtkObject() -> vtkSmartPointer<vtkVolume> {
        return this->m_vtkVolume;
    }
    
    auto Volume::setMapper(AbstractVolumeMapper* mapper) -> void {
        this->m_mapper = mapper;
        this->m_vtkVolume->SetMapper(mapper->getVtkObject());
        mapper->setProp(this);

        emit this->mapperChanged();

        this->update();
    }

    auto Volume::getMapper() -> AbstractVolumeMapper* {
        return this->m_mapper;
    }

    auto Volume::getProperty() -> VolumeProperty* {
        return this->m_property;
    }

    Volume::~Volume() {
        delete this->m_property;
    }
}
