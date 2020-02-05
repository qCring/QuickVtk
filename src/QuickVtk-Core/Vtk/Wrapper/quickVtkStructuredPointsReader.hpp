#pragma once

#include "quickVtkDataReader.hpp"

#include <vtkStructuredPointsReader.h>

namespace quick::Vtk {

    class StructuredPointsReader : public DataReader {
        Q_OBJECT
    private:
        static Qml::Register::Class<StructuredPointsReader> Register;
    public:
        StructuredPointsReader();
    };
}
