#include "quickVtkAbstractPolyDataReader.hpp"
#include "quickNotifications.hpp"
#include "quickUtilIO.hpp"

namespace quick {

    namespace Vtk {
        Qml::Register::AbstractClass<AbstractPolyDataReader> AbstractPolyDataReader::Register;

        AbstractPolyDataReader::AbstractPolyDataReader() : PolyDataAlgorithm(this) {
            this->m_fileName = "";
            PolyDataAlgorithm::setVtkPolyDataAlgorithm(m_vtkAbstractPolyDataReader);
        }

        auto AbstractPolyDataReader::isValid() -> bool {
            if (!Util::IO::FileExists(this->m_fileName)) {
                Notifications::instance->addWarning("No fileName specified for AbstractPolyDataReader!");
                return false;
            }

            return true;
        }

        AbstractPolyDataReader::AbstractPolyDataReader(AbstractPolyDataReader* other) {
        }

        auto AbstractPolyDataReader::setVtkAbstractPolyDataReader(vtkSmartPointer<vtkAbstractPolyDataReader> ref) -> void {
            this->m_vtkAbstractPolyDataReader = ref;
            PolyDataAlgorithm::setVtkPolyDataAlgorithm(ref);
        }

        auto AbstractPolyDataReader::getVtkAbstractPolyDataReader() -> vtkSmartPointer<vtkAbstractPolyDataReader> {
            return this->m_vtkAbstractPolyDataReader;
        }

        auto AbstractPolyDataReader::setFileName(QString& fileName) -> void {
            auto suffix = this->getSuffix();

            if (!fileName.endsWith(suffix)) {
                fileName += suffix;
            }

            this->m_fileName = fileName;

            emit this->fileNameChanged();

            if (Util::IO::FileExists(fileName))
            {
                this->m_vtkAbstractPolyDataReader->SetFileName(fileName.toStdString().c_str());
                this->m_vtkAbstractPolyDataReader->Update();
                this->update();
            }
        }

        auto AbstractPolyDataReader::getFileName() -> QString {
            return this->m_fileName;
        }

        AbstractPolyDataReader::~AbstractPolyDataReader() {
        }
    }
}
