#include "quickVtkDICOMImageReader.hpp"

namespace quick {

    namespace Vtk {

        Qml::Register::Class<DICOMImageReader> DICOMImageReader::Register;

        DICOMImageReader::DICOMImageReader() : ImageReader2(this) {
            this->m_vtkDICOMImageReader = vtkSmartPointer<vtkDICOMImageReader>::New();
            this->setVtkImageReader2(this->m_vtkDICOMImageReader);
        }

        auto DICOMImageReader::getSuffix() -> QString {
            return ".dcm";
        }
    }
}