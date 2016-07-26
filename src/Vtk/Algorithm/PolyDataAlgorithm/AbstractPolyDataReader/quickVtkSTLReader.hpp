#pragma once

#include "quickVtkAbstractPolyDataReader.hpp"

#include <vtkSTLReader.h>

namespace quick {

    namespace Vtk {

        class STLReader : public AbstractPolyDataReader {
            Q_OBJECT
        private:
            static Qml::Register::Class<STLReader> Register;
            vtkSmartPointer<vtkSTLReader> m_vtkSTLReader;
        public:
            STLReader();
            auto getSuffix() -> QString override;
        };
    }
}
