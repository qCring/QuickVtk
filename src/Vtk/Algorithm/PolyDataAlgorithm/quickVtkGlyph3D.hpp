#pragma once

#include "quickVtkPolyDataAlgorithm.hpp"
#include "quickMathVector2.hpp"

#include <vtkGlyph3D.h>

namespace quick {

    namespace Vtk {

        class Glyph3D : public PolyDataAlgorithm {
            Q_OBJECT
            Q_ENUMS(ScaleMode);
            Q_ENUMS(ColorMode);
            Q_PROPERTY(quick::Math::Vector2* range READ getRange WRITE setRange NOTIFY rangeChanged);
            Q_PROPERTY(ScaleMode scaleMode READ getScaleMode WRITE setScaleMode NOTIFY scaleModeChanged);
            Q_PROPERTY(ColorMode colorMode READ getColorMode WRITE setColorMode NOTIFY colorModeChanged);
            Q_PROPERTY(double scaleFactor READ getScaleFactor WRITE setScaleFactor NOTIFY scaleFactorChanged);
        public:
            enum ScaleMode {
                ScaleByScalar = VTK_SCALE_BY_SCALAR,
                ScaleByVector = VTK_SCALE_BY_VECTOR,
                ScaleByVectorComponents = VTK_SCALE_BY_VECTORCOMPONENTS,
                ScaleOff = VTK_DATA_SCALING_OFF
            };
            enum ColorMode {
                ColorByScale = VTK_COLOR_BY_SCALE,
                ColorByScalar = VTK_COLOR_BY_SCALAR,
                ColorByVector = VTK_COLOR_BY_VECTOR
            };
        private:
            static Qml::Register::Class<Glyph3D> Register;
            vtkSmartPointer<vtkGlyph3D> m_vtkGlyph3D;
            Math::Vector2::cb_t m_rangeCb;
            Math::Vector2* m_range;
        private:
            auto updateRange(Math::Vector2&&) -> void;
        public:
            Glyph3D();
            auto setScaleMode(ScaleMode) -> void;
            auto getScaleMode() -> ScaleMode;
            auto setColorMode(ColorMode) -> void;
            auto getColorMode() -> ColorMode;
            auto setScaleFactor(double) -> void;
            auto getScaleFactor() -> double;
            auto setRange(Math::Vector2*) -> void;
            auto getRange() -> Math::Vector2*;
            ~Glyph3D();
        signals:
            void rangeChanged();
            void scaleModeChanged();
            void colorModeChanged();
            void scaleFactorChanged();
        };
    }
}
