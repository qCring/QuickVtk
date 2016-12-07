#pragma once

#include "quickQmlRegister.hpp"

#include <QObject>
#include <QTextDocument>

namespace quick {

    namespace Code {

        class UndoStack;
        class Selection;

        class Document : public QObject {
            Q_OBJECT
            Q_PROPERTY(quick::Code::Selection* selection READ getSelection CONSTANT);
            Q_PROPERTY(QList<int> lines READ getLines NOTIFY linesChanged);
            Q_PROPERTY(QString fileUrl READ getFileUrl NOTIFY fileUrlChanged);
            Q_PROPERTY(bool modified READ getModified NOTIFY modifiedChanged);
        private:
            static Qml::Register::Type<Document> Register;
            Selection* m_selection = nullptr;
            UndoStack* m_undoStack = nullptr;
            QTextDocument* m_document = nullptr;
            QString m_fileUrl;
            QString m_text;
            QList<int> m_lines;
            bool m_modified = true;
        private:
            auto characterAt(int) -> QChar;
            auto getLines() -> QList<int>;
            auto onChar(const QString&) -> bool;
            auto onCut() -> bool;
            auto onUndo() -> bool;
            auto onRedo() -> bool;
            auto onCopy() -> bool;
            auto onEnter() -> bool;
            auto onPaste() -> bool;
            auto onDelete() -> bool;
            auto onBackspace() -> bool;
        public:
            static Document* current;
            Document();
            auto bindQTextDocument(QTextDocument*) -> void;
            auto getSelection() -> Selection*;
            auto save() -> void;
            auto saveAs() -> void;
            auto getModified() -> bool;
            auto getFileUrl() -> const QString;
            auto clear() -> void;
            auto format() -> void;
            ~Document();
        public:
            auto onKey(int key, int modifiers, const QString&) -> bool;
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
