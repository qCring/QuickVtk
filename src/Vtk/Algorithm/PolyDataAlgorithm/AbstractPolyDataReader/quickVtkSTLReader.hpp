#pragma once

#include "quickVtkAbstractPolyDataReader.hpp"

#include <vtkSTLReader.h>

namespace quick {

    namespace Vtk {

        class STLReader : public AbstractPolyDataReader {
            Q_OBJECT
        private:
            static Qml::Register::Symbol::Class<STLReader> Register;
        public:
            STLReader();
        };
    }
}
