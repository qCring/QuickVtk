#pragma once

#include "quickVtkProp3D.hpp"
#include "quickVtkMapper.hpp"

#include <vtkActor.h>

namespace quick {

    namespace Vtk {

        class Actor : public Prop3D {
            Q_OBJECT
            Q_PROPERTY(quick::Vtk::Mapper* mapper READ getMapper WRITE setMapper NOTIFY mapperChanged);
            Q_CLASSINFO("DefaultProperty", "mapper");
        private:
            static Qml::Register::VtkClass<Actor> Register;
            Mapper* m_mapper;
            vtkSmartPointer<vtkActor> m_vtkActor;
        public:
            Actor();
            Actor(Actor* other);
            auto setVtkActor(vtkSmartPointer<vtkActor>) -> void;
            auto setMapper(Mapper*) -> void;
            auto getMapper() -> Mapper*;
            auto getVtkActor() -> vtkSmartPointer<vtkActor>;
            virtual ~Actor();
        signals:
            void mapperChanged();
        };
    }
}