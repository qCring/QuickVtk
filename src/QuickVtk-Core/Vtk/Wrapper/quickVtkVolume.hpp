#pragma once

#include "quickVtkProp3D.hpp"

#include <vtkVolume.h>

namespace quick {
    namespace Vtk {

        class AbstractVolumeMapper;
        class VolumeProperty;

        class Volume : public Prop3D {
            Q_OBJECT
            Q_PROPERTY(quick::Vtk::AbstractVolumeMapper* mapper READ getMapper WRITE setMapper NOTIFY mapperChanged);
            Q_PROPERTY(quick::Vtk::VolumeProperty* property READ getProperty CONSTANT);
            Q_CLASSINFO("DefaultProperty", "mapper");
        private:
            static Qml::Register::Class<Volume> Register;
            VolumeProperty* m_property = nullptr;
            AbstractVolumeMapper* m_mapper = nullptr;
            vtkSmartPointer<vtkVolume> m_vtkVolume = nullptr;
        public:
            Volume();
            auto setMapper(AbstractVolumeMapper*) -> void;
            auto getMapper() -> AbstractVolumeMapper*;
            auto getProperty() -> VolumeProperty*;
            auto getVtkObject() -> vtkSmartPointer<vtkVolume>;
            ~Volume();
        signals:
            void mapperChanged();
        };
    }
}
