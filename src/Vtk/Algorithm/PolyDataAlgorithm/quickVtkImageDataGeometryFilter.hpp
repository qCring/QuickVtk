#pragma once

#include "quickVtkPolyDataAlgorithm.hpp"

#include <vtkImageDataGeometryFilter.h>

namespace quick {

    namespace Vtk {

        class ImageDataGeometryFilter : public PolyDataAlgorithm {
            Q_OBJECT
        private:
            static Qml::Register::Class<ImageDataGeometryFilter> Register;
            vtkSmartPointer<vtkImageDataGeometryFilter> m_vtkObject;
        public:
            ImageDataGeometryFilter();
        signals:
        };
    }
}
