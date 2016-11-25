#pragma once

#include "quickQmlRegister.hpp"

#include <QObject>
#include <QTextCursor>
#include <QQuickTextDocument>

namespace quick {

    namespace Code {

        class Errors;
        class Search;
        class Document;
        class Settings;
        class Highlighter;

        class Editor : public QObject {
            Q_OBJECT
            Q_PROPERTY(QQuickTextDocument* editorDocument READ getEditorDocument WRITE setEditorDocument NOTIFY editorDocumentChanged);
            Q_PROPERTY(quick::Code::Errors* errors READ getErrors CONSTANT);
            Q_PROPERTY(quick::Code::Search* search READ getSearch CONSTANT);
            Q_PROPERTY(quick::Code::Settings* settings READ getSettings CONSTANT);
            Q_PROPERTY(quick::Code::Document* document READ getDocument NOTIFY documentChanged);
            Q_PROPERTY(bool expanded READ getExpanded NOTIFY expandedChanged);
            Q_PROPERTY(int fontSize READ getFontSize NOTIFY fontSizeChanged);
            Q_PROPERTY(int formatTime READ getFormatTime NOTIFY formatTimeChanged);
        private:
            static Qml::Register::Controller<Editor> Register;
            QQuickTextDocument* m_editorDocument = nullptr;
            Highlighter* m_highlighter = nullptr;
            Settings* m_settings = nullptr;
            Search* m_search = nullptr;
            Document* m_document = nullptr;
            bool m_modified = false;
            bool m_expanded = true;
            int m_formatTime = 0;
            int minFontSize = 6;
            int maxFontSize = 20;
            int m_fontSize = 12;
        public:
            Editor();
            static Editor* instance;
            static auto Create() -> void;
            auto init() -> void;
            auto setText(const QString&) -> void;
            auto getText() -> QString;
            auto setEditorDocument(QQuickTextDocument*) -> void;
            auto getEditorDocument() -> QQuickTextDocument*;
            auto getDocument() -> Document*;
            auto setModified(bool) -> void;
            auto getModified() -> bool;
            auto getExpanded() -> bool;
            auto setFontSize(int) -> void;
            auto getFontSize() -> int;
            auto getFormatTime() -> int;
            auto getErrors() -> Errors*;
            auto getSearch() -> Search*;
            auto getSettings() -> Settings*;
            auto open(const QString&) -> void;
            auto resetSelection() -> void;
            auto showSearch() -> void;
            auto resetFontSize() -> void;
            auto reset() -> void;
            auto increaseFontSize() -> void;
            auto decreaseFontSize() -> void;
            auto toggleExpanded() -> void;
            ~Editor();
        public slots:
            bool onKeyPressed(int, int, const QString&);
            void openFile();
            void saveFile();
            void newFile();
            void run();
            void format();
        signals:
            void editorDocumentChanged();
            void documentChanged();
            void modifiedChanged();
            void fontSizeChanged();
            void formatTimeChanged();
            void expandedChanged();
        };
    }
}
