#include "quickVtkVolume.hpp"
#include "quickVtkAbstractVolumeMapper.hpp"

namespace quick {

    namespace Vtk {

        Qml::Register::Class<Volume> Volume::Register;

        Volume::Volume() : Prop3D(vtkSmartPointer<vtkVolume>::New()) {
            this->m_vtkVolume = vtkVolume::SafeDownCast(Prop::getVtkObject());
        }

        auto Volume::getVtkObject() -> vtkSmartPointer<vtkVolume> {
            return this->m_vtkVolume;
        }
        
        auto Volume::setMapper(AbstractVolumeMapper* mapper) -> void {
            this->m_mapper = mapper;
            this->m_vtkVolume->SetMapper(mapper->getVtkObject());

            emit this->mapperChanged();

            this->update();
        }

        auto Volume::getMapper() -> AbstractVolumeMapper* {
            return this->m_mapper;
        }
    }
}