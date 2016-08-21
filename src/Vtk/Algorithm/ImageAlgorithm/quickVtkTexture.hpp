#pragma once

#include "quickVtkImageAlgorithm.hpp"

#include <functional>
#include <vtkTexture.h>

namespace quick {

    namespace Vtk {

        class Texture : public ImageAlgorithm {
            Q_OBJECT
        public:
            enum Quality {
                QualityDefault = VTK_TEXTURE_QUALITY_DEFAULT,
                Quality16Bit = VTK_TEXTURE_QUALITY_16BIT,
                Quality32Bit = VTK_TEXTURE_QUALITY_32BIT
            };
            enum BlendingMode {
                BlendingNone =  vtkTexture::VTK_TEXTURE_BLENDING_MODE_NONE,
                BlendingReplace = vtkTexture::VTK_TEXTURE_BLENDING_MODE_REPLACE,
                BlendingModulate = vtkTexture::VTK_TEXTURE_BLENDING_MODE_MODULATE,
                BlendingAdd = vtkTexture::VTK_TEXTURE_BLENDING_MODE_ADD,
                BlendingAddSigned = vtkTexture::VTK_TEXTURE_BLENDING_MODE_ADD_SIGNED,
                BlendingInterpolate = vtkTexture::VTK_TEXTURE_BLENDING_MODE_INTERPOLATE,
                BlendingSubtract = vtkTexture::VTK_TEXTURE_BLENDING_MODE_SUBTRACT
            };
        private:
            Q_ENUM(Quality);
            Q_ENUM(BlendingMode);
            Q_PROPERTY(BlendingMode blendingMode READ getBlendingMode WRITE setBlendingMode NOTIFY blendingModeChanged);
            Q_PROPERTY(Quality quality READ getQuality WRITE setQuality NOTIFY qualityChanged);
            Q_PROPERTY(bool repeat READ getRepeat WRITE setRepeat NOTIFY repeatChanged);
            Q_PROPERTY(bool edgeClamp READ getEdgeClamp WRITE setEdgeClamp NOTIFY edgeClampChanged);
            Q_PROPERTY(bool interpolate READ getInterpolate WRITE setInterpolate NOTIFY interpolateChanged);
        private:
            using cb_t = std::function<void()>;
            static Qml::Register::UncreatableClass<Texture> Register;
            vtkSmartPointer<vtkTexture> m_vtkObject;
            cb_t m_callback;
        public:
            Texture() = delete;
            Texture(vtkSmartPointer<vtkTexture>, cb_t&&);
            auto setQuality(Quality) -> void;
            auto getQuality() -> Quality;
            auto setBlendingMode(BlendingMode) -> void;
            auto getBlendingMode() -> BlendingMode;
            auto setRepeat(bool) -> void;
            auto getRepeat() -> bool;
            auto setEdgeClamp(bool) -> void;
            auto getEdgeClamp() -> bool;
            auto setInterpolate(bool) -> void;
            auto getInterpolate() -> bool;
        signals:
            void blendingModeChanged();
            void qualityChanged();
            void repeatChanged();
            void edgeClampChanged();
            void interpolateChanged();
        };
    }
}