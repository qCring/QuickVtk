#pragma once

#include "quickQmlRegister.hpp"

#include <QObject>
#include <QTextDocument>

namespace quick {

    namespace Code {

        class Selection;

        class Document : public QObject {
            Q_OBJECT
            Q_PROPERTY(quick::Code::Selection* selection READ getSelection CONSTANT);
            Q_PROPERTY(QString fileUrl READ getFileUrl NOTIFY fileUrlChanged);
            Q_PROPERTY(bool modified READ getModified NOTIFY modifiedChanged);
        private:
            static Qml::Register::Type<Document> Register;
            Selection* m_selection = nullptr;
            QTextDocument* m_document = nullptr;
            QString m_fileUrl;
            QString m_text;
            bool m_modified = true;
        public:
            static Document* current;
            Document();
            auto bindQTextDocument(QTextDocument*) -> void;
            auto getSelection() -> Selection*;
            auto save() -> void;
            auto saveAs() -> void;
            auto getModified() -> bool;
            auto getFileUrl() -> const QString;
        private slots:
            void onModified(bool);
        signals:
            void modifiedChanged();
            void fileUrlChanged();
        };
    }
}
