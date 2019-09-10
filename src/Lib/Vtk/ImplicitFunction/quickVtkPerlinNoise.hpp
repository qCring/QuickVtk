#pragma once

#include "quickMathVector3.hpp"
#include "quickVtkImplicitFunction.hpp"

#include <vtkPerlinNoise.h>

namespace quick {

    namespace Vtk {

        class PerlinNoise : public ImplicitFunction {
            Q_OBJECT
            Q_PROPERTY(qreal amplitude READ getAmplitude WRITE setAmplitude NOTIFY amplitudeChanged);
            Q_PROPERTY(quick::Math::Vector3* frequency READ getFrequency CONSTANT);
            Q_PROPERTY(quick::Math::Vector3* phase READ getPhase CONSTANT);
        private:
            static Qml::Register::Symbol::Class<PerlinNoise> Register;
            vtkSmartPointer<vtkPerlinNoise> m_vtkObject = nullptr;
            Math::Vector3* m_frequency = nullptr;
            Math::Vector3* m_phase = nullptr;
        public:
            PerlinNoise();
            auto setAmplitude(qreal) -> void;
            auto getAmplitude() -> qreal;
            auto getFrequency() -> Math::Vector3*;
            auto getPhase() -> Math::Vector3*;
        signals:
            void amplitudeChanged();
        };
    }
}
