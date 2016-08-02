#pragma once

#include "quickVtkProp3D.hpp"

#include <vtkActor.h>

namespace quick {

    namespace Vtk {

        class Mapper;
        class Property;

        class Actor : public Prop3D {
            Q_OBJECT
            Q_PROPERTY(quick::Vtk::Property* property READ getProperty WRITE setProperty NOTIFY propertyChanged);
            Q_PROPERTY(quick::Vtk::Mapper* mapper READ getMapper WRITE setMapper NOTIFY mapperChanged);
            Q_CLASSINFO("DefaultProperty", "mapper");
        private:
            static Qml::Register::Class<Actor> Register;
            Property* m_property = nullptr;
            Mapper* m_mapper = nullptr;
            vtkSmartPointer<vtkActor> m_vtkActor;
        public:
            Actor();
            Actor(Actor* other);
            auto setVtkActor(vtkSmartPointer<vtkActor>) -> void;
            auto setMapper(Mapper*) -> void;
            auto getMapper() -> Mapper*;
            auto setProperty(Property*) -> void;
            auto getProperty() -> Property*;
            auto getVtkActor() -> vtkSmartPointer<vtkActor>;
            virtual ~Actor();
        signals:
            void mapperChanged();
            void propertyChanged();
        };
    }
}