#include "quickVtkImageReader2.hpp"
#include "quickIO.hpp"

namespace quick {

    namespace Vtk {

        Qml::Register::AbstractClass<ImageReader2> ImageReader2::Register;

        ImageReader2::ImageReader2(vtkSmartPointer<vtkImageReader2> vtkObject) : ImageAlgorithm(vtkObject) {
            this->m_vtkObject = vtkObject;
        }

        auto ImageReader2::isValid() -> bool {
            if (!IO::FileExists(this->m_fileName)) {
                return false;
            }

            return true;
        }

        auto ImageReader2::setFileName(QString& fileName) -> void {
            this->m_fileName = fileName;

            emit this->fileNameChanged();

            if (IO::FileExists(fileName)) {
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