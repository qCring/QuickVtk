#include "quickVtkStructuredPointsReader.hpp"

namespace quick {

    namespace Vtk {

        Qml::Register::Symbol::Class<StructuredPointsReader> StructuredPointsReader::Register;

        StructuredPointsReader::StructuredPointsReader() : DataReader(vtkSmartPointer<vtkStructuredPointsReader>::New()) {
        }
    }
}
