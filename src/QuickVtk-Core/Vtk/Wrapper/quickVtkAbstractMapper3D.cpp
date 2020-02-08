#include "quickVtkAbstractMapper3D.hpp"

namespace quick::Vtk {

    Qml::Register::AbstractClass<AbstractMapper3D> AbstractMapper3D::Register(true);

    AbstractMapper3D::AbstractMapper3D(vtkSmartPointer<vtkAbstractMapper3D> vtkObject) : AbstractMapper(vtkObject) {
    }
}
