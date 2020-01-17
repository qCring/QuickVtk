#pragma once

#include <QQmlListProperty>

#include "quickVtkMapper.hpp"
#include "quickVtkAlgorithm.hpp"

#include <vtkPolyDataMapper.h>

namespace quick {
    namespace Vtk {

        class PolyDataAlgorithm;

        class PolyDataMapper : public Mapper {
            Q_OBJECT
        private:
            static Qml::Register::Class<PolyDataMapper> Register;
        public:
            PolyDataMapper();
        };
    }
}
