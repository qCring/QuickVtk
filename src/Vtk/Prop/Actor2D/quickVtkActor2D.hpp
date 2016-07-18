#pragma once

#include "quickVtkProp.hpp"

#include <vtkSmartPointer.h>
#include <vtkActor2D.h>

namespace quick {

    namespace Vtk {

        class Mapper2D;

        class Actor2D : public Prop {
            Q_OBJECT
            Q_PROPERTY(quick::Vtk::Mapper2D* mapper READ getMapper WRITE setMapper NOTIFY mapperChanged);
            Q_CLASSINFO("DefaultProperty", "mapper");
        private:
            static Qml::Register::Class<Actor2D> Register;
            vtkSmartPointer<vtkActor2D> m_vtkActor2D;
            Mapper2D* m_mapper2D;
        public:
            Actor2D();
            Actor2D(Actor2D*);
            auto setVtkActor2D(vtkSmartPointer<vtkActor2D>) -> void;
            auto getVtkActor2D() -> vtkSmartPointer<vtkActor2D>;
            auto setMapper(Mapper2D*) -> void;
            auto getMapper() -> Mapper2D*;
            virtual ~Actor2D();
        signals:
            void mapperChanged();
        };
    }
}