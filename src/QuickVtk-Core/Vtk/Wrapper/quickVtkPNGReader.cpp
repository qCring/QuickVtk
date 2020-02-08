#include "quickVtkPNGReader.hpp"

namespace quick::Vtk {

    Qml::Register::Class<PNGReader> PNGReader::Register(true);

    PNGReader::PNGReader() : ImageReader2(vtkSmartPointer<vtkPNGReader>::New()) {
    }
}
