#pragma once

#include "quickVtkPointSetAlgorithm.hpp"
#include "quickMathVector2.hpp"

#include <vtkWarpLens.h>

namespace quick {

    namespace Vtk {

        class WarpLens : public PointSetAlgorithm {
            Q_OBJECT
            Q_PROPERTY(quick::Math::Vector2* center READ getCenter CONSTANT);
            Q_PROPERTY(quick::Math::Vector2* principalPoint READ getPrincipalPoint CONSTANT);
            Q_PROPERTY(float k1 READ getK1 WRITE setK1 NOTIFY k1Changed);
            Q_PROPERTY(float k2 READ getK2 WRITE setK2 NOTIFY k2Changed);
            Q_PROPERTY(float p1 READ getP1 WRITE setP1 NOTIFY p1Changed);
            Q_PROPERTY(float p2 READ getP2 WRITE setP2 NOTIFY p2Changed);
        private:
            static Qml::Register::Class<WarpLens> Register;
            vtkSmartPointer<vtkWarpLens> m_vtkObject;
            Math::Vector2* m_center = nullptr;
            Math::Vector2* m_principalPoint = nullptr;
        public:
            WarpLens();
            auto getCenter() -> Math::Vector2*;
            auto getPrincipalPoint() -> Math::Vector2*;
            auto setK1(float) -> void;
            auto getK1() -> float;
            auto setK2(float) -> void;
            auto getK2() -> float;
            auto setP1(float) -> void;
            auto getP1() -> float;
            auto setP2(float) -> void;
            auto getP2() -> float;
        signals:
            void k1Changed();
            void k2Changed();
            void p1Changed();
            void p2Changed();
        };
    }
}
