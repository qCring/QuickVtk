#include "quickVtkImageMapper.hpp"

namespace quick {

    namespace Vtk {

        Qml::Register::Symbol::Class<ImageMapper> ImageMapper::Register;

        ImageMapper::ImageMapper() : Mapper2D(vtkSmartPointer<vtkImageMapper>::New()) {
            this->m_vtkObject = vtkImageMapper::SafeDownCast(Algorithm::getVtkObject());
        }

        auto ImageMapper::setColorWindow(float colorWindow) -> void {
            this->m_vtkObject->SetColorWindow(colorWindow);
            emit this->colorWindowChanged();
            emit this->colorScaleChanged();
            emit this->colorShiftChanged();

            this->update();
        }

        auto ImageMapper::getColorWindow() -> float {
            return this->m_vtkObject->GetColorWindow();
        }

        auto ImageMapper::setColorLevel(float colorLevel) -> void {
            this->m_vtkObject->SetColorLevel(colorLevel);
            emit this->colorLevelChanged();
            emit this->colorScaleChanged();
            emit this->colorShiftChanged();

            this->update();
        }

        auto ImageMapper::getColorLevel() -> float {
            return this->m_vtkObject->GetColorLevel();
        }

        auto ImageMapper::getColorShift() -> float {
            return this->m_vtkObject->GetColorShift();
        }

        auto ImageMapper::getColorScale() -> float {
            return this->m_vtkObject->GetColorScale();
        }
    }
}
