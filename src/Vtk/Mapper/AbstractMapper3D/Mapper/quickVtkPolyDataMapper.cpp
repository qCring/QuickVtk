#include "quickVtkPolyDataMapper.hpp"
#include "quickVtkPolyDataAlgorithm.hpp"

#include <vtkAlgorithm.h>

namespace quick {

    namespace Vtk {

        Qml::Register::VtkClass<PolyDataMapper> PolyDataMapper::Register;

        PolyDataMapper::PolyDataMapper() : Mapper(this) {
            this->setVtkPolyDataMapper(vtkSmartPointer<vtkPolyDataMapper>::New());
        }

        PolyDataMapper::PolyDataMapper(PolyDataMapper* other) : Mapper(this) {
        }

        auto PolyDataMapper::setVtkPolyDataMapper(vtkSmartPointer<vtkPolyDataMapper> vtkPolyDataMapper) -> void {
            this->m_vtkPolyDataMapper = vtkPolyDataMapper;
            Mapper::setVtkMapper(vtkPolyDataMapper);
        }

        auto PolyDataMapper::getVtkPolyDataMapper() -> vtkSmartPointer<vtkPolyDataMapper> {
            return this->m_vtkPolyDataMapper;
        }

        PolyDataMapper::~PolyDataMapper() {
        }
    }
}