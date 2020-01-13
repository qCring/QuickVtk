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
            Q_PROPERTY(qreal k1 READ getK1 WRITE setK1 NOTIFY k1Changed);
            Q_PROPERTY(qreal k2 READ getK2 WRITE setK2 NOTIFY k2Changed);
            Q_PROPERTY(qreal p1 READ getP1 WRITE setP1 NOTIFY p1Changed);
            Q_PROPERTY(qreal p2 READ getP2 WRITE setP2 NOTIFY p2Changed);
        private:
            static Qml::Register::Class<WarpLens> Register;
            vtkSmartPointer<vtkWarpLens> m_vtkObject = nullptr;
            Math::Vector2* m_center = nullptr;
            Math::Vector2* m_principalPoint = nullptr;
        public:
            WarpLens();
            auto getCenter() -> Math::Vector2*;
            auto getPrincipalPoint() -> Math::Vector2*;
            auto setK1(qreal) -> void;
            auto getK1() -> qreal;
            auto setK2(qreal) -> void;
            auto getK2() -> qreal;
            auto setP1(qreal) -> void;
            auto getP1() -> qreal;
            auto setP2(qreal) -> void;
            auto getP2() -> qreal;
        signals:
            void k1Changed();
            void k2Changed();
            void p1Changed();
            void p2Changed();
        };
    }
}
