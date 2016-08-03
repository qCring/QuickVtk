#include "quickVtkPolyDataMapper.hpp"
#include "quickVtkPolyDataAlgorithm.hpp"

#include <vtkAlgorithm.h>

namespace quick {

    namespace Vtk {

        Qml::Register::Class<PolyDataMapper> PolyDataMapper::Register;

        PolyDataMapper::PolyDataMapper() : Mapper(vtkSmartPointer<vtkPolyDataMapper>::New()) {
        }
    }
}