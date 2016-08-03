#pragma once

#include "quickVtkAbstractMapper.hpp"

#include <vtkAbstractMapper3D.h>

namespace quick {

    namespace Vtk {

        class AbstractMapper3D : public AbstractMapper {
            Q_OBJECT
        private:
            static Qml::Register::AbstractClass<AbstractMapper3D> Register;
        public:
            AbstractMapper3D(vtkSmartPointer<vtkAbstractMapper3D>);
        };
    }
}