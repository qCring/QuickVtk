#pragma once

#include "quickQmlRegister.hpp"

#include <QObject>
#include <QQuickTextDocument>
#include <QFileSystemWatcher>

namespace quick {

    namespace Editor {

        class Util;
        class Search;
        class Selection;
        class Highlighter;

        class Controller : public QObject {
            Q_OBJECT
            Q_PROPERTY(int fontSize READ getFontSize NOTIFY fontSizeChanged);
            Q_PROPERTY(bool expanded READ getExpanded NOTIFY expandedChanged);
            Q_PROPERTY(bool modified READ getModified NOTIFY modifiedChanged);
            Q_PROPERTY(bool autorun READ getAutorun WRITE setAutorun NOTIFY autorunChanged);
            Q_PROPERTY(QString buildTimestamp READ getBuildTimestamp NOTIFY buildTimestampChanged);
            Q_PROPERTY(QString fileUrl READ getFileUrl NOTIFY fileUrlChanged);
            Q_PROPERTY(QQuickTextDocument* document READ getDocument WRITE setDocument NOTIFY documentChanged);
            Q_PROPERTY(quick::Editor::Search* search READ getSearch CONSTANT);
            Q_PROPERTY(quick::Editor::Selection* selection READ getSelection CONSTANT);
        public:
            friend class Util;
            static Controller* instance;
            static Qml::Register::Controller<Controller> Register;
            static auto Create() -> void;
        private:
            QString m_buildTimestamp;
            QString m_fileUrl;
            int m_fontSizeMin = 8;
            int m_fontSize = 11;
            int m_fontSizeMax = 20;
            bool m_expanded = true;
            bool m_modified = false;
            bool m_autorun = true;
            Highlighter* m_highlighter = nullptr;
            QFileSystemWatcher* m_fileWatcher = nullptr;
            QQuickTextDocument* m_document = nullptr;
        private:
            auto setFileUrl(const QString&) -> void;
            auto loadSourceFromFile() -> void;
        public slots:
            void setModified(bool);
            void copyToClipboard(const QString&);
            void observedFileChanged(const QString&);
            void run();
            void showSearch();
            void resetFontSize();
            void increaseFontSize();
            void decreaseFontSize();
            QString getText();
        public:
            auto setDocument(QQuickTextDocument*) -> void;
            auto getDocument() -> QQuickTextDocument*;
            auto setBuildTimestamp (const QString&) -> void;
            auto getBuildTimestamp () -> QString;
            auto getSelection() -> Selection*;
            auto getSearch() -> Search*;
            auto getFileUrl() -> QString;
            auto getExpanded() -> bool;
            auto getModified() -> bool;
            auto toggleExpanded() -> void;
            auto getFontSize() -> int;
            auto setAutorun(bool) -> void;
            auto getAutorun() -> bool;
            auto loadFile(const QString&) -> void;
            ~Controller();
        signals:
            void select(int start, int end);
            void buildTimestampChanged();
            void fontSizeChanged();
            void documentChanged();
            void expandedChanged();
            void modifiedChanged();
            void fileUrlChanged();
            void autorunChanged();
            void compile();
            void clear();
        };
    }
}
