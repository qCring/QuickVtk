#include "quickVtkImageAlgorithm.hpp"

namespace quick {

    namespace Vtk {

        Qml::Register::AbstractClass<ImageAlgorithm> ImageAlgorithm::Register;

        ImageAlgorithm::ImageAlgorithm() : Algorithm(this) {
            this->m_vtkImageAlgorithm    = 0;
        }

        ImageAlgorithm::ImageAlgorithm(ImageAlgorithm* other) : Algorithm(this) {
        }

        auto ImageAlgorithm::setVtkImageAlgorithm(vtkSmartPointer<vtkImageAlgorithm> vtkImageAlgorithm) -> void {
            this->m_vtkImageAlgorithm = vtkImageAlgorithm;
            Algorithm::setVtkAlgorithm(vtkImageAlgorithm);
        }

        auto ImageAlgorithm::getVtkImageAlgorithm() -> vtkSmartPointer<vtkImageAlgorithm> {
            return this->m_vtkImageAlgorithm;
        }

        ImageAlgorithm::~ImageAlgorithm() {
        }
    }
}