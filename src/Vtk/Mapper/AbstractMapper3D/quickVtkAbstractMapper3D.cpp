#include "quickVtkAbstractMapper3D.hpp"

namespace quick {

    namespace Vtk {

        Qml::Register::AbstractClass<AbstractMapper3D> AbstractMapper3D::Register;

        AbstractMapper3D::AbstractMapper3D() : AbstractMapper(this) {
        }

        AbstractMapper3D::AbstractMapper3D(AbstractMapper3D* other) : AbstractMapper(this) {
        }

        auto AbstractMapper3D::setVtkAbstractMapper3D(vtkSmartPointer<vtkAbstractMapper3D> vtkAbstractMapper3D) -> void {
            this->m_vtkAbstractMapper3D = vtkAbstractMapper3D;
            AbstractMapper::setVtkAbstractMapper(vtkAbstractMapper3D);
        }

        auto AbstractMapper3D::getVtkAbstractMapper3D() -> vtkSmartPointer<vtkAbstractMapper3D> {
            return this->m_vtkAbstractMapper3D;
        }

        AbstractMapper3D::~AbstractMapper3D() {
        }
    }
}
