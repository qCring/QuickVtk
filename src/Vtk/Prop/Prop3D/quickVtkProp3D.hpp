#pragma once

#include "quickVtkProp.hpp"
#include "quickMathVector3.hpp"

#include <vtkSmartPointer.h>
#include <vtkProp3D.h>

namespace quick {

    namespace Vtk {

        class Prop3D : public Prop {
            Q_OBJECT
            Q_PROPERTY(quick::Math::Vector3* scale READ getScale WRITE setScale NOTIFY scaleChanged);
            Q_PROPERTY(quick::Math::Vector3* origin READ getOrigin WRITE setOrigin NOTIFY originChanged);
            Q_PROPERTY(quick::Math::Vector3* position READ getPosition WRITE setPosition NOTIFY positionChanged);
            Q_PROPERTY(quick::Math::Vector3* orientation READ getOrientation WRITE setOrientation NOTIFY orientationChanged);
        private:
            static Qml::Register::AbstractClass<Prop3D> Register;
            Math::Vector3* m_scale = nullptr;
            Math::Vector3* m_origin = nullptr;
            Math::Vector3* m_position = nullptr;
            Math::Vector3* m_orientation = nullptr;
            Math::Vector3::cb_t m_scaleCb;
            Math::Vector3::cb_t m_originCb;
            Math::Vector3::cb_t m_positionCb;
            Math::Vector3::cb_t m_orientationCb;
            vtkSmartPointer<vtkProp3D> m_vtkObject;
        private:
            auto updateScale(Math::Vector3&&) -> void;
            auto updateOrigin(Math::Vector3&&) -> void;
            auto updatePosition(Math::Vector3&&) -> void;
            auto updateOrientation(Math::Vector3&&) -> void;
        public:
            Prop3D(vtkSmartPointer<vtkProp3D>);
            auto setScale(Math::Vector3*) -> void;
            auto getScale() -> Math::Vector3*;
            auto setOrigin(Math::Vector3*) -> void;
            auto getOrigin() -> Math::Vector3*;
            auto setPosition(Math::Vector3*) -> void;
            auto getPosition() -> Math::Vector3*;
            auto setOrientation(Math::Vector3*) -> void;
            auto getOrientation() -> Math::Vector3*;
            virtual ~Prop3D();
        signals:
            void scaleChanged();
            void originChanged();
            void positionChanged();
            void orientationChanged();
        };
    }
}