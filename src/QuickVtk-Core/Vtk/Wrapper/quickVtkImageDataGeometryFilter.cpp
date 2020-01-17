#include "quickVtkImageDataGeometryFilter.hpp"

namespace quick {
    namespace Vtk {

        Qml::Register::Class<ImageDataGeometryFilter> ImageDataGeometryFilter::Register(true);

        ImageDataGeometryFilter::ImageDataGeometryFilter() : PolyDataAlgorithm(vtkSmartPointer<vtkImageDataGeometryFilter>::New()) {
            this->m_vtkObject = vtkImageDataGeometryFilter::SafeDownCast(Algorithm::getVtkObject());
        }
    }
}
