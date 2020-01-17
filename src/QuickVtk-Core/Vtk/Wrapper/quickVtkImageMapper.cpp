#include "quickVtkImageMapper.hpp"

namespace quick {
    namespace Vtk {

        Qml::Register::Class<ImageMapper> ImageMapper::Register(true);

        ImageMapper::ImageMapper() : Mapper2D(vtkSmartPointer<vtkImageMapper>::New()) {
            this->m_vtkObject = vtkImageMapper::SafeDownCast(Algorithm::getVtkObject());
        }

        auto ImageMapper::setColorWindow(qreal colorWindow) -> void {
            this->m_vtkObject->SetColorWindow(colorWindow);
            emit this->colorWindowChanged();
            emit this->colorScaleChanged();
            emit this->colorShiftChanged();

            this->update();
        }

        auto ImageMapper::getColorWindow() -> qreal {
            return this->m_vtkObject->GetColorWindow();
        }

        auto ImageMapper::setColorLevel(qreal colorLevel) -> void {
            this->m_vtkObject->SetColorLevel(colorLevel);
            emit this->colorLevelChanged();
            emit this->colorScaleChanged();
            emit this->colorShiftChanged();

            this->update();
        }

        auto ImageMapper::getColorLevel() -> qreal {
            return this->m_vtkObject->GetColorLevel();
        }

        auto ImageMapper::getColorShift() -> qreal {
            return this->m_vtkObject->GetColorShift();
        }

        auto ImageMapper::getColorScale() -> qreal {
            return this->m_vtkObject->GetColorScale();
        }
    }
}
