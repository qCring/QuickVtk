#pragma once

#include "quickMathVector3.hpp"
#include "quickVtkImplicitFunction.hpp"

#include <vtkPerlinNoise.h>

namespace quick {

    namespace Vtk {

        class PerlinNoise : public ImplicitFunction {
            Q_OBJECT
            Q_PROPERTY(float amplitude READ getAmplitude WRITE setAmplitude NOTIFY amplitudeChanged);
            Q_PROPERTY(quick::Math::Vector3* frequency READ getFrequency WRITE setFrequency NOTIFY frequencyChanged);
            Q_PROPERTY(quick::Math::Vector3* phase READ getPhase WRITE setPhase NOTIFY phaseChanged);
        private:
            static Qml::Register::Class<PerlinNoise> Register;
            vtkSmartPointer<vtkPerlinNoise> m_vtkObject = nullptr;
            Math::Vector3::cb_t m_frequencyCb;
            Math::Vector3::cb_t m_phaseCb;
            Math::Vector3* m_frequency = nullptr;
            Math::Vector3* m_phase = nullptr;
            float m_amplitude;
        private:
            auto updateFrequency(Math::Vector3&&) -> void;   
            auto updatePhase(Math::Vector3&&) -> void;
        public:
            PerlinNoise();
            auto setAmplitude(float) -> void;
            auto getAmplitude() -> float;
            auto setFrequency(Math::Vector3*) -> void;
            auto getFrequency() -> Math::Vector3*;
            auto setPhase(Math::Vector3*) -> void;
            auto getPhase() -> Math::Vector3*;
            ~PerlinNoise();
        signals:
            void amplitudeChanged();
            void frequencyChanged();
            void phaseChanged();
        };
    }
}