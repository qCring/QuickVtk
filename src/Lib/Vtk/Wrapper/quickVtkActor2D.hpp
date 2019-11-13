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
            Q_PROPERTY(quick::Vtk::Property2D* property READ getProperty CONSTANT);
            Q_PROPERTY(quick::Vtk::Mapper2D* mapper READ getMapper WRITE setMapper NOTIFY mapperChanged);
            Q_PROPERTY(qreal width READ getWidth WRITE setWidth NOTIFY widthChanged);
            Q_PROPERTY(qreal height READ getHeight WRITE setHeight NOTIFY heightChanged);
            Q_CLASSINFO("DefaultProperty", "mapper");
        private:
            static Qml::Register::Class<Actor2D> Register;
            vtkSmartPointer<vtkActor2D> m_vtkObject;
            Mapper2D* m_mapper = nullptr;
            Property2D* m_property = nullptr;
        public:
            Actor2D();
            Actor2D(vtkSmartPointer<vtkActor2D>);
            auto getVtkObject() -> vtkSmartPointer<vtkActor2D>;
            auto getProperty() -> Property2D*;
            auto setMapper(Mapper2D*) -> void;
            auto getMapper() -> Mapper2D*;
            auto setWidth(qreal) -> void;
            auto getWidth() -> qreal;
            auto setHeight(qreal) -> void;
            auto getHeight() -> qreal;
            virtual ~Actor2D();
        signals:
            void widthChanged();
            void heightChanged();
            void mapperChanged();
        };
    }
}
