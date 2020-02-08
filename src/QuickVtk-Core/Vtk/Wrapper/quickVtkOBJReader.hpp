#pragma once

#include "quickVtkAbstractPolyDataReader.hpp"

#include <vtkOBJReader.h>

namespace quick::Vtk {

    class OBJReader : public AbstractPolyDataReader {
        Q_OBJECT
    private:
        static Qml::Register::Class<OBJReader> Register;
    public:
        OBJReader();
    };
}
