#pragma once

#include "quickVtkProp3D.hpp"

#include <vtkVolume.h>

namespace quick {

    namespace Vtk {

        class AbstractVolumeMapper;

        class Volume : public Prop3D {
            Q_OBJECT
            Q_PROPERTY(quick::Vtk::AbstractVolumeMapper* mapper READ getMapper WRITE setMapper NOTIFY mapperChanged);
            Q_CLASSINFO("DefaultProperty", "mapper");
        private:
            static Qml::Register::Class<Volume> Register;
            AbstractVolumeMapper* m_mapper = nullptr;
            vtkSmartPointer<vtkVolume> m_vtkVolume;
        public:
            Volume();
            auto setMapper(AbstractVolumeMapper*) -> void;
            auto getMapper() -> AbstractVolumeMapper*;
            auto getVtkVolume() -> vtkSmartPointer<vtkVolume>;
            virtual ~Volume();
        signals:
            void mapperChanged();
        };
    }
}