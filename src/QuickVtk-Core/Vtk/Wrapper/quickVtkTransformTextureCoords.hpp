#pragma once

#include "quickVtkDataSetAlgorithm.hpp"
#include "quickMathVector3.hpp"

#include <vtkTransformTextureCoords.h>

namespace quick::Vtk {

    class TransformTextureCoords : public DataSetAlgorithm {
        Q_OBJECT
        Q_PROPERTY(quick::Math::Vector3* origin READ getOrigin CONSTANT);
        Q_PROPERTY(quick::Math::Vector3* position READ getPosition CONSTANT);
        Q_PROPERTY(quick::Math::Vector3* scale READ getScale CONSTANT);
        Q_PROPERTY(bool flipR READ getFlipR WRITE setFlipR NOTIFY flipRChanged);
        Q_PROPERTY(bool flipS READ getFlipS WRITE setFlipS NOTIFY flipSChanged);
        Q_PROPERTY(bool flipT READ getFlipT WRITE setFlipT NOTIFY flipTChanged);
    private:
        static Qml::Register::Class<TransformTextureCoords> Register;
        vtkSmartPointer<vtkTransformTextureCoords> m_vtkObject = nullptr;
        Math::Vector3* m_origin = nullptr;
        Math::Vector3* m_position = nullptr;
        Math::Vector3* m_scale = nullptr;
    public:
        TransformTextureCoords();
        auto getOrigin() -> Math::Vector3*;
        auto getPosition() -> Math::Vector3*;
        auto getScale() -> Math::Vector3*;
        auto setFlipR(bool) -> void;
        auto getFlipR() -> bool;
        auto setFlipS(bool) -> void;
        auto getFlipS() -> bool;
        auto setFlipT(bool) -> void;
        auto getFlipT() -> bool;
    signals:
        void flipRChanged();
        void flipSChanged();
        void flipTChanged();
    };
}
