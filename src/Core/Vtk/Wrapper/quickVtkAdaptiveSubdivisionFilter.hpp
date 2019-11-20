#pragma once

#include "quickVtkPolyDataAlgorithm.hpp"

#include <vtkAdaptiveSubdivisionFilter.h>

namespace quick {

    namespace Vtk {

        class AdaptiveSubdivisionFilter : public PolyDataAlgorithm {
            Q_OBJECT
            Q_PROPERTY(qreal maximumEdgeLength READ getMaximumEdgeLength WRITE setMaximumEdgeLength NOTIFY maximumEdgeLengthChanged);
            Q_PROPERTY(qreal maximumTriangleArea READ getMaximumTriangleArea WRITE setMaximumTriangleArea NOTIFY maximumTriangleAreaChanged);
            Q_PROPERTY(int maximumNumberOfTriangles READ getMaximumNumberOfTriangles WRITE setMaximumNumberOfTriangles NOTIFY maximumNumberOfTrianglesChanged);
            Q_PROPERTY(int maximumNumberOfPasses READ getMaximumNumberOfPasses WRITE setMaximumNumberOfPasses NOTIFY maximumNumberOfPassesChanged);
        private:
            static Qml::Register::Class<AdaptiveSubdivisionFilter> Register;
            vtkSmartPointer<vtkAdaptiveSubdivisionFilter> m_vtkObject = nullptr;
        public:
            AdaptiveSubdivisionFilter();
            auto setMaximumEdgeLength(qreal) -> void;
            auto getMaximumEdgeLength() -> qreal;
            auto setMaximumTriangleArea(qreal) -> void;
            auto getMaximumTriangleArea() -> qreal;
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
