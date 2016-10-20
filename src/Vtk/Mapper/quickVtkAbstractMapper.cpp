#include "quickVtkProp.hpp"
#include "quickVtkAbstractMapper.hpp"

namespace quick {

    namespace Vtk {

        Qml::Register::Symbol::AbstractClass<AbstractMapper> AbstractMapper::Register;

        AbstractMapper::AbstractMapper(vtkSmartPointer<vtkAbstractMapper> vtkObject) : Algorithm(vtkObject) {
        }
    }
}
