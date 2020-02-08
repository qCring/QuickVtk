#pragma once

#include "quickVtkPolyDataAlgorithm.hpp"

#include <vtkExtractSurface.h>

namespace quick::Vtk {

    class ExtractSurface : public PolyDataAlgorithm {
        Q_OBJECT
        Q_PROPERTY(qreal radius READ getRadius WRITE setRadius NOTIFY radiusChanged);
        Q_PROPERTY(bool holeFilling READ getHoleFilling WRITE setHoleFilling NOTIFY holeFillingChanged);
        Q_PROPERTY(bool computeNormals READ getComputeNormals WRITE setComputeNormals NOTIFY computeNormalsChanged);
        Q_PROPERTY(bool computeGradients READ getComputeGradients WRITE setComputeGradients NOTIFY computeGradientsChanged);
    private:
        static Qml::Register::Class<ExtractSurface> Register;
        vtkSmartPointer<vtkExtractSurface> m_vtkObject = nullptr;
    public:
        ExtractSurface();
        auto setRadius(qreal) -> void;
        auto getRadius() -> qreal;
        auto setHoleFilling(bool) -> void;
        auto getHoleFilling() -> bool;
        auto setComputeNormals(bool) -> void;
        auto getComputeNormals() -> bool;
        auto setComputeGradients(bool) -> void;
        auto getComputeGradients() -> bool;
    signals:
        void radiusChanged();
        void holeFillingChanged();
        void computeNormalsChanged();
        void computeGradientsChanged();
    };
}
