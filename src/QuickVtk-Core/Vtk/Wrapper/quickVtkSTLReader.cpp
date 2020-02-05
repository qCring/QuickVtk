#include "quickVtkSTLReader.hpp"

namespace quick::Vtk {

    Qml::Register::Class<STLReader> STLReader::Register(true);

    STLReader::STLReader() : AbstractPolyDataReader(vtkSmartPointer<vtkSTLReader>::New()) {
    }
}
