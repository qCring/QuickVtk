#include "quickVtkSTLReader.hpp"

namespace quick {

    namespace Vtk {

        Qml::Register::Class<STLReader> STLReader::Register;

        STLReader::STLReader() : AbstractPolyDataReader(vtkSmartPointer<vtkSTLReader>::New()) {
        }
    }
}
