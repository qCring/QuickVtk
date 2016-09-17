#pragma once

#include <QObject>

#include "quickQmlRegister.hpp"

namespace quick {

    namespace Code {

        class Search : public QObject {
            Q_OBJECT
            Q_PROPERTY(QString searchString READ getSearchString WRITE setSearchString NOTIFY searchStringChanged);
            Q_PROPERTY(bool visible READ getVisible WRITE setVisible NOTIFY visibleChanged);
        private:
            QString m_searchString;
            bool m_visible = false;
        private:
            static Qml::Register::Controller<Search> Register;
            static Search* instance;
        public:
            Search();
            static auto Create() -> void;
            static auto GetInstance() -> Search*;
            auto setSearchString(const QString&) -> void;
            auto getSearchString() -> QString;
            auto setVisible(bool) -> void;
            auto getVisible() -> bool;
        signals:
            void searchStringChanged();
            void visibleChanged();
        };
    }
}
