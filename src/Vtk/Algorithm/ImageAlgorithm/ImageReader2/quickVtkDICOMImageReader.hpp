#pragma once

#include "quickVtkImageReader2.hpp"

#include <vtkDICOMImageReader.h>

namespace quick {

    namespace Vtk {

        class DICOMImageReader : public ImageReader2 {
            Q_OBJECT
            Q_PROPERTY(QString directoryName READ getDirectoryName WRITE setDirectoryName NOTIFY directoryNameChanged);
        private:
            QString m_directoryName;
            static Qml::Register::Class<DICOMImageReader> Register;
            vtkSmartPointer<vtkDICOMImageReader> m_vtkDICOMImageReader;
        public:
            auto getSuffix() -> QString override;
            auto setDirectoryName(const QString&) -> void;
            auto getDirectoryName() -> QString;
            DICOMImageReader();
        signals:
            void directoryNameChanged();
        };
    }
}