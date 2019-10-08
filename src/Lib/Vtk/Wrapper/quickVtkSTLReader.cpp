#include "quickVtkSTLReader.hpp"

namespace quick {

    namespace Vtk {

        Qml::Register::Symbol::Class<STLReader> STLReader::Register(true);

        STLReader::STLReader() : AbstractPolyDataReader(vtkSmartPointer<vtkSTLReader>::New()) {
        }
    }
}
