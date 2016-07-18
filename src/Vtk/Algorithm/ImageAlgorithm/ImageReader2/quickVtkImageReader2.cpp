#include "quickVtkImageReader2.hpp"
#include "quickUtilIO.hpp"
#include "quickNotifications.hpp"

namespace quick {

    namespace Vtk {

        Qml::Register::AbstractClass<ImageReader2> ImageReader2::Register;

        ImageReader2::ImageReader2() : ImageAlgorithm(this) {
            this->m_vtkImageReader2 = nullptr;
        }

        ImageReader2::ImageReader2(ImageReader2* other) : ImageAlgorithm(this) {
        }

        auto ImageReader2::setVtkImageReader2(vtkSmartPointer<vtkImageReader2> vtkImageReader2) -> void {
            this->m_vtkImageReader2 = vtkImageReader2;
            ImageAlgorithm::setVtkImageAlgorithm(vtkImageReader2);
        }

        auto ImageReader2::getVtkImageReader2() -> vtkSmartPointer<vtkImageReader2> {
            return this->m_vtkImageReader2;
        }

        auto ImageReader2::isValid() -> bool {
            if (!Util::IO::FileExists(QString(this->m_vtkImageReader2->GetFileName()))) {
                Notifications::instance->addWarning("No fileName specified for ImageReader2!");
                return false;
            }

            return true;
        }

        auto ImageReader2::setFileName(const QString& fileName) -> void {
            this->m_fileName = fileName;

            emit this->fileNameChanged();

            if (Util::IO::FileExists(fileName)) {
                this->m_vtkImageReader2->SetFileName(fileName.toStdString().c_str());
                this->m_vtkImageReader2->Update();
                this->update();
            }
        }

        auto ImageReader2::getFileName() -> QString {
            return this->m_fileName;
        }

        ImageReader2::~ImageReader2() {
        }
    }
}