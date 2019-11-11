#include "quickVtkProp.hpp"
#include "quickVtkAbstractMapper.hpp"

namespace quick {

    namespace Vtk {

        Qml::Register::AbstractClass<AbstractMapper> AbstractMapper::Register(true);

        AbstractMapper::AbstractMapper(vtkSmartPointer<vtkAbstractMapper> vtkObject) : Algorithm(vtkObject) {
        }
    }
}
