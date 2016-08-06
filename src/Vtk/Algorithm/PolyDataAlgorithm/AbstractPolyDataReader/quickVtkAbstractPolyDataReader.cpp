#include "quickVtkAbstractPolyDataReader.hpp"
#include "quickNotifications.hpp"
#include "quickUtilIO.hpp"

namespace quick {

    namespace Vtk {
        Qml::Register::AbstractClass<AbstractPolyDataReader> AbstractPolyDataReader::Register;

        AbstractPolyDataReader::AbstractPolyDataReader(vtkSmartPointer<vtkAbstractPolyDataReader> vtkObject) : PolyDataAlgorithm(vtkObject) {
            this->m_vtkObject = vtkObject;
        }
        
        auto AbstractPolyDataReader::isValid() -> bool {
            if (!Util::IO::FileExists(this->m_fileName)) {
                Notifications::instance->addWarning("No fileName specified for AbstractPolyDataReader!");
                return false;
            }

            return true;
        }

        auto AbstractPolyDataReader::setFileName(QString& fileName) -> void {
            this->m_fileName = fileName;

            emit this->fileNameChanged();

            if (Util::IO::FileExists(fileName))
            {
                this->m_vtkObject->SetFileName(fileName.toStdString().c_str());
                this->m_vtkObject->Update();
                this->update();
            }
        }

        auto AbstractPolyDataReader::getFileName() -> QString {
            return this->m_fileName;
        }
    }
}
