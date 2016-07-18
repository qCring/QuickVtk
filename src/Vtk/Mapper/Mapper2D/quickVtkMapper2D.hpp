#pragma once

#include "quickVtkAbstractMapper.hpp"

#include <vtkMapper2D.h>

namespace quick {

    namespace Vtk {

        class Mapper2D : public AbstractMapper {
            Q_OBJECT
        private:
            static Qml::Register::AbstractClass<Mapper2D> Register;
            vtkSmartPointer<vtkMapper2D> m_vtkMapper2D;
        public:
            Mapper2D();
            Mapper2D(Mapper2D*);
            auto setVtkMapper2D(vtkSmartPointer<vtkMapper2D>) -> void;
            auto getVtkMapper2D() -> vtkSmartPointer<vtkMapper2D>;
            ~Mapper2D();
        };
    }
}