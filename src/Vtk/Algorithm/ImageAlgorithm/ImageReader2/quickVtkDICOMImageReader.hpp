#pragma once

#include "quickVtkImageReader2.hpp"

#include <vtkDICOMImageReader.h>

namespace quick {

    namespace Vtk {

        class DICOMImageReader : public ImageReader2 {
            Q_OBJECT
        private:
            static Qml::Register::Class<DICOMImageReader> Register;
            vtkSmartPointer<vtkDICOMImageReader> m_vtkDICOMImageReader;
        public:
            auto getSuffix() -> QString override;
            DICOMImageReader();
        };
    }
}