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
            static Qml::Register::VtkClass<PolyDataMapper> Register;
            vtkSmartPointer<vtkPolyDataMapper> m_vtkPolyDataMapper;
        public:
            PolyDataMapper();
            PolyDataMapper(PolyDataMapper*);
            auto setVtkPolyDataMapper(vtkSmartPointer<vtkPolyDataMapper>) -> void;
            auto getVtkPolyDataMapper() -> vtkSmartPointer<vtkPolyDataMapper>;
            ~PolyDataMapper();
        };
    }
}