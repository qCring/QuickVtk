#pragma once

#include "quickQmlRegister.hpp"

#include <QObject>

namespace quick::Vtk {

    class Object : public QObject {
        Q_OBJECT
    public:
        enum class Type {
            Prop,
            Algorithm,
            Widget,
            Other,
            InteractorObserver
        };
    private:
        static Qml::Register::AbstractClass<Object> Register;
        Type m_type;
    public:
        Object(Type);
        auto getType() -> Type;
    };
}
