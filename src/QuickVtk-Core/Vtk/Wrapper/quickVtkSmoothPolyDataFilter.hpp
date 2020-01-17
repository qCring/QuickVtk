#pragma once

#include "quickVtkPolyDataAlgorithm.hpp"

#include <vtkSmoothPolyDataFilter.h>

namespace quick {
    namespace Vtk {

        class SmoothPolyDataFilter : public PolyDataAlgorithm {
            Q_OBJECT
            Q_PROPERTY(qreal convergence READ getConvergence WRITE setConvergence NOTIFY convergenceChanged);
            Q_PROPERTY(int numberOfIterations READ getNumberOfIterations WRITE setNumberOfIterations NOTIFY numberOfIterationsChanged);
            Q_PROPERTY(qreal relaxationFactor READ getRelaxationFactor WRITE setRelaxationFactor NOTIFY relaxationFactorChanged);
            Q_PROPERTY(bool featureEdgeSmoothing READ getFeatureEdgeSmoothing WRITE setFeatureEdgeSmoothing NOTIFY featureEdgeSmoothingChanged);
            Q_PROPERTY(qreal featureAngle READ getFeatureAngle WRITE setFeatureAngle NOTIFY featureAngleChanged);
            Q_PROPERTY(qreal edgeAngle READ getEdgeAngle WRITE setEdgeAngle NOTIFY edgeAngleChanged);
            Q_PROPERTY(bool boundarySmoothing READ getBoundarySmoothing WRITE setBoundarySmoothing NOTIFY boundarySmoothingChanged);
            Q_PROPERTY(bool generateErrorScalars READ getGenerateErrorScalars WRITE setGenerateErrorScalars NOTIFY generateErrorScalarsChanged);
            Q_PROPERTY(bool generateErrorVectors READ getGenerateErrorVectors WRITE setGenerateErrorVectors NOTIFY generateErrorVectorsChanged);
        private:
            static Qml::Register::Class<SmoothPolyDataFilter> Register;
            vtkSmartPointer<vtkSmoothPolyDataFilter> m_vtkObject = nullptr;
        public:
            SmoothPolyDataFilter();
            auto setConvergence(qreal) -> void;
            auto getConvergence() -> qreal;
            auto setNumberOfIterations(int) -> void;
            auto getNumberOfIterations() -> int;
            auto setRelaxationFactor(qreal) -> void;
            auto getRelaxationFactor() -> qreal;
            auto setFeatureEdgeSmoothing(bool) -> void;
            auto getFeatureEdgeSmoothing() -> bool;
            auto setFeatureAngle(qreal) -> void;
            auto getFeatureAngle() -> qreal;
            auto setEdgeAngle(qreal) -> void;
            auto getEdgeAngle() -> qreal;
            auto setBoundarySmoothing(bool) -> void;
            auto getBoundarySmoothing() -> bool;
            auto setGenerateErrorScalars(bool) -> void;
            auto getGenerateErrorScalars() -> bool;
            auto setGenerateErrorVectors(bool) -> void;
            auto getGenerateErrorVectors() -> bool;
        signals:
            void convergenceChanged();
            void numberOfIterationsChanged();
            void relaxationFactorChanged();
            void featureEdgeSmoothingChanged();
            void featureAngleChanged();
            void edgeAngleChanged();
            void boundarySmoothingChanged();
            void generateErrorScalarsChanged();
            void generateErrorVectorsChanged();
        };
    }
}

