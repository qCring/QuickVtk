#pragma once

#include "quickVtkPolyDataAlgorithm.hpp"

#include <vtkPolyDataNormals.h>

namespace quick {

    namespace Vtk {

        class PolyDataNormals : public PolyDataAlgorithm {
            Q_OBJECT
            Q_PROPERTY(qreal featureAngle READ getFeatureAngle WRITE setFeatureAngle NOTIFY featureAngleChanged);
            Q_PROPERTY(bool splitting READ getSplitting WRITE setSplitting NOTIFY splittingChanged);
            Q_PROPERTY(bool consistency READ getConsistency WRITE setConsistency NOTIFY consistencyChanged);
            Q_PROPERTY(bool autoOrientNormals READ getAutoOrientNormals WRITE setAutoOrientNormals NOTIFY autoOrientNormalsChanged);
            Q_PROPERTY(bool computePointNormals READ getComputePointNormals WRITE setComputePointNormals NOTIFY computePointNormalsChanged);
            Q_PROPERTY(bool computeCellNormals READ getComputeCellNormals WRITE setComputeCellNormals NOTIFY computeCellNormalsChanged);
            Q_PROPERTY(bool flipNormals READ getFlipNormals WRITE setFlipNormals NOTIFY flipNormalsChanged);
            Q_PROPERTY(bool nonManifoldTraversal READ getNonManifoldTraversal WRITE setNonManifoldTraversal NOTIFY nonManifoldTraversalChanged);
        private:
            static Qml::Register::Class<PolyDataNormals> Register;
            vtkSmartPointer<vtkPolyDataNormals> m_vtkObject;
        public:
            PolyDataNormals();
            auto setFeatureAngle(qreal) -> void;
            auto getFeatureAngle() -> qreal;
            auto setSplitting(bool) -> void;
            auto getSplitting() -> bool;
            auto setConsistency(bool) -> void;
            auto getConsistency() -> bool;
            auto setAutoOrientNormals(bool) -> void;
            auto getAutoOrientNormals() -> bool;
            auto setComputePointNormals(bool) -> void;
            auto getComputePointNormals() -> bool;
            auto setComputeCellNormals(bool) -> void;
            auto getComputeCellNormals() -> bool;
            auto setFlipNormals(bool) -> void;
            auto getFlipNormals() -> bool;
            auto setNonManifoldTraversal(bool) -> void;
            auto getNonManifoldTraversal() -> bool;
        signals:
            void featureAngleChanged();
            void splittingChanged();
            void consistencyChanged();
            void autoOrientNormalsChanged();
            void computePointNormalsChanged();
            void computeCellNormalsChanged();
            void flipNormalsChanged();
            void nonManifoldTraversalChanged();
        };
    }
}
