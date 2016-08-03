#include "quickVtkStructuredPointsReader.hpp"

namespace quick {

    namespace Vtk {

        Qml::Register::Class<StructuredPointsReader> StructuredPointsReader::Register;

        StructuredPointsReader::StructuredPointsReader() : DataReader(vtkSmartPointer<vtkStructuredPointsReader>::New()) {
        }
    }
}
