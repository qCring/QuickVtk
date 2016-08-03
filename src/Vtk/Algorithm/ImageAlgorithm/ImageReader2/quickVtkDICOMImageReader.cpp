#include "quickVtkDICOMImageReader.hpp"

namespace quick {

    namespace Vtk {

        Qml::Register::Class<DICOMImageReader> DICOMImageReader::Register;

        DICOMImageReader::DICOMImageReader() : ImageReader2(vtkSmartPointer<vtkDICOMImageReader>::New()) {
            this->m_vtkObject = vtkDICOMImageReader::SafeDownCast(Algorithm::getVtkObject());
        }

        auto DICOMImageReader::getSuffix() -> QString {
            return ".dcm";
        }

        auto DICOMImageReader::setDirectoryName(const QString& directoryName) -> void {
            this->m_directoryName = directoryName;
            emit this->directoryNameChanged();
            this->m_vtkObject->SetDirectoryName(directoryName.toStdString().c_str());
            this->m_vtkObject->Update();
            this->update();
        }

        auto DICOMImageReader::getDirectoryName() -> QString {
            return this->m_directoryName;
        }
    }
}