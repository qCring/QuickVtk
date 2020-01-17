#include "quickVtkAbstractPolyDataReader.hpp"
#include "quickIO.hpp"

namespace quick {
    namespace Vtk {

        Qml::Register::AbstractClass<AbstractPolyDataReader> AbstractPolyDataReader::Register(true);

        AbstractPolyDataReader::AbstractPolyDataReader(vtkSmartPointer<vtkAbstractPolyDataReader> vtkObject) : PolyDataAlgorithm(vtkObject) {
            this->m_vtkObject = vtkObject;
        }
        
        auto AbstractPolyDataReader::isValid() -> bool {
            if (!IO::FileExists(this->m_fileName)) {
                return false;
            }

            return true;
        }

        auto AbstractPolyDataReader::setFileName(const QString& fileName) -> void {
            this->m_fileName = fileName;

            emit this->fileNameChanged();

            if (IO::FileExists(fileName)) {
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
