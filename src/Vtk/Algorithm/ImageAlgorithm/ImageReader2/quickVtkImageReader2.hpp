#pragma once

#include "quickVtkImageAlgorithm.hpp"

#include <vtkImageReader2.h>

namespace quick {

    namespace Vtk {

        class ImageReader2 : public ImageAlgorithm {
            Q_OBJECT
            Q_PROPERTY(QString fileName READ getFileName WRITE setFileName NOTIFY fileNameChanged);
        private:
            static Qml::Register::AbstractClass<ImageReader2> Register;
            vtkSmartPointer<vtkImageReader2> m_vtkImageReader2;
            QString m_fileName;
        public:
            ImageReader2();
            ImageReader2(ImageReader2*);
            auto setVtkImageReader2(vtkSmartPointer<vtkImageReader2>) -> void;
            auto getVtkImageReader2() -> vtkSmartPointer<vtkImageReader2>;
            auto setFileName(const QString&) -> void;
            auto getFileName() -> QString;
            virtual auto isValid() -> bool;
            ~ImageReader2();
        signals:
            void fileNameChanged();
        };
    }
}