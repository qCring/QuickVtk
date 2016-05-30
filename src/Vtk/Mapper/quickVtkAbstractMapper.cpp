#include "quickVtkProp.hpp"
#include "quickVtkAbstractMapper.hpp"

namespace quick {

    namespace Vtk {

        Qml::Register::VtkClass<AbstractMapper> AbstractMapper::Register;

        AbstractMapper::AbstractMapper() : Algorithm(this) {
            this->m_vtkAbstractMapper   = 0;
        }

        AbstractMapper::AbstractMapper(AbstractMapper* other) : Algorithm(this) {
        }

        auto AbstractMapper::setVtkAbstractMapper(vtkSmartPointer<vtkAbstractMapper> vtkAbstractMapper) -> void {
            this->m_vtkAbstractMapper = vtkAbstractMapper;
            this->setVtkAlgorithm(vtkAbstractMapper);
        }

        auto AbstractMapper::getVtkAbstractMapper() -> vtkSmartPointer<vtkAbstractMapper> {
            return this->m_vtkAbstractMapper;
        }

        AbstractMapper::~AbstractMapper() {
        }
    }
}