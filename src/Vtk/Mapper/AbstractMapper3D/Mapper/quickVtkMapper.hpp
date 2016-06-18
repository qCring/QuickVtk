#pragma once

#include "quickVtkAbstractMapper3D.hpp"

#include <vtkMapper.h>

namespace quick {

    namespace Vtk {

        class ScalarsToColors;

        class Mapper : public AbstractMapper3D {
            Q_OBJECT
            Q_ENUMS(ScalarMode);
            Q_PROPERTY(ScalarMode scalarMode READ getScalarMode WRITE setScalarMode NOTIFY scalarModeChanged);
            Q_PROPERTY(bool scalarVisibility READ getScalarVisibility WRITE setScalarVisibility NOTIFY scalarVisibilityChanged);
        public:
            enum ScalarMode {
                DefaultScalarMode = VTK_SCALAR_MODE_DEFAULT,
                PointData = VTK_SCALAR_MODE_USE_POINT_DATA,
                CellData = VTK_SCALAR_MODE_USE_CELL_DATA,
                PointFieldData = VTK_SCALAR_MODE_USE_POINT_FIELD_DATA,
                CellFieldData = VTK_SCALAR_MODE_USE_CELL_FIELD_DATA
            };
        private:
            static Qml::Register::AbstractClass<Mapper> Register;
            vtkSmartPointer<vtkMapper> m_vtkMapper;
        public:
            Mapper();
            Mapper(Mapper*);
            auto setVtkMapper(vtkSmartPointer<vtkMapper>) -> void;
            auto getVtkMapper() -> vtkSmartPointer<vtkMapper>;
            auto setScalarMode(ScalarMode) -> void;
            auto getScalarMode() -> ScalarMode;
            auto setScalarVisibility(bool) -> void;
            auto getScalarVisibility() -> bool;
            ~Mapper();
        signals:
            void scalarVisibilityChanged();
            void scalarModeChanged();
        };
    }
}