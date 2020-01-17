#include "quickVtkPerlinNoise.hpp"

namespace quick {
    namespace Vtk {

        Qml::Register::Class<PerlinNoise> PerlinNoise::Register(true);

        PerlinNoise::PerlinNoise() : ImplicitFunction(vtkSmartPointer<vtkPerlinNoise>::New()) {
            this->m_vtkObject = vtkPerlinNoise::SafeDownCast(ImplicitFunction::getVtkObject());

            this->m_frequency = new Math::Vector3([this](){
                this->m_vtkObject->SetFrequency(this->m_frequency->getValues().data());
                this->update();
            });

            this->m_phase = new Math::Vector3([this](){
                this->m_vtkObject->SetPhase(this->m_phase->getValues().data());
                this->update();
            });
        }

        auto PerlinNoise::setAmplitude(qreal amplitude) -> void {
            this->m_vtkObject->SetAmplitude(amplitude);
            this->update();
        }

        auto PerlinNoise::getAmplitude() -> qreal {
            return this->m_vtkObject->GetAmplitude();
        }

        auto PerlinNoise::getFrequency() -> Math::Vector3* {
            return this->m_frequency;
        }

        auto PerlinNoise::getPhase() -> Math::Vector3* {
            return this->m_phase;
        }
    }
}
