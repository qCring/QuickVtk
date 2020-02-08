#pragma once

#include "quickQmlRegister.hpp"

#include <QObject>

namespace quick::App {

    class Details : public QObject {
        Q_OBJECT
        Q_PROPERTY(bool collapsed READ getCollapsed WRITE setCollapsed NOTIFY collapsedChanged);
        Q_PROPERTY(bool info READ getInfo NOTIFY infoChanged);
        Q_PROPERTY(bool types READ getTypes NOTIFY typesChanged);
    private:
        bool m_collapsed = false;
        bool m_info = true;
        bool m_types = false;
        static Qml::Register::Controller<Details> Register;
        Details() = default;
    public:
        static Details* instance;
        static auto Create() -> void;
        auto setCollapsed(bool) -> void;
        auto getCollapsed() -> bool;
        auto getInfo() -> bool;
        auto getTypes() -> bool;
    public slots:
        void toggle();
        void showInfo();
        void showTypes();
    signals:
        void collapsedChanged();
        void infoChanged();
        void typesChanged();
    };
}
