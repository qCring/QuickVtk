#include "quickVtkDataReader.hpp"

namespace quick {

    namespace Vtk {

        Qml::Register::AbstractClass<DataReader> DataReader::Register;

        DataReader::DataReader() : Algorithm(this) {
            this->m_vtkDataReader    = 0;
        }

        DataReader::DataReader(DataReader* other) : Algorithm(this) {
        }

        auto DataReader::setVtkDataReader(vtkSmartPointer<vtkDataReader> vtkDataReader) -> void {
            this->m_vtkDataReader = vtkDataReader;
            Algorithm::setVtkAlgorithm(vtkDataReader);
        }

        auto DataReader::getVtkDataReader() -> vtkSmartPointer<vtkDataReader> {
            return this->m_vtkDataReader;
        }

        auto DataReader::setFileName(const QString& fileName) -> void {
            this->m_vtkDataReader->SetFileName(fileName.toStdString().c_str());
            this->m_vtkDataReader->Update();
            this->update();

            emit this->fileNameChanged();
        }

        auto DataReader::getFileName() -> QString {
            return this->m_vtkDataReader->GetFileName();
        }

        DataReader::~DataReader() {
        }
    }
}