#pragma once

#include "quickVtkMapper2D.hpp"

#include <vtkImageMapper.h>

namespace quick {

    namespace Vtk {

        class ImageMapper : public Mapper2D {
            Q_OBJECT
            Q_PROPERTY(qreal colorWindow READ getColorWindow WRITE setColorWindow NOTIFY colorWindowChanged);
            Q_PROPERTY(qreal colorLevel READ getColorLevel WRITE setColorLevel NOTIFY colorLevelChanged);
            Q_PROPERTY(qreal colorShift READ getColorShift NOTIFY colorShiftChanged);
            Q_PROPERTY(qreal colorScale READ getColorScale NOTIFY colorScaleChanged);
        private:
            static Qml::Register::Class<ImageMapper> Register;
            vtkSmartPointer<vtkImageMapper> m_vtkObject;
        public:
            ImageMapper();
            auto setColorWindow(qreal) -> void;
            auto getColorWindow() -> qreal;
            auto setColorLevel(qreal) -> void;
            auto getColorLevel() -> qreal;
            auto getColorShift() -> qreal;
            auto getColorScale() -> qreal;
        signals:
            void colorWindowChanged();
            void colorLevelChanged();
            void colorShiftChanged();
            void colorScaleChanged();
        };
    }
}
