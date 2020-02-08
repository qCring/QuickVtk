#pragma once

#include "quickVtkAbstractMapper.hpp"

#include <vtkMapper2D.h>

namespace quick::Vtk {

    class Mapper2D : public AbstractMapper {
        Q_OBJECT
    private:
        static Qml::Register::AbstractClass<Mapper2D> Register;
    public:
        Mapper2D(vtkSmartPointer<vtkMapper2D>);
        auto getVtkObject() -> vtkSmartPointer<vtkMapper2D>;
    };
}
