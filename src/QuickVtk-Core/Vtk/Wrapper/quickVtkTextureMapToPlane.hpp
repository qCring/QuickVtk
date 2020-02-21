#pragma once

#include "quickVtkDataSetAlgorithm.hpp"
#include "quickMathVector2.hpp"
#include "quickMathVector3.hpp"

#include <vtkTextureMapToPlane.h>

namespace quick::Vtk {

    class TextureMapToPlane : public DataSetAlgorithm {
        Q_OBJECT
        Q_PROPERTY(quick::Math::Vector3* origin READ getOrigin CONSTANT);
        Q_PROPERTY(quick::Math::Vector3* point1 READ getPoint1 CONSTANT);
        Q_PROPERTY(quick::Math::Vector3* point2 READ getPoint2 CONSTANT);
        Q_PROPERTY(quick::Math::Vector3* normal READ getNormal CONSTANT);
        Q_PROPERTY(quick::Math::Vector2* sRange READ getSRange CONSTANT);
        Q_PROPERTY(quick::Math::Vector2* tRange READ getTRange CONSTANT);
    private:
        static Qml::Register::Class<TextureMapToPlane> Register;
        vtkSmartPointer<vtkTextureMapToPlane> m_vtkObject = nullptr;
        Math::Vector3* m_origin = nullptr;
        Math::Vector3* m_point1 = nullptr;
        Math::Vector3* m_point2 = nullptr;
        Math::Vector3* m_normal = nullptr;
        Math::Vector2* m_sRange = nullptr;
        Math::Vector2* m_tRange = nullptr;
    public:
        TextureMapToPlane();
        auto getOrigin() -> Math::Vector3*;
        auto getPoint1() -> Math::Vector3*;
        auto getPoint2() -> Math::Vector3*;
        auto getNormal() -> Math::Vector3*;
        auto getSRange() -> Math::Vector2*;
        auto getTRange() -> Math::Vector2*;
    };
}
