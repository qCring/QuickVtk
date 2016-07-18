#pragma once

#include "quickVtkAlgorithm.hpp"

#include <vtkImageAlgorithm.h>

namespace quick {

    namespace Vtk {

        class ImageAlgorithm : public Algorithm {
            Q_OBJECT
        private:
            static Qml::Register::AbstractClass<ImageAlgorithm> Register;
            vtkSmartPointer<vtkImageAlgorithm> m_vtkImageAlgorithm;
        public:
            ImageAlgorithm();
            ImageAlgorithm(ImageAlgorithm*);
            auto setVtkImageAlgorithm(vtkSmartPointer<vtkImageAlgorithm>) -> void;
            auto getVtkImageAlgorithm() -> vtkSmartPointer<vtkImageAlgorithm>;
            ~ImageAlgorithm();
        };
    }
}