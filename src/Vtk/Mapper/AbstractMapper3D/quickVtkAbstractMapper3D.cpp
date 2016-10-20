#include "quickVtkAbstractMapper3D.hpp"

namespace quick {

    namespace Vtk {

        Qml::Register::Symbol::AbstractClass<AbstractMapper3D> AbstractMapper3D::Register;

        AbstractMapper3D::AbstractMapper3D(vtkSmartPointer<vtkAbstractMapper3D> vtkObject) : AbstractMapper(vtkObject) {
        }
    }
}
