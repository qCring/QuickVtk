#include "quickVtkOBJReader.hpp"

namespace quick {

    namespace Vtk {

        Qml::Register::Symbol::Class<OBJReader> OBJReader::Register(true);

        OBJReader::OBJReader() : AbstractPolyDataReader(vtkSmartPointer<vtkOBJReader>::New()) {
        }
    }
}
