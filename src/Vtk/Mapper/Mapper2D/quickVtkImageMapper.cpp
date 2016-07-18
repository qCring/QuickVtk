#include "quickVtkImageMapper.hpp"

namespace quick {

    namespace Vtk {

        Qml::Register::Class<ImageMapper> ImageMapper::Register;

        ImageMapper::ImageMapper() {
            this->m_vtkImageMapper = vtkSmartPointer<vtkImageMapper>::New();
            Mapper2D::setVtkMapper2D(this->m_vtkImageMapper);
        }

        auto ImageMapper::getVtkImageMapper() -> vtkSmartPointer<vtkImageMapper> {
            return this->m_vtkImageMapper;
        }

        auto ImageMapper::setColorWindow(float colorWindow) -> void {
            this->m_vtkImageMapper->SetColorWindow(colorWindow);
            emit this->colorWindowChanged();
            emit this->colorScaleChanged();
            emit this->colorShiftChanged();

            this->update();
        }

        auto ImageMapper::getColorWindow() -> float {
            return this->m_vtkImageMapper->GetColorWindow();
        }

        auto ImageMapper::setColorLevel(float colorLevel) -> void {
            this->m_vtkImageMapper->SetColorLevel(colorLevel);
            emit this->colorLevelChanged();
            emit this->colorScaleChanged();
            emit this->colorShiftChanged();

            this->update();
        }

        auto ImageMapper::getColorLevel() -> float {
            return this->m_vtkImageMapper->GetColorLevel();
        }

        auto ImageMapper::getColorShift() -> float {
            return this->m_vtkImageMapper->GetColorShift();
        }

        auto ImageMapper::getColorScale() -> float {
            return this->m_vtkImageMapper->GetColorScale();
        }
    }
}