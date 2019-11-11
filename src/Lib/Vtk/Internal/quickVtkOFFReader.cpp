#include "quickVtkOFFReader.hpp"

#include "quickIO.hpp"

namespace quick {

    namespace Vtk {

        Qml::Register::Class<OFFReader> OFFReader::Register;

        OFFReader::OFFReader() : quick::Vtk::PolyDataAlgorithm(vtkSmartPointer<vtkOFFReader>::New()) {
            this->m_vtkObject = vtkOFFReader::SafeDownCast(getVtkObject());
        }

        auto OFFReader::setFileName(const QString& fileName) -> void {
            this->m_fileName = fileName;

            emit this->fileNameChanged();

            if (IO::FileExists(fileName)) {
                this->m_vtkObject->SetFileName(fileName.toStdString().c_str());
                this->m_vtkObject->Update();
                this->update();
            }
        }

        auto OFFReader::getFileName() -> QString {
            return this->m_fileName;
        }
    }
}
