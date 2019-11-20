#pragma once

#include "quickVtkProp3D.hpp"

#include <vtkActor.h>

namespace quick {

    namespace Vtk {

        class Mapper;
        class Texture;
        class Property;

        class Actor : public Prop3D {
            Q_OBJECT
            Q_PROPERTY(quick::Vtk::Texture* texture READ getTexture CONSTANT);
            Q_PROPERTY(quick::Vtk::Property* property READ getProperty CONSTANT);
            Q_PROPERTY(quick::Vtk::Mapper* mapper READ getMapper WRITE setMapper NOTIFY mapperChanged);
            Q_CLASSINFO("DefaultProperty", "mapper");
        private:
            static Qml::Register::Class<Actor> Register;
            Property* m_property = nullptr;
            Texture* m_texture = nullptr;
            Mapper* m_mapper = nullptr;
            vtkSmartPointer<vtkActor> m_vtkObject = nullptr;
        public:
            Actor();
            Actor(vtkSmartPointer<vtkActor>);
            auto setVtkActor(vtkSmartPointer<vtkActor>) -> void;
            auto setMapper(Mapper*) -> void;
            auto getMapper() -> Mapper*;
            auto getProperty() -> Property*;
            auto getTexture() -> Texture*;
            auto getVtkObject() -> vtkSmartPointer<vtkActor>;
            ~Actor();
        signals:
            void mapperChanged();
        };
    }
}
