#include "quickVtkPLYReader.hpp"

namespace quick {

    namespace Vtk {

        Qml::Register::Class<PLYReader> PLYReader::Register;

        PLYReader::PLYReader() : AbstractPolyDataReader(vtkSmartPointer<vtkPLYReader>::New()) {
        }
    }
}
