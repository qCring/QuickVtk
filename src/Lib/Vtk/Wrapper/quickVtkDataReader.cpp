#include "quickVtkDataReader.hpp"

namespace quick {

    namespace Vtk {

        Qml::Register::Symbol::AbstractClass<DataReader> DataReader::Register(true);

        DataReader::DataReader(vtkSmartPointer<vtkDataReader> vtkObject) : Algorithm(vtkObject) {
            this->m_vtkObject = vtkObject;
        }

        auto DataReader::setFileName(const QString& fileName) -> void {
            this->m_vtkObject->SetFileName(fileName.toStdString().c_str());
            this->m_vtkObject->Update();
            this->update();

            emit this->fileNameChanged();
        }

        auto DataReader::getFileName() -> QString {
            return this->m_vtkObject->GetFileName();
        }
    }
}
