#pragma once

#include "quickVtkProp.hpp"
#include "quickMathVector.hpp"

#include <vtkSmartPointer.h>
#include <vtkProp3D.h>

namespace quick {

    namespace Vtk {

        class Prop3D : public Prop {
            Q_OBJECT
            Q_PROPERTY(quick::Math::Vector* scale READ getScale WRITE setScale NOTIFY scaleChanged);
            Q_PROPERTY(quick::Math::Vector* origin READ getOrigin WRITE setOrigin NOTIFY originChanged);
            Q_PROPERTY(quick::Math::Vector* position READ getPosition WRITE setPosition NOTIFY positionChanged);
            Q_PROPERTY(quick::Math::Vector* orientation READ getOrientation WRITE setOrientation NOTIFY orientationChanged);
        private:
            static Qml::Register::VtkClass<Prop3D> Register;
            Math::Vector* m_scale = nullptr;
            Math::Vector* m_origin = nullptr;
            Math::Vector* m_position = nullptr;
            Math::Vector* m_orientation = nullptr;
            Math::Vector::cb_t m_scaleCb;
            Math::Vector::cb_t m_originCb;
            Math::Vector::cb_t m_positionCb;
            Math::Vector::cb_t m_orientationCb;
            vtkSmartPointer<vtkProp3D> m_vtkProp3D;
        private:
            auto updateScale(Math::Vector&&) -> void;
            auto updateOrigin(Math::Vector&&) -> void;
            auto updatePosition(Math::Vector&&) -> void;
            auto updateOrientation(Math::Vector&&) -> void;
        public:
            Prop3D();
            Prop3D(Prop3D*);
            auto setScale(Math::Vector*) -> void;
            auto getScale() -> Math::Vector*;
            auto setOrigin(Math::Vector*) -> void;
            auto getOrigin() -> Math::Vector*;
            auto setPosition(Math::Vector*) -> void;
            auto getPosition() -> Math::Vector*;
            auto setOrientation(Math::Vector*) -> void;
            auto getOrientation() -> Math::Vector*;
            auto setVtkProp3D(vtkSmartPointer<vtkProp3D>) -> void;
            auto getVtkProp3D() -> vtkSmartPointer<vtkProp3D>;
            virtual ~Prop3D();
        signals:
            void scaleChanged();
            void originChanged();
            void positionChanged();
            void orientationChanged();
        };
    }
}