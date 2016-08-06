#include "quickVtkOBJReader.hpp"

namespace quick {

    namespace Vtk {

        Qml::Register::Class<OBJReader> OBJReader::Register;

        OBJReader::OBJReader() : AbstractPolyDataReader(vtkSmartPointer<vtkOBJReader>::New()) {
        }
    }
}
