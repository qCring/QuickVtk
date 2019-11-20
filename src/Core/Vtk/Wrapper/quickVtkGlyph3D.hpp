#pragma once

#include "quickVtkPolyDataAlgorithm.hpp"
#include "quickMathVector2.hpp"

#include <vtkGlyph3D.h>

namespace quick {

    namespace Vtk {

        class Glyph3D : public PolyDataAlgorithm {
            Q_OBJECT
        public:
            enum ScaleMode {
                ScaleByScalar = VTK_SCALE_BY_SCALAR,
                ScaleByVector = VTK_SCALE_BY_VECTOR,
                ScaleByVectorComponents = VTK_SCALE_BY_VECTORCOMPONENTS,
                DataScalingOff = VTK_DATA_SCALING_OFF
            };
            enum ColorMode {
                ColorByScale = VTK_COLOR_BY_SCALE,
                ColorByScalar = VTK_COLOR_BY_SCALAR,
                ColorByVector = VTK_COLOR_BY_VECTOR
            };
            enum IndexMode {
                IndexingOff = VTK_INDEXING_OFF,
                IndexingByScalar = VTK_INDEXING_BY_SCALAR,
                IndexingByVector = VTK_INDEXING_BY_VECTOR
            };
            enum VectorMode {
                UseVector = VTK_USE_VECTOR,
                UseNormal = VTK_USE_NORMAL,
                VectorRotationOff = VTK_VECTOR_ROTATION_OFF
            };
        private:
            Q_ENUM(ScaleMode);
            Q_ENUM(ColorMode);
            Q_ENUM(IndexMode);
            Q_ENUM(VectorMode);
            Q_PROPERTY(quick::Math::Vector2* range READ getRange CONSTANT);
            Q_PROPERTY(ScaleMode scaleMode READ getScaleMode WRITE setScaleMode NOTIFY scaleModeChanged);
            Q_PROPERTY(ColorMode colorMode READ getColorMode WRITE setColorMode NOTIFY colorModeChanged);
            Q_PROPERTY(IndexMode indexMode READ getIndexMode WRITE setIndexMode NOTIFY indexModeChanged);
            Q_PROPERTY(VectorMode vectorMode READ getVectorMode WRITE setVectorMode NOTIFY vectorModeChanged);
            Q_PROPERTY(qreal scaleFactor READ getScaleFactor WRITE setScaleFactor NOTIFY scaleFactorChanged);
            Q_PROPERTY(bool orient READ getOrient WRITE setOrient NOTIFY orientChanged);
            Q_PROPERTY(bool scaling READ getScaling WRITE setScaling NOTIFY scalingChanged);
            Q_PROPERTY(bool clamping READ getClamping WRITE setClamping NOTIFY clampingChanged);
            Q_PROPERTY(bool fillCellData READ getFillCellData WRITE setFillCellData NOTIFY fillCellDataChanged);
            Q_PROPERTY(bool generatePointIds READ getGeneratePointIds WRITE setGeneratePointIds NOTIFY generatePointIdsChanged);
        private:
            static Qml::Register::Class<Glyph3D> Register;
            vtkSmartPointer<vtkGlyph3D> m_vtkObject = nullptr;
            Math::Vector2* m_range = nullptr;
        private:
            auto updateRange(Math::Vector2&&) -> void;
        public:
            Glyph3D();
            auto setScaleMode(ScaleMode) -> void;
            auto getScaleMode() -> ScaleMode;
            auto setColorMode(ColorMode) -> void;
            auto getColorMode() -> ColorMode;
            auto setIndexMode(IndexMode) -> void;
            auto getIndexMode() -> IndexMode;
            auto setVectorMode(VectorMode) -> void;
            auto getVectorMode() -> VectorMode;
            auto setScaleFactor(qreal) -> void;
            auto getScaleFactor() -> qreal;
            auto getRange() -> Math::Vector2*;
            auto setOrient(bool) -> void;
            auto getOrient() -> bool;
            auto setClamping(bool) -> void;
            auto getClamping() -> bool;
            auto setScaling(bool) -> void;
            auto getScaling() -> bool;
            auto setFillCellData(bool) -> void;
            auto getFillCellData() -> bool;
            auto setGeneratePointIds(bool) -> void;
            auto getGeneratePointIds() -> bool;
        signals:
            void scaleModeChanged();
            void colorModeChanged();
            void indexModeChanged();
            void vectorModeChanged();
            void scaleFactorChanged();
            void orientChanged();
            void scalingChanged();
            void clampingChanged();
            void fillCellDataChanged();
            void generatePointIdsChanged();
        };
    }
}
