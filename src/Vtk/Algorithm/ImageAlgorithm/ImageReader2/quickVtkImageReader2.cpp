#include "quickVtkImageReader2.hpp"
#include "quickUtilIO.hpp"
#include "quickNotifications.hpp"

namespace quick {

    namespace Vtk {

        Qml::Register::AbstractClass<ImageReader2> ImageReader2::Register;

        ImageReader2::ImageReader2(vtkSmartPointer<vtkImageReader2> vtkObject) : ImageAlgorithm(vtkObject) {
            this->m_vtkObject = vtkObject;
        }

        auto ImageReader2::isValid() -> bool {
            if (!Util::IO::FileExists(this->m_fileName)) {
                Notifications::instance->addWarning("No fileName specified for ImageReader2!");
                return false;
            }

            return true;
        }

        auto ImageReader2::setFileName(QString& fileName) -> void {
            auto suffix = this->getSuffix();

            if (!fileName.endsWith(suffix)) {
                fileName += suffix;
            }

            this->m_fileName = fileName;

            emit this->fileNameChanged();

            if (Util::IO::FileExists(fileName)) {
                this->m_vtkObject->SetFileName(fileName.toStdString().c_str());
                this->m_vtkObject->Update();
                this->update();
            }
        }

        auto ImageReader2::getFileName() -> QString {
            return this->m_fileName;
        }
    }
}