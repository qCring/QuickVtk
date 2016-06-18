#pragma once

#include "quickMathVector.hpp"
#include "quickVtkImplicitFunction.hpp"

#include <vtkPerlinNoise.h>

namespace quick {

    namespace Vtk {

        class PerlinNoise : public ImplicitFunction {
            Q_OBJECT
            Q_PROPERTY(float amplitude READ getAmplitude WRITE setAmplitude NOTIFY amplitudeChanged);
            Q_PROPERTY(quick::Math::Vector* frequency READ getFrequency WRITE setFrequency NOTIFY frequencyChanged);
            Q_PROPERTY(quick::Math::Vector* phase READ getPhase WRITE setPhase NOTIFY phaseChanged);
        private:
            static Qml::Register::Class<PerlinNoise> Register;
            vtkSmartPointer<vtkPerlinNoise> m_vtkPerlinNoise;
            Math::Vector::cb_t m_frequencyCb;
            Math::Vector::cb_t m_phaseCb;
            Math::Vector* m_frequency = nullptr;
            Math::Vector* m_phase = nullptr;
            float m_amplitude;
        private:
            auto updateFrequency(Math::Vector&&) -> void;   
            auto updatePhase(Math::Vector&&) -> void;
        public:
            PerlinNoise();
            auto setVtkPerlinNoise(vtkSmartPointer<vtkPerlinNoise>) -> void;
            auto setAmplitude(float) -> void;
            auto getAmplitude() -> float;
            auto setFrequency(Math::Vector*) -> void;
            auto getFrequency() -> Math::Vector*;
            auto setPhase(Math::Vector*) -> void;
            auto getPhase() -> Math::Vector*;
            auto getVtkPerlinNoise() -> vtkSmartPointer<vtkPerlinNoise> ;
            ~PerlinNoise();
        signals:
            void amplitudeChanged();
            void frequencyChanged();
            void phaseChanged();
        };
    }
}