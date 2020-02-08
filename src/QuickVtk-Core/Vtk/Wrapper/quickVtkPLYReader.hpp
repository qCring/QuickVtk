#pragma once

#include "quickVtkAbstractPolyDataReader.hpp"

#include <vtkPLYReader.h>

namespace quick::Vtk {

    class PLYReader : public AbstractPolyDataReader {
        Q_OBJECT
    private:
        static Qml::Register::Class<PLYReader> Register;
    public:
        PLYReader();
    };
}
