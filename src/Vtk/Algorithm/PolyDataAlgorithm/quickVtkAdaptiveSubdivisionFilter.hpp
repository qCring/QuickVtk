#pragma once

#include "quickVtkPolyDataAlgorithm.hpp"

#include <vtkAdaptiveSubdivisionFilter.h>

namespace quick {

    namespace Vtk {

        class AdaptiveSubdivisionFilter : public PolyDataAlgorithm {
            Q_OBJECT
            Q_PROPERTY(float maximumEdgeLength READ getMaximumEdgeLength WRITE setMaximumEdgeLength NOTIFY maximumEdgeLengthChanged);
            Q_PROPERTY(float maximumTriangleArea READ getMaximumTriangleArea WRITE setMaximumTriangleArea NOTIFY maximumTriangleAreaChanged);
            Q_PROPERTY(int maximumNumberOfTriangles READ getMaximumNumberOfTriangles WRITE setMaximumNumberOfTriangles NOTIFY maximumNumberOfTrianglesChanged);
            Q_PROPERTY(int maximumNumberOfPasses READ getMaximumNumberOfPasses WRITE setMaximumNumberOfPasses NOTIFY maximumNumberOfPassesChanged);
        private:
            static Qml::Register::Class<AdaptiveSubdivisionFilter> Register;
            vtkSmartPointer<vtkAdaptiveSubdivisionFilter> m_vtkObject;
        public:
            AdaptiveSubdivisionFilter();
            auto setMaximumEdgeLength(float) -> void;
            auto getMaximumEdgeLength() -> float;
            auto setMaximumTriangleArea(float) -> void;
            auto getMaximumTriangleArea() -> float;
            auto setMaximumNumberOfTriangles(int) -> void;
            auto getMaximumNumberOfTriangles() -> int;
            auto setMaximumNumberOfPasses(int) -> void;
            auto getMaximumNumberOfPasses() -> int;
        signals:
            void maximumEdgeLengthChanged();
            void maximumTriangleAreaChanged();
            void maximumNumberOfTrianglesChanged();
            void maximumNumberOfPassesChanged();
        };
    }
}
