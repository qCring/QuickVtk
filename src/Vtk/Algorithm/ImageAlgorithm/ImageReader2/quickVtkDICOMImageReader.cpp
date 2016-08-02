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

        auto DICOMImageReader::setDirectoryName(const QString& directoryName) -> void {
            this->m_directoryName = directoryName;
            emit this->directoryNameChanged();
            this->m_vtkDICOMImageReader->SetDirectoryName(directoryName.toStdString().c_str());
            this->m_vtkDICOMImageReader->Update();
            this->update();
        }

        auto DICOMImageReader::getDirectoryName() -> QString {
            return this->m_directoryName;
        }
    }
}