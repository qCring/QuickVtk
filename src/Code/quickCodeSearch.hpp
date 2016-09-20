#pragma once

#include <QObject>
#include <QTextCursor>

#include "quickQmlRegister.hpp"

namespace quick {

    namespace Code {

        class Search : public QObject {
            Q_OBJECT
            Q_PROPERTY(QString findString READ getFindString WRITE setFindString NOTIFY findStringChanged);
            Q_PROPERTY(QString replaceString READ getReplaceString WRITE setReplaceString NOTIFY replaceStringChanged);
            Q_PROPERTY(int currentMatch READ getCurrentMatch NOTIFY currentMatchChanged);
            Q_PROPERTY(int matchCount READ getMatchCount NOTIFY matchCountChanged);
        private:
            QList<QTextCursor> m_matches;
            QString m_findString;
            QString m_replaceString;
            bool m_valid = false;
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
            auto setReplaceString(const QString&) -> void;
            auto getReplaceString() -> QString;
            auto setCurrentMatch(int) -> void;
            auto getCurrentMatch() -> int;
            auto getMatchCount() -> int;
            auto invalidate() -> void;
        public slots:
            void findNext();
            void findPrevious();
            void replaceNext();
            void replaceAll();
        signals:
            void show();
            void hide();
            void findStringChanged();
            void currentMatchChanged();
            void replaceStringChanged();
            void matchCountChanged();
        };
    }
}
