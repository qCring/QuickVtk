#pragma once

#include "quickVtkAbstractVolumeMapper.hpp"

#include <vtkVolumeMapper.h>

namespace quick {

    namespace Vtk {

        class VolumeMapper : public AbstractVolumeMapper {
            Q_OBJECT
        public:
            enum BlendMode {
                CompositeBlend = vtkVolumeMapper::COMPOSITE_BLEND,
                MaximumIntensityBlend = vtkVolumeMapper::MAXIMUM_INTENSITY_BLEND,
                MinimumIntensityBlend = vtkVolumeMapper::MINIMUM_INTENSITY_BLEND,
                AdditiveBlend = vtkVolumeMapper::ADDITIVE_BLEND
            };
        private:
            Q_ENUM(BlendMode);
            Q_PROPERTY(BlendMode blendMode READ getBlendMode WRITE setBlendMode NOTIFY blendModeChanged);
        private:
            static Qml::Register::AbstractClass<VolumeMapper> Register;
            vtkSmartPointer<vtkVolumeMapper> m_vtkObject = nullptr;
        public:
            VolumeMapper(vtkSmartPointer<vtkVolumeMapper>);
            auto setBlendMode(BlendMode) -> void;
            auto getBlendMode() -> BlendMode;
        signals:
            void blendModeChanged();
        };
    }
}