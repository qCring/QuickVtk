#pragma once

#include "quickQmlRegister.hpp"

#include <QObject>

namespace quick {

    namespace Editor {

        class Search : public QObject {
            Q_OBJECT
            Q_PROPERTY(bool visible READ getVisible NOTIFY visibleChanged);
        private:
            bool m_visible = false;
        private:
            Search();
        public:
            static Qml::Register::Controller<Search> Register;
            static auto Create() -> void;
            static Search* instance;
            auto getVisible() -> bool;
            auto show() -> void;
            auto hide() -> void;
        signals:
            void visibleChanged();
        };
    }
}
