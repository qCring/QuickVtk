#include "quickVtkPNGReader.hpp"

namespace quick {

    namespace Vtk {

        Qml::Register::Class<PNGReader> PNGReader::Register;

        PNGReader::PNGReader() : ImageReader2(vtkSmartPointer<vtkPNGReader>::New()) {
        }
    }
}