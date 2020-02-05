#include "quickVtkStructuredPointsReader.hpp"

namespace quick::Vtk {

    Qml::Register::Class<StructuredPointsReader> StructuredPointsReader::Register(true);

    StructuredPointsReader::StructuredPointsReader() : DataReader(vtkSmartPointer<vtkStructuredPointsReader>::New()) {
    }
}
