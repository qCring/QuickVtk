#pragma once

#include <QObject>
#include <QTextCursor>

#include "quickQmlRegister.hpp"

namespace quick {

    namespace Code {

        class Search : public QObject {
            Q_OBJECT
            Q_PROPERTY(QString findString READ getFindString WRITE setFindString NOTIFY findStringChanged);
            Q_PROPERTY(bool visible READ getVisible WRITE setVisible NOTIFY visibleChanged);
            Q_PROPERTY(int currentMatch READ getCurrentMatch NOTIFY currentMatchChanged);
            Q_PROPERTY(int matchCount READ getMatchCount NOTIFY matchCountChanged);
        private:
            QList<QTextCursor> m_matches;
            QString m_findString;
            bool m_visible = false;
            int m_currentMatch = -1;
        private:
            static Qml::Register::Controller<Search> Register;
            static Search* instance;
        public:
            Search();
            static auto Create() -> void;
            static auto GetInstance() -> Search*;
            auto processSearch() -> void;
            auto setFindString(const QString&) -> void;
            auto getFindString() -> QString;
            auto setCurrentMatch(int) -> void;
            auto getCurrentMatch() -> int;
            auto getMatchCount() -> int;
            auto setVisible(bool) -> void;
            auto getVisible() -> bool;
        public slots:
            void clear();
            void findNext();
            void findPrevious();
        signals:
            void findStringChanged();
            void currentMatchChanged();
            void matchCountChanged();
            void visibleChanged();
        };
    }
}
