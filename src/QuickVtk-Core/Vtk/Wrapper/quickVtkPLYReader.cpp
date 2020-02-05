#include "quickVtkPLYReader.hpp"

namespace quick::Vtk {

    Qml::Register::Class<PLYReader> PLYReader::Register(true);

    PLYReader::PLYReader() : AbstractPolyDataReader(vtkSmartPointer<vtkPLYReader>::New()) {
    }
}
