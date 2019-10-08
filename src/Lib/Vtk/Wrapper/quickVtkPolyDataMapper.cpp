#include "quickVtkPolyDataMapper.hpp"
#include "quickVtkPolyDataAlgorithm.hpp"

#include <vtkAlgorithm.h>

namespace quick {

    namespace Vtk {

        Qml::Register::Symbol::Class<PolyDataMapper> PolyDataMapper::Register(true);

        PolyDataMapper::PolyDataMapper() : Mapper(vtkSmartPointer<vtkPolyDataMapper>::New()) {
        }
    }
}
