#include "quickVtkVolume.hpp"
#include "quickVtkAbstractVolumeMapper.hpp"

namespace quick {

    namespace Vtk {

        Qml::Register::Class<Volume> Volume::Register;

        Volume::Volume() : Prop3D(this) {
            this->m_mapper = nullptr;
            this->m_vtkVolume = vtkSmartPointer<vtkVolume>::New();
            Prop3D::setVtkProp3D(this->m_vtkVolume);
        }

        auto Volume::setMapper(AbstractVolumeMapper* mapper) -> void {
            this->m_mapper = mapper;
            this->m_vtkVolume->SetMapper(mapper->getVtkAbstractVolumeMapper());

            emit this->mapperChanged();

            this->update();
        }

        auto Volume::getMapper() -> AbstractVolumeMapper* {
            return this->m_mapper;
        }

        auto Volume::getVtkVolume() -> vtkSmartPointer<vtkVolume> {
            return this->m_vtkVolume;
        }

        Volume::~Volume() {
            this->m_vtkVolume = nullptr;
        }
    }
}