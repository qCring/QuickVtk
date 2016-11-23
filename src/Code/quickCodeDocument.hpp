#pragma once

#include "quickQmlRegister.hpp"

#include <QObject>
#include <QTextDocument>

namespace quick {

    namespace Code {

        class Document : public QObject {
            Q_OBJECT
            Q_PROPERTY(QString fileUrl READ getFileUrl NOTIFY fileUrlChanged);
            Q_PROPERTY(bool modified READ getModified NOTIFY modifiedChanged);
        private:
            static Qml::Register::Type<Document> Register;
            static Document* current;
            QTextDocument* m_document = nullptr;
            QString m_fileUrl;
            QString m_text;
            bool m_modified = true;
        public:
            auto bindQTextDocument(QTextDocument*) -> void;
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
