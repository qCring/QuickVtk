#pragma once

#include "quickVtkProp.hpp"
#include "quickMathVector.hpp"

#include <vtkSmartPointer.h>
#include <vtkProp3D.h>

namespace quick {

    namespace Vtk {

        class Prop3D : public Prop {
            Q_OBJECT
            Q_PROPERTY(quick::Math::Vector* position READ getPosition WRITE setPosition NOTIFY positionChanged);
            Q_PROPERTY(quick::Math::Vector* origin READ getOrigin WRITE setOrigin NOTIFY originChanged);
        private:
            Math::Vector* m_position = nullptr;
            Math::Vector* m_origin = nullptr;
            static Qml::Register::VtkClass<Prop3D> Register;
            vtkSmartPointer<vtkProp3D> m_vtkProp3D;
            std::function<void(Math::Vector&&)> m_positionChanged;
            std::function<void(Math::Vector&&)> m_originChanged;
        public:
            Prop3D();
            Prop3D(Prop3D*);
            auto setPosition(Math::Vector*) -> void;
            auto getPosition() -> Math::Vector*;
            auto setOrigin(Math::Vector*) -> void;
            auto getOrigin() -> Math::Vector*;
            auto setVtkProp3D(vtkSmartPointer<vtkProp3D>) -> void;
            auto getVtkProp3D() -> vtkSmartPointer<vtkProp3D>;
            virtual ~Prop3D();
        signals:
            void positionChanged();
            void originChanged();
        };
    }
}