#pragma once

#include <QObject>

#include <vtkSmartPointer.h>
#include <vtkAbstractMapper.h>

#include "quickVtkAlgorithm.hpp"

namespace quick {

    namespace Vtk {

        class AbstractMapper : public Algorithm {
            Q_OBJECT
        private:
            static Qml::Register::Symbol::AbstractClass<AbstractMapper> Register;
        public:
            AbstractMapper(vtkSmartPointer<vtkAbstractMapper>);
        };
    }
}
