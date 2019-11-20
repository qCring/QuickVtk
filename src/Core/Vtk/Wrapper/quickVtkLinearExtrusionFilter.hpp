#pragma once

#include "quickVtkPolyDataAlgorithm.hpp"
#include "quickMathVector3.hpp"

#include <vtkLinearExtrusionFilter.h>

namespace quick {

    namespace Vtk {

        class LinearExtrusionFilter : public PolyDataAlgorithm {
            Q_OBJECT
        public:
            enum ExtrusionType
            {
                VectorExtrusion = VTK_VECTOR_EXTRUSION,
                NormalExtrusion = VTK_NORMAL_EXTRUSION,
                PointExtrusion = VTK_POINT_EXTRUSION
            };
        private:
            Q_ENUM(ExtrusionType);
            Q_PROPERTY(quick::Math::Vector3* vector READ getVector CONSTANT);
            Q_PROPERTY(quick::Math::Vector3* extrusionPoint READ getExtrusionPoint CONSTANT);
            Q_PROPERTY(ExtrusionType extrusionType READ getExtrusionType WRITE setExtrusionType NOTIFY extrusionTypeChanged);
            Q_PROPERTY(qreal scaleFactor READ getScaleFactor WRITE setScaleFactor NOTIFY scaleFactorChanged);
            Q_PROPERTY(bool capping READ getCapping WRITE setCapping NOTIFY cappingChanged);
        private:
            static Qml::Register::Class<LinearExtrusionFilter> Register;
            vtkSmartPointer<vtkLinearExtrusionFilter> m_vtkObject = nullptr;
            Math::Vector3* m_extrusionPoint = nullptr;
            Math::Vector3* m_vector = nullptr;
        public:
            LinearExtrusionFilter();
            auto setExtrusionType(ExtrusionType) -> void;
            auto getExtrusionType() -> ExtrusionType;
            auto setScaleFactor(qreal) -> void;
            auto getScaleFactor() -> qreal;
            auto setCapping(bool) -> void;
            auto getCapping() -> bool;
            auto getVector() -> Math::Vector3*;
            auto getExtrusionPoint() -> Math::Vector3*;
        signals:
            void extrusionTypeChanged();
            void scaleFactorChanged();
            void cappingChanged();
        };
    }
}
