#pragma once

#include "quickVtkAbstractPolyDataReader.hpp"

#include <vtkOBJReader.h>

namespace quick {

    namespace Vtk {

        class OBJReader : public AbstractPolyDataReader {
            Q_OBJECT
        private:
            static Qml::Register::VtkClass<OBJReader> Register;
            vtkSmartPointer<vtkOBJReader> m_vtkOBJReader;
        public:
            OBJReader();
            ~OBJReader();
        };
    }
}
