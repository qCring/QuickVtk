#pragma once

#include "quickVtkAbstractMapper.hpp"

#include <vtkAbstractMapper3D.h>

namespace quick {

    namespace Vtk {

        class AbstractMapper3D : public AbstractMapper {
            Q_OBJECT
        private:
            static Qml::Register::AbstractClass<AbstractMapper3D> Register;
            vtkSmartPointer<vtkAbstractMapper3D> m_vtkAbstractMapper3D;
        public:
            AbstractMapper3D();
            AbstractMapper3D(AbstractMapper3D*);
            auto setVtkAbstractMapper3D(vtkSmartPointer<vtkAbstractMapper3D>) -> void;
            auto getVtkAbstractMapper3D() -> vtkSmartPointer<vtkAbstractMapper3D>;
            ~AbstractMapper3D();
        };
    }
}