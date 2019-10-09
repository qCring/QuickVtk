#include "quickVtkPLYReader.hpp"

namespace quick {

    namespace Vtk {

        Qml::Register::Symbol::Class<PLYReader> PLYReader::Register(true);

        PLYReader::PLYReader() : AbstractPolyDataReader(vtkSmartPointer<vtkPLYReader>::New()) {
        }
    }
}
