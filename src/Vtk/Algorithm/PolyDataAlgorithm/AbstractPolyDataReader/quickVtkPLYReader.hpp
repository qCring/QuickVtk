#pragma once

#include "quickVtkAbstractPolyDataReader.hpp"

#include <vtkPLYReader.h>

namespace quick {

    namespace Vtk {

        class PLYReader : public AbstractPolyDataReader {
            Q_OBJECT
        private:
            static Qml::Register::Symbol::Class<PLYReader> Register;
        public:
            PLYReader();
        };
    }
}
