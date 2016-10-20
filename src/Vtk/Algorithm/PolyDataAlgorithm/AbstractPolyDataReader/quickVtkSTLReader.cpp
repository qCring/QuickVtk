#include "quickVtkSTLReader.hpp"

namespace quick {

    namespace Vtk {

        Qml::Register::Symbol::Class<STLReader> STLReader::Register;

        STLReader::STLReader() : AbstractPolyDataReader(vtkSmartPointer<vtkSTLReader>::New()) {
        }
    }
}
