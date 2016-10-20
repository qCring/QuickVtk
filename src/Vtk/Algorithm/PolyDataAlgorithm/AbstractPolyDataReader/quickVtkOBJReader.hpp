#pragma once

#include "quickVtkAbstractPolyDataReader.hpp"

#include <vtkOBJReader.h>

namespace quick {

    namespace Vtk {

        class OBJReader : public AbstractPolyDataReader {
            Q_OBJECT
        private:
            static Qml::Register::Symbol::Class<OBJReader> Register;
        public:
            OBJReader();
        };
    }
}
