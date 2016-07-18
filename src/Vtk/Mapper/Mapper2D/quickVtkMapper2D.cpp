#include "quickVtkMapper2D.hpp"

namespace quick {

    namespace Vtk {

        Qml::Register::AbstractClass<Mapper2D> Mapper2D::Register;

        Mapper2D::Mapper2D() : AbstractMapper(this) {
        }

        Mapper2D::Mapper2D(Mapper2D* other) : AbstractMapper(this) {
        }

        auto Mapper2D::setVtkMapper2D(vtkSmartPointer<vtkMapper2D> vtkMapper2D) -> void {
            this->m_vtkMapper2D = vtkMapper2D;
            AbstractMapper::setVtkAbstractMapper(vtkMapper2D);
        }

        auto Mapper2D::getVtkMapper2D() -> vtkSmartPointer<vtkMapper2D> {
            return this->m_vtkMapper2D;
        }

        Mapper2D::~Mapper2D() {
        }
    }
}
