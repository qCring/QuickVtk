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
            Q_PROPERTY(bool cropping READ getCropping WRITE setCropping NOTIFY croppingChanged);
        private:
            static Qml::Register::AbstractClass<VolumeMapper> Register;
            vtkSmartPointer<vtkVolumeMapper> m_vtkObject = nullptr;
        public:
            VolumeMapper(vtkSmartPointer<vtkVolumeMapper>);
            auto setBlendMode(BlendMode) -> void;
            auto getBlendMode() -> BlendMode;
            auto setCropping(bool) -> void;
            auto getCropping() -> bool;
        signals:
            void blendModeChanged();
            void croppingChanged();
        };
    }
}