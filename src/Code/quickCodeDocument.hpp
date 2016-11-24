#pragma once

#include "quickQmlRegister.hpp"

#include <QStack>
#include <QObject>
#include <QTextDocument>

namespace quick {

    namespace Code {

        class Selection;
        class Action;

        class Document : public QObject {
            Q_OBJECT
            Q_PROPERTY(quick::Code::Selection* selection READ getSelection CONSTANT);
            Q_PROPERTY(QList<int> lines READ getLines NOTIFY linesChanged);
            Q_PROPERTY(QString fileUrl READ getFileUrl NOTIFY fileUrlChanged);
            Q_PROPERTY(bool modified READ getModified NOTIFY modifiedChanged);
        private:
            static Qml::Register::Type<Document> Register;
            Selection* m_selection = nullptr;
            QTextDocument* m_document = nullptr;
            QString m_fileUrl;
            QString m_text;
            QList<int> m_lines;
            QStack<Action*> m_undoStack;
            QStack<Action*> m_redoStack;
            bool m_modified = true;
        private:
            auto characterAt(int) -> QString;
            auto handleBackspace() -> void;
            auto handleEnter() -> void;
            auto getLines() -> QList<int>;
        public:
            static Document* current;
            Document();
            auto bindQTextDocument(QTextDocument*) -> void;
            auto getSelection() -> Selection*;
            auto save() -> void;
            auto saveAs() -> void;
            auto getModified() -> bool;
            auto getFileUrl() -> const QString;
            auto undo() -> void;
            auto redo() -> void;
            auto clear() -> void;
            auto insertText(const QString&) -> void;
        private slots:
            void onModified(bool);
        signals:
            void select(int selectStart, int selectEnd);
            void modifiedChanged();
            void fileUrlChanged();
            void linesChanged();
        };
    }
}
