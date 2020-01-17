#pragma once

#include "quickVtkPolyDataAlgorithm.hpp"

#include <vtkOFFReader.h>

namespace quick {
    namespace Vtk {

        class OFFReader : public PolyDataAlgorithm {
            Q_OBJECT
            Q_PROPERTY(QString fileName READ getFileName WRITE setFileName NOTIFY fileNameChanged);
        private:
            static Qml::Register::Class<OFFReader> Register;
            vtkSmartPointer<vtkOFFReader> m_vtkObject = nullptr;
            QString m_fileName;
        public:
            OFFReader();
            auto setFileName(const QString&) -> void;
            auto getFileName() -> QString;
        signals:
            void fileNameChanged();
        };
    }
}
