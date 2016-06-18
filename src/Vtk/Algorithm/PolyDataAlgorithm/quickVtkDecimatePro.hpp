#pragma once

#include "quickVtkPolyDataAlgorithm.hpp"

#include <vtkDecimatePro.h>

namespace quick {

    namespace Vtk {

        class DecimatePro : public PolyDataAlgorithm {
            Q_OBJECT
            Q_PROPERTY(float splitAngle READ getSplitAngle WRITE setSplitAngle NOTIFY splitAngleChanged);
            Q_PROPERTY(float featureAngle READ getFeatureAngle WRITE setFeatureAngle NOTIFY featureAngleChanged);
            Q_PROPERTY(float targetReduction READ getTargetReduction WRITE setTargetReduction NOTIFY targetReductionChanged);
            Q_PROPERTY(bool preserveTopology READ getPreserveTopology WRITE setPreserveTopology NOTIFY preserveTopologyChanged);
            Q_PROPERTY(bool splitting READ getSplitting WRITE setSplitting NOTIFY splittingChanged);
            Q_PROPERTY(bool preSplitMesh READ getPreSplitMesh WRITE setPreSplitMesh NOTIFY preSplitMeshChanged);
            Q_PROPERTY(int degree READ getDegree WRITE setDegree NOTIFY degreeChanged);
        private:
            static Qml::Register::Class<DecimatePro> Register;
            vtkSmartPointer<vtkDecimatePro> m_vtkDecimatePro;
        public:
            DecimatePro();
            auto setDegree(int) -> void;
            auto getDegree() -> int;
            auto setSplitting(bool) -> void;
            auto getSplitting() -> bool;
            auto setSplitAngle(float) -> void;
            auto getSplitAngle() -> float;
            auto setFeatureAngle(float) -> void;
            auto getFeatureAngle() -> float;
            auto setPreSplitMesh(bool) -> void;
            auto getPreSplitMesh() -> bool;
            auto setTargetReduction(float) -> void;
            auto getTargetReduction() -> float;
            auto setPreserveTopology(bool) -> void;
            auto getPreserveTopology() ->bool;
            ~DecimatePro();
        signals:
            void degreeChanged();
            void splittingChanged();
            void splitAngleChanged();
            void preSplitMeshChanged();
            void featureAngleChanged();
            void targetReductionChanged();
            void preserveTopologyChanged();
        };
    }
}
