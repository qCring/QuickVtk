#pragma once

#include "quickVtkAlgorithm.hpp"

#include <vtkDataReader.h>

namespace quick {

    namespace Vtk {

        class DataReader : public Algorithm {
            Q_OBJECT
            Q_PROPERTY(QString fileName READ getFileName WRITE setFileName NOTIFY fileNameChanged);
        private:
            static Qml::Register::AbstractClass<DataReader> Register;
            vtkSmartPointer<vtkDataReader> m_vtkDataReader;
        public:
            DataReader();
            DataReader(DataReader*);
            auto setVtkDataReader(vtkSmartPointer<vtkDataReader>) -> void;
            auto getVtkDataReader() -> vtkSmartPointer<vtkDataReader>;
            auto setFileName(const QString&) -> void;
            auto getFileName() -> QString;
            ~DataReader();
        signals:
            void fileNameChanged();
        };
    }
}