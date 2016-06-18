#pragma once

#include <QObject>

#include <vtkSmartPointer.h>
#include <vtkAbstractMapper.h>

#include "quickVtkAlgorithm.hpp"

namespace quick {

    namespace Vtk {

        class Prop;

        class AbstractMapper : public Algorithm {
            Q_OBJECT
        private:
            static Qml::Register::AbstractClass<AbstractMapper> Register;
            vtkSmartPointer<vtkAbstractMapper> m_vtkAbstractMapper;
        public:
            AbstractMapper();
            AbstractMapper(AbstractMapper*);
            auto setVtkAbstractMapper(vtkSmartPointer<vtkAbstractMapper>) -> void;
            auto getVtkAbstractMapper() -> vtkSmartPointer<vtkAbstractMapper>;
            ~AbstractMapper();
        };
    }
}