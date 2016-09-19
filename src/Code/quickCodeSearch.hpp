#pragma once

#include <QObject>

#include "quickQmlRegister.hpp"

namespace quick {

    namespace Code {

        class Search : public QObject {
            Q_OBJECT
            Q_PROPERTY(QString findString READ getFindString WRITE setFindString NOTIFY findStringChanged);
            Q_PROPERTY(bool visible READ getVisible WRITE setVisible NOTIFY visibleChanged);
        private:
            QString m_findString;
            bool m_visible = false;
        private:
            static Qml::Register::Controller<Search> Register;
            static Search* instance;
        public:
            Search();
            static auto Create() -> void;
            static auto GetInstance() -> Search*;
            auto setFindString(const QString&) -> void;
            auto getFindString() -> QString;
            auto setVisible(bool) -> void;
            auto getVisible() -> bool;
        signals:
            void findStringChanged();
            void visibleChanged();
        };
    }
}
