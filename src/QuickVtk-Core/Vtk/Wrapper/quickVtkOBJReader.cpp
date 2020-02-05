#include "quickVtkOBJReader.hpp"

namespace quick::Vtk {

    Qml::Register::Class<OBJReader> OBJReader::Register(true);

    OBJReader::OBJReader() : AbstractPolyDataReader(vtkSmartPointer<vtkOBJReader>::New()) {
    }
}
