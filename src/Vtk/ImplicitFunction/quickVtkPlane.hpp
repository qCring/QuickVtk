#pragma once

#include "quickMathVector3.hpp"
#include "quickVtkImplicitFunction.hpp"

#include <vtkPlane.h>

namespace quick {

    namespace Vtk {

        class Plane : public ImplicitFunction {
            Q_OBJECT
            Q_PROPERTY(quick::Math::Vector3* origin READ getOrigin WRITE setOrigin NOTIFY originChanged);
            Q_PROPERTY(quick::Math::Vector3* normal READ getNormal WRITE setNormal NOTIFY normalChanged);
        private:
            static Qml::Register::Class<Plane> Register;
            vtkSmartPointer<vtkPlane> m_vtkPlane;
            Math::Vector3::cb_t m_originCb;
            Math::Vector3::cb_t m_normalCb;
            Math::Vector3* m_origin;
            Math::Vector3* m_normal;
        private:
            auto updateOrigin(Math::Vector3&&) -> void;
            auto updateNormal(Math::Vector3&&) -> void;
        public:
            Plane();
            auto setVtkPlane(vtkSmartPointer<vtkPlane>) -> void;
            auto getVtkPlane() -> vtkSmartPointer<vtkPlane> ;
            auto setOrigin(Math::Vector3*) -> void;
            auto getOrigin() -> Math::Vector3*;
            auto setNormal(Math::Vector3*) -> void;
            auto getNormal() -> Math::Vector3*;
            ~Plane();
        signals:
            void originChanged();
            void normalChanged();
        };
    }
}