#pragma once

#include "quickVtkProp.hpp"

#include <vtkSmartPointer.h>
#include <vtkActor2D.h>

namespace quick {

    namespace Vtk {

        class Mapper2D;
        class Property2D;

        class Actor2D : public Prop {
            Q_OBJECT
            Q_PROPERTY(quick::Vtk::Property2D* property2D READ getProperty2D WRITE setProperty2D NOTIFY property2DChanged);
            Q_PROPERTY(quick::Vtk::Mapper2D* mapper2D READ getMapper2D WRITE setMapper2D NOTIFY mapper2DChanged);
            Q_PROPERTY(double width READ getWidth WRITE setWidth NOTIFY widthChanged);
            Q_PROPERTY(double height READ getHeight WRITE setHeight NOTIFY heightChanged);
            Q_CLASSINFO("DefaultProperty", "mapper2D");
        private:
            static Qml::Register::Class<Actor2D> Register;
            vtkSmartPointer<vtkActor2D> m_vtkActor2D;
            Mapper2D* m_mapper2D = nullptr;
            Property2D* m_property2D = nullptr;
        public:
            Actor2D();
            Actor2D(Actor2D*);
            auto setVtkActor2D(vtkSmartPointer<vtkActor2D>) -> void;
            auto getVtkActor2D() -> vtkSmartPointer<vtkActor2D>;
            auto setProperty2D(Property2D*) -> void;
            auto getProperty2D() -> Property2D*;
            auto setMapper2D(Mapper2D*) -> void;
            auto getMapper2D() -> Mapper2D*;
            auto setWidth(double) -> void;
            auto getWidth() -> double;
            auto setHeight(double) -> void;
            auto getHeight() -> double;
            virtual ~Actor2D();
        signals:
            void widthChanged();
            void heightChanged();
            void mapper2DChanged();
            void property2DChanged();
        };
    }
}